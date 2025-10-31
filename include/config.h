#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ====== PIN CONFIGURATION ======
// Port A - First RGB strip
#define R1_PIN  16
#define G1_PIN  17
#define B1_PIN  18

// Port B - Second RGB strip (mirrored outputs)
#define R2_PIN  19
#define G2_PIN  21
#define B2_PIN  22

// ====== PWM CONFIGURATION ======
// Common anode logic: false = 0 off, 255 max (common anode with MOSFET low-side)
//                     true  = inverted logic (direct common anode OR common cathode)
const bool INVERT_LOGIC = true;

// PWM settings (LEDC)
const uint8_t  PWM_BITS = 10;      // 0..1023 resolution
const uint32_t PWM_FREQ = 2000;    // 2 kHz frequency

// PWM channels (duplicate per color for both strips)
#define CH_R1 0
#define CH_G1 1
#define CH_B1 2
#define CH_R2 3
#define CH_G2 4
#define CH_B2 5

// ====== BRIGHTNESS LIMITS ======
#define MAX_BRIGHTNESS 255

// ====== WIFI ACCESS POINT - DEFAULT VALUES ======
// These can be overridden in main.cpp if needed
#ifndef CUSTOM_WIFI_SSID
    #define DEFAULT_AP_SSID "SimsPlumbob"
#endif

#ifndef CUSTOM_WIFI_PASS
    #define DEFAULT_AP_PASS ""  // Empty password for open network
#endif

#endif // CONFIG_H

