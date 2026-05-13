/*
 * MAX30100 Sensor Test
 * Measurement of heart rate and oxygen level (SpO2)
 * Library: MAX30100lib by OXullo
 */

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

// Callback for beat detection
void onBeatDetected() {
  Serial.println("💓 Beat detected!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing MAX30100...");
  
  // Sensor initialization
  if (!pox.begin()) {
    Serial.println("ERROR: MAX30100 not detected!");
    Serial.println("Check:");
    Serial.println("- I2C connections (SDA/SCL)");
    Serial.println("- Power supply (3.3V)");
    Serial.println("- Pull-up resistors on SDA/SCL");
    while (1);
  }
  
  Serial.println("✓ MAX30100 sensor detected!");
  
  // Sensor configuration
  pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
  
  // Register the callback for beats
  pox.setOnBeatDetectedCallback(onBeatDetected);
  
  Serial.println("\n=== Place your finger on the sensor ===");
  Serial.println("Press firmly but without crushing");
  Serial.println("Wait 10-15 seconds for stabilization");
  Serial.println();
}

void loop() {
  // Update sensor readings
  pox.update();
  
  // Periodic display of values
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    uint8_t spo2 = pox.getSpO2();
    
    Serial.println("┌─────────────────────────────────┐");
    
    // Display heart rate
    Serial.print("│ Heart rate: ");
    if (heartRate > 0) {
      Serial.print((int)heartRate);
      Serial.print(" BPM");
      
      // Condition indicator
      if (heartRate < 60) {
        Serial.println(" ⬇️  │");
      } else if (heartRate > 100) {
        Serial.println(" ⬆️  │");
      } else {
        Serial.println(" ✓   │");
      }
    } else {
      Serial.println("-- BPM      │");
    }
    
    // Display SpO2
    Serial.print("│ SpO2 (Oxygen):       ");
    if (spo2 > 0) {
      Serial.print(spo2);
      Serial.print(" %");
      
      // Oxygen level indicator
      if (spo2 >= 95) {
        Serial.println("  ✓   │");
      } else if (spo2 >= 90) {
        Serial.println("  ⚠️  │");
      } else {
        Serial.println("  ❌  │");
      }
    } else {
      Serial.println("-- %        │");
    }
    
    Serial.println("└─────────────────────────────────┘");
    
    // Advice if no reading
    if (heartRate == 0 && spo2 == 0) {
      Serial.println("⚠️  No finger detected or weak signal");
      Serial.println("   → Reposition your finger");
      Serial.println("   → Press more firmly");
    }

    // >>> LINE ADDED FOR THE WEB INTERFACE (simple format readable by your HTML/JS) <<<
    // Only sends the line if both values are valid (>0)
    if (heartRate > 0 && spo2 > 0) {
      Serial.print("BPM:");
      Serial.print((int)heartRate);
      Serial.print(" SPO2:");
      Serial.println((int)spo2);  // \n line ending is essential
    }
    // <<< END OF ADDITION >>>

    Serial.println();
    
    tsLastReport = millis();
  }
}