#include <BluetoothSerial.h>

// Create a BluetoothSerial object
BluetoothSerial ESP_BT;

// Define motor control pins
#define relay1  12  // Motor 1 LPWM pin
#define relay2  13  // Motor 1 RPWM pin
#define relay3  14  // Motor 2 LPWM pin
#define relay4  27  // Motor 2 RPWM pin

void setup() {
  // Start the serial monitor
  Serial.begin(115200);

  // Start Bluetooth communication
  ESP_BT.begin("RADE");

  // Set motor control pins as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // Initialize motors as stopped
  stopMotors();
}

void loop() {
  // Check if any data is available from the Bluetooth module
  if (ESP_BT.available()) {
    char command = ESP_BT.read();

    // Handle received commands
    switch (command) {
      case 'L':  // Forward L
        moveForward();
        break;
      case 'R':  // Backward R
        moveBackward();
        break;
      case 'B':  // Turn Left B
        turnLeft();
        break;
      case 'F':  // Turn Right F
        turnRight();
        break;
      case 'S':  // Stop
        stopMotors();
        break;
    }
  }
}

// Function to move forward
void moveForward() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

// Function to move backward
void moveBackward() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}

// Function to turn left
void turnLeft() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

// Function to turn right
void turnRight() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}
