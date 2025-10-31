#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <WebServer.h>
#include "config.h"
#include "color_utils.h"
#include "led_controller.h"
#include "html_page.h"

// ====== HTTP REQUEST HANDLERS ======

/**
 * Handle root path "/" - serve the HTML interface
 */
void handleRoot(WebServer& server) { 
    server.send_P(200, "text/html", INDEX_HTML); 
}

/**
 * Apply parameters from HTTP request to shared state
 * @param S Shared state to modify
 * @param mood Mood name (optional)
 * @param hex Hex color code (optional)
 * @param bstr Brightness string (optional)
 * @param anim Animation mode (optional)
 */
void applyParams(SharedState& S, const String& mood, const String& hex, 
                 const String& bstr, const String& anim) {
    // Update color from mood
    if (mood.length()) {
        RGB c; 
        moodToRGB(mood, c);
        S.r = c.r; 
        S.g = c.g; 
        S.b = c.b;
    }
    
    // Update color from hex code
    if (hex.length() == 6) {
        RGB c = hexToRGB(hex);
        S.r = c.r; 
        S.g = c.g; 
        S.b = c.b;
    }
    
    // Update brightness
    if (bstr.length()) {
        int v = constrain(bstr.toInt(), 0, (int)MAX_BRIGHTNESS);
        S.brightness = (uint8_t)v;
    }
    
    // Update animation mode
    if (anim.length()) {
        S.anim = (anim == "pulse") ? PULSE : SOLID;
    }
}

/**
 * Handle "/set" path - update LED state from parameters
 */
void handleSet(WebServer& server, SharedState& S) {
    applyParams(S, 
                server.arg("mood"), 
                server.arg("hex"), 
                server.arg("brightness"), 
                server.arg("anim"));
    
    // If in solid mode, immediately update LEDs
    if (S.anim == SOLID) {
        writeBothStrips(S);
    }
    
    server.send(200, "text/plain", "OK");
}

#endif // WEB_SERVER_H

