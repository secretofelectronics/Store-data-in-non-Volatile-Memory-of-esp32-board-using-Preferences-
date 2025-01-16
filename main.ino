#include <Preferences.h>

// Create Preferences object
Preferences preferences;

// Pin definitions
const int ledPin = 5;    // LED pin
const int buttonPin = 18; // Push button pin

bool ledState = false;   // LED state

void setup() {
  Serial.begin(115200);

  // Pin setup
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);

  // Initialize Preferences
  preferences.begin("ledPrefs", false);

  // Check if a previous LED state exists
  if (preferences.isKey("ledState")) {
    ledState = preferences.getBool("ledState", false);
    Serial.println("Loaded LED state: " + String(ledState ? "ON" : "OFF"));
  } else {
    Serial.println("No saved LED state found. Default is OFF.");
  }

  // Apply the saved LED state
  digitalWrite(ledPin, ledState ? HIGH : LOW);
}

void loop() {
  static bool lastButtonState = LOW;  // Previous button state
  bool buttonState = digitalRead(buttonPin);  // Current button state

  // Check for button press (low-to-high transition)
  if (buttonState == HIGH && lastButtonState == LOW) {
    delay(50);  // Debounce delay
    if (digitalRead(buttonPin) == HIGH) {
      // Toggle LED state
      ledState = !ledState;

      // Save the LED state in preferences
      preferences.putBool("ledState", ledState);
      Serial.println("LED state saved: " + String(ledState ? "ON" : "OFF"));

      // Update LED
      digitalWrite(ledPin, ledState ? HIGH : LOW);
    }
  }

  lastButtonState = buttonState;  // Update last button state
}
