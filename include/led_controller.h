#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>
#include "config.h"

// ====== ANIMATION MODES ======
enum AnimMode { 
    SOLID,  // Static color
    PULSE   // Pulsing animation
};

// ====== SHARED STATE STRUCTURE ======
struct SharedState {
    uint8_t r = 0x34;       // Red component (default: green "happy")
    uint8_t g = 0xC7;       // Green component
    uint8_t b = 0x59;       // Blue component
    uint8_t brightness = 150;  // Overall brightness (0-255)
    AnimMode anim = SOLID;     // Current animation mode
};

// ====== GAMMA CORRECTION ======
uint16_t gammaLUT[256];  // Gamma lookup table

/**
 * Build gamma correction lookup table
 * Gamma correction makes LED brightness changes appear more natural
 */
void buildGammaLUT() {
    const float gamma = 2.2f;
    for (int i = 0; i < 256; ++i) {
        float n = i / 255.0f;
        float c = powf(n, gamma);
        gammaLUT[i] = (uint16_t)(c * ((1 << PWM_BITS) - 1));
    }
}

/**
 * Map color value through gamma correction
 * @param x Input color value (0-255)
 * @return Gamma-corrected PWM duty cycle value
 */
uint16_t gammaMap(uint8_t x) { 
    return gammaLUT[x]; 
}

// ====== PWM CONTROL FUNCTIONS ======

/**
 * Apply brightness scaling to color component
 * @param c Color component (0-255)
 * @param br Brightness level (0-255)
 * @return Scaled color value
 */
static inline uint8_t applyBrightness(uint8_t c, uint8_t br) {
    return (uint16_t)c * (uint16_t)br / 255;
}

/**
 * Write PWM duty cycle to a pair of synchronized channels
 * @param chA First channel
 * @param chB Second channel (mirrored)
 * @param duty PWM duty cycle value
 */
void writePWMpair(uint8_t chA, uint8_t chB, uint16_t duty) {
    if (INVERT_LOGIC) {
        uint16_t maxv = (1 << PWM_BITS) - 1;
        duty = maxv - duty;
    }
    ledcWrite(chA, duty);
    ledcWrite(chB, duty);
}

/**
 * Write color to both RGB strips (synchronized)
 * @param S Shared state containing color and brightness
 */
void writeBothStrips(const SharedState& S) {
    // Apply brightness scaling
    uint8_t r = applyBrightness(S.r, S.brightness);
    uint8_t g = applyBrightness(S.g, S.brightness);
    uint8_t b = applyBrightness(S.b, S.brightness);

    // Apply gamma correction
    uint16_t dr = gammaMap(r);
    uint16_t dg = gammaMap(g);
    uint16_t db = gammaMap(b);

    // Write to both strips synchronously
    writePWMpair(CH_R1, CH_R2, dr);
    writePWMpair(CH_G1, CH_G2, dg);
    writePWMpair(CH_B1, CH_B2, db);
}

// ====== PULSE ANIMATION ======
unsigned long lastMs = 0;
float tPulse = 0.0f;

/**
 * Update pulse animation effect
 * Creates a sinusoidal brightness variation
 * @param S Shared state
 * @param periodSec Pulse period in seconds (default: 3.0s)
 */
void updatePulse(SharedState& S, float periodSec = 3.0f) {
    unsigned long now = millis();
    float dt = (now - lastMs) / 1000.0f;
    if (dt < 0) dt = 0;
    lastMs = now;
    tPulse += dt;

    // Oscillate brightness between 30% and 100% of base brightness
    float phase = (sinf(2.0f * 3.14159f * (tPulse / periodSec)) + 1.0f) * 0.5f;
    float f = 0.3f + 0.7f * phase;

    // Create temporary state with modulated brightness
    SharedState tmp = S;
    tmp.brightness = (uint8_t)constrain((int)(S.brightness * f), 0, (int)MAX_BRIGHTNESS);
    writeBothStrips(tmp);
}

/**
 * Initialize PWM for a single channel
 * @param ch PWM channel number
 * @param pin GPIO pin number
 */
void setupPWM(uint8_t ch, uint8_t pin) {
    ledcSetup(ch, PWM_FREQ, PWM_BITS);
    ledcAttachPin(pin, ch);
    // Initial state: off
    ledcWrite(ch, INVERT_LOGIC ? ((1 << PWM_BITS) - 1) : 0);
}

#endif // LED_CONTROLLER_H

