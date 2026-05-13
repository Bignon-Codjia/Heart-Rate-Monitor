# Web-Serial Heart Rate & SpO2 Monitor

![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![JavaScript](https://img.shields.io/badge/javascript-%23323330.svg?style=for-the-badge&logo=javascript&logoColor=%23F7DF1E)
![Web Serial API](https://img.shields.io/badge/Web_Serial_API-Integrated-blue?style=for-the-badge)

This project is a real-time health monitoring system that interfaces a **MAX30100 sensor** with an Arduino and visualizes the data via a modern web dashboard. Unlike traditional IoT projects, this uses the **Web Serial API**, allowing your browser to talk directly to your hardware over USB—no server or cloud required.

---

## Features

- **Beat Detection:** Visual pulse feedback and BPM calculation.
- **Oxygen Saturation:** Real-time SpO2 percentage monitoring.
- **Dynamic Graphing:** Live heart rate trend line powered by **Chart.js**.
- **Zero Setup UI:** No need to install specialized software; works directly in Chrome or Edge.
- **Modern Dashboard:** Responsive CSS design with glassmorphism and gradient effects.

---

## Hardware Setup

### Components
- **Microcontroller:** Arduino (Uno, Nano, or ESP32).
- **Sensor:** MAX30100 Pulse Oximeter.
- **Connections:** I2C Protocol.

### Wiring Diagram
| MAX30100 Pin | Arduino Pin (Uno) | Description |
| :--- | :--- | :--- |
| **VIN** | 3.3V | Power (Use 3.3V to protect sensor) |
| **GND** | GND | Ground |
| **SCL** | A5 | I2C Clock |
| **SDA** | A4 | I2C Data |

---

## Getting Started

### 1. Firmware Installation
1. Install the `MAX30100lib` by OXullo via the Arduino Library Manager.
2. Open `firmware/heart_monitor_pox.ino` in your Arduino IDE.
3. Upload the code to your board.
4. **Important:** Keep the Serial Monitor closed in the IDE so the web browser can access the port.

### 2. Launching the Dashboard
1. Open the `web/index.html` file in **Google Chrome** or **Microsoft Edge**.
2. Click the **📡 Connect to Serial Port** button.
3. Select your device from the list and click **Connect**.
4. Place your finger on the sensor and wait 10-15 seconds for calibration.

---

## How It Works

### The Firmware
The Arduino uses the `MAX30100_PulseOximeter` library to handle the complex filtering of the IR and Red light signals. Every second, it broadcasts a formatted string over Serial:
`BPM:75 SPO2:98`

### The Frontend
The JavaScript interface uses a `TextDecoderStream` to listen to the incoming Serial data. It utilizes **Regex (Regular Expressions)** to parse the BPM and SpO2 values from the string and updates the DOM and the Chart.js dataset instantly.

---

## Browser Compatibility
This project relies on the **Web Serial API**.
- Supported: Chrome, Edge, Opera.
- Not Supported: Firefox, Safari, Internet Explorer.
- Note that the bordrate should be at 115200 for the Serial Monitor and if you want that the project works well, close the Serial monitor after uploading the code 

---

## 👤 Credits
**Designed by Bignon Codjia** *Building professional tools with accessible technology.*

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
