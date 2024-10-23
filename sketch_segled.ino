// Define segment pins (A, B, C, D, E, F, G, DP)
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};  // A, B, C, D, E, F, G, DP

// Define digit select pins
const int digitPins[] = {10, 11, 12, 13};  // Digit 1, Digit 2, Digit 3, Digit 4

// Define LED pins
const int ledPins[] = {14, 15, 16, 17};  // LED 1, LED 2, LED 3, LED 4

// Binary patterns for numbers 0-9 on a 7-segment display (Common Anode)
const byte numberPatterns[] = {
  0b11111100,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000   // 9
};

void setup() {
  // Set segment pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Set digit select pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }

  // Set LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Turn off all segments, digits, and LEDs initially
  clearDisplay();
}

void loop() {
  // Display digits 1, 2, 3, 4
  displayNumber(1, 0);  // Display 1 on the first digit
  controlLED(0);        // Turn on LED 1
  delay(1000);          // Keep it on for 1 second

  displayNumber(2, 1);  // Display 2 on the second digit
  controlLED(1);        // Turn on LED 2
  delay(1000);          // Keep it on for 1 second

  displayNumber(3, 2);  // Display 3 on the third digit
  controlLED(2);        // Turn on LED 3
  delay(1000);          // Keep it on for 1 second

  displayNumber(4, 3);  // Display 4 on the fourth digit
  controlLED(3);        // Turn on LED 4
  delay(1000);          // Keep it on for 1 second
}

void displayNumber(int number, int digit) {
  // Turn off all digits
  clearDisplay();
  
  // Select the current digit (set HIGH for common anode)
  digitalWrite(digitPins[digit], HIGH);

  // Display the corresponding number (set segments HIGH to turn them on)
  for (int i = 0; i < 8; i++) {
    bool segmentState = numberPatterns[number] & (1 << i);
    digitalWrite(segmentPins[i], segmentState ? HIGH : LOW);  // HIGH turns ON the segment
  }

  // Small delay for multiplexing
  delay(5);
}

// Function to control the corresponding LED for the digit
void controlLED(int index) {
  // Turn off all LEDs
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);  // LOW turns OFF the LED
  }
  // Turn on the selected LED
  digitalWrite(ledPins[index], HIGH);  // HIGH turns ON the selected LED
}

// Function to clear all digits and LEDs (turn off)
void clearDisplay() {
  // Turn off all segments (LOW = off for common anode)
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], LOW);  // LOW turns OFF the segment
  }

  // Turn off all digit select pins (LOW = off for common anode)
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);  // LOW turns OFF the digit
  }

  // Turn off all LEDs
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);  // LOW turns OFF the LED
  }
}
