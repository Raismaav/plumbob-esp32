#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Project headers
#include "config.h"
#include "color_utils.h"
#include "led_controller.h"
#include "web_server.h"
#include "html_page.h"

// ====== WIFI CONFIGURATION ======
// Edit these values to customize your WiFi Access Point
// If not modified, default values from config.h will be used
const char* AP_SSID = "SimsPlumbob-rafael";     // WiFi network name
const char* AP_PASS = "123456789";     // WiFi password (empty = open network)

// ====== GLOBAL STATE ======
SharedState S;          // LED state (color, brightness, animation)
WebServer server(80);   // HTTP server on port 80

// ====== INITIALIZATION ======
void setup() {
    // Build gamma correction lookup table
    buildGammaLUT();

    // Initialize PWM for all 6 outputs (2 mirrored RGB strips)
    setupPWM(CH_R1, R1_PIN); 
    setupPWM(CH_R2, R2_PIN);
    setupPWM(CH_G1, G1_PIN); 
    setupPWM(CH_G2, G2_PIN);
    setupPWM(CH_B1, B1_PIN); 
    setupPWM(CH_B2, B2_PIN);

    // Configure WiFi Access Point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
    delay(100);

    // Setup HTTP routes
    server.on("/", [](){ handleRoot(server); });
    server.on("/set", [](){ handleSet(server, S); });
    server.begin();

    // Initialize timing and set initial LED state
    lastMs = millis();
    writeBothStrips(S);
}

// ====== MAIN LOOP ======
void loop() {
    // Handle incoming HTTP requests
    server.handleClient();

    // Update animation if active
    if (S.anim == PULSE) {
        updatePulse(S, 3.0f);  // 3 second pulse period
        delay(10);
    } else {
        delay(5);
    }
}
