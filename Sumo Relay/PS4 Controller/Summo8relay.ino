#include <BluetoothSerial.h>
#include <PS4Controller.h>
BluetoothSerial ESP_BT;

// Define motor control pins using step up
#define relay1 12 // Motor 1 LPWM pin
#define relay2 13 // Motor 1 RPWM pin
#define relay3 14 // Motor 2 LPWM pin
#define relay4 15 // Motor 2 RPWM pin

// Pins for slow control normal speed
#define relay5 38 // Motor 1 LPWM pin (slow)
#define relay6 35 // Motor 1 RPWM pin (slow)
#define relay7 34 // Motor 2 LPWM pin (slow)
#define relay8 27 // Motor 2 RPWM pin (slow)

void setup()
{
  // Serial monitor
  Serial.begin(115200);
  ESP_BT.begin("RADE");

  // Initialize PS4 controller
  PS4.begin("xx:xx:xx:xx:xx:xx");
  PS4.attach(onConnect);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  stopMotors();
}

void loop()
{
  if (PS4.isConnected())
  {
    // Using Step Up
    if (PS4.Right())
    {
      moveForward();
    }
    else if (PS4.Left())
    {
      moveBackward();
    }
    else if (PS4.Up())
    {
      turnLeft();
    }
    else if (PS4.Down())
    {
      turnRight();
    }
    // Normal speed
    else if (PS4.Square())
    {
      moveForwardSlow();
    }
    else if (PS4.Circle())
    {
      moveBackwardSlow();
    }
    else if (PS4.Triangle())
    {
      turnLeftSlow();
    }
    else if (PS4.Cross())
    {
      turnRightSlow();
    }
    else
    {
      stopMotors();
    }
  }
}

void onConnect()
{
  Serial.println("PS4 Controller Connected");
}

// Function to move forward
void moveForward()
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

// Function to move backward
void moveBackward()
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}

// Function to turn left
void turnLeft()
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

// Function to turn right
void turnRight()
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}

// Slow version of the robot
void moveForwardSlow()
{
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, LOW);
}

void moveBackwardSlow()
{
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, HIGH);
}

void turnLeftSlow()
{
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, LOW);
}

void turnRightSlow()
{
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, HIGH);
}

// Function to stop the motors
void stopMotors()
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, LOW);
}
