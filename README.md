# 🎮 Sims Plumbob LED Controller

RGB LED controller for ESP32 that simulates the iconic "Plumbob" (the green diamond) from The Sims, with mood state control and animations.

## 📋 What does this project do?

This is an **ESP32** project that controls **two synchronized RGB LED strips** (6 PWM outputs in total) with the following features:

### Main Features:

1. **WiFi Control via Access Point**
   - Creates a WiFi network called "SimsPlumbob"
   - Web interface accessible from any connected device
   - No Internet connection required

2. **Mood States from The Sims**
   - 11 predefined mood states with exact colors from the game:
     - Happy - Green
     - Inspired - Turquoise
     - Focused - Blue
     - Confident - Orange
     - Playful - Purple
     - Flirty - Pink
     - Sad - Dark blue
     - Angry - Red
     - Uncomfortable - Yellow
     - Tense - Dark orange
     - Fine - White

3. **Custom Control**
   - Free color picker (any RGB color)
   - Brightness control (0-255)
   - Two animation modes: Solid and Pulse (breathing effect)

4. **Technical Features**
   - Gamma correction for smooth transitions
   - 10-bit PWM (1024 brightness levels)
   - 2 kHz PWM frequency
   - Two fully synchronized RGB LED strips

## 🗂️ Project Structure

```
Plumbob/
├── src/
│   └── main.cpp              # Main program (setup and loop)
├── include/
│   ├── config.h              # Pin and constant configuration
│   ├── color_utils.h         # Color conversion and moods
│   ├── led_controller.h      # PWM control and animations
│   ├── web_server.h          # HTTP handlers
│   └── html_page.h           # Web interface HTML/CSS/JS
├── lib/                      # External libraries (if any)
├── test/                     # Tests (if any)
└── platformio.ini            # PlatformIO configuration
```

## 🔌 Hardware Connections

### Pin Configuration (adjustable in `config.h`):

**LED Strip 1 (Port A):**
- R1 (Red) → GPIO 16
- G1 (Green) → GPIO 17
- B1 (Blue) → GPIO 18

**LED Strip 2 (Port B - mirrored):**
- R2 (Red) → GPIO 19
- G2 (Green) → GPIO 21
- B2 (Blue) → GPIO 22

### Hardware Notes:
- Default configured for common anode with low-side MOSFETs
- If using common cathode, change `INVERT_LOGIC = true` in `config.h`
- Both strips are controlled synchronously (same color/animation)

## 🚀 How to Use

1. **Compile and Upload the Code:**
   ```bash
   pio run -t upload
   ```

2. **Connect to the ESP32:**
   - Search for the WiFi network "SimsPlumbob"
   - Connect (no password required)
   - Open your browser and go to: `http://192.168.4.1`

3. **Control the LEDs:**
   - Click on any mood state button
   - Or use the custom color picker
   - Adjust brightness with the slider
   - Activate "Pulse" mode for breathing effect

## 🛠️ Main Files

- **`config.h`**: GPIO pin configuration, PWM, WiFi settings
- **`color_utils.h`**: Functions to convert hex colors and moods to RGB
- **`led_controller.h`**: PWM control logic, gamma correction, animations
- **`web_server.h`**: HTTP request handlers
- **`html_page.h`**: Complete web interface (HTML/CSS/JavaScript)
- **`main.cpp`**: Main program with setup() and loop()

## 🎨 Customization

### Change Mood Colors:
Edit the `moodToRGB()` function in `color_utils.h`

### Add New Animation Modes:
1. Add the mode to the `AnimMode` enum in `led_controller.h`
2. Implement the animation logic
3. Update the selector in `html_page.h`

### Change Pins:
Modify the pin definitions in `config.h`

### Change WiFi Network:
Modify `AP_SSID` and `AP_PASS` in `config.h`

## 📝 Technical Notes

- **Gamma Correction**: Applies gamma 2.2 for more natural brightness transitions
- **Dual PWM**: Each color uses 2 synchronized PWM channels (6 channels total)
- **Pulse Animation**: Oscillates brightness between 30% and 100% with a 3-second period
- **Asynchronous Web Server**: Handles multiple simultaneous connections

## 📦 Dependencies

- Arduino Framework
- WiFi library (included in ESP32)
- WebServer library (included in ESP32)

## 🔧 Target Board

- **Board**: ESP32 VN IoT Uno
- **Platform**: Espressif32
- **Framework**: Arduino

## 📄 License

Open source project. Use it freely for your personal projects.

