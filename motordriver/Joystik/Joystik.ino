#include <Ps3Controller.h>

// Pin untuk motor driver pertama (kiri)
const int LPWMPin1 = 18; // PWM pada ESP32 untuk kecepatan motor kiri
const int L_ENPin1 = 17; // GPIO pada ESP32 untuk mengaktifkan motor kiri
const int RPWMPin1 = 5;  // PWM pada ESP32 untuk kecepatan motor kiri
const int R_ENPin1 = 16; // GPIO pada ESP32 untuk mengaktifkan motor kiri

// Pin untuk motor driver kedua (kanan)
const int LPWMPin2 = 4; // PWM pada ESP32 untuk kecepatan motor kanan
const int L_ENPin2 = 0; // GPIO pada ESP32 untuk mengaktifkan motor kanan
const int RPWMPin2 = 2;  // PWM pada ESP32 untuk kecepatan motor kanan
const int R_ENPin2 = 15; // GPIO pada ESP32 untuk mengaktifkan motor kanan

void setup() {
  Serial.begin(115200);

  // Setup pin untuk motor driver
  pinMode(LPWMPin1, OUTPUT);
  pinMode(L_ENPin1, OUTPUT);
  pinMode(RPWMPin1, OUTPUT);
  pinMode(R_ENPin1, OUTPUT);
  pinMode(LPWMPin2, OUTPUT);
  pinMode(L_ENPin2, OUTPUT);
  pinMode(RPWMPin2, OUTPUT);
  pinMode(R_ENPin2, OUTPUT);

  // Setup PS3 controller
  Ps3.begin("aa:23:7c:ba:c9:00");  // Ganti dengan alamat Bluetooth stik PS3 kamu
}

void loop() {
  if (!Ps3.isConnected()) {
    // Stik PS3 tidak terhubung, berhenti robot
    stopRobot();
    Serial.println("Stik PS3 tidak terhubung.");
    return;
  }

  // Baca nilai tombol arah
  

  // Baca nilai dari analog stick kiri dan kanan
  int leftStickY = Ps3.data.analog.stick.ly;
  int leftStickX = Ps3.data.analog.stick.lx;

  // Konversi nilai stick menjadi kecepatan motor
  int motorSpeedLeft = map(leftStickY, 0, 255, -255, 255);
  int motorSpeedRight = map(leftStickX, 0, 255, -255, 255);

  // Kendalikan motor berdasarkan input stik PS3
  if (leftStickY > -30 && leftStickY < 5) {
    // Berhenti
    stopRobot();
    Serial.println("Berhenti");
  } else if (leftStickY > 6) {
    // Mundur
    moveBackward(motorSpeedLeft, motorSpeedRight);
    Serial.println("Mundur");
  } else if (leftStickY < -30) {
    // Maju
    moveForward(motorSpeedLeft, motorSpeedRight);
    Serial.println("Maju");
  }
  // Kontrol belok kiri dan belok kanan
  if (leftStickX < -30) {
    // Belok kiri
    turnLeft(motorSpeedLeft, motorSpeedRight);
    Serial.println("Belok Kiri");
  } else if (leftStickX > 30) {
    // Belok kanan
    turnRight(motorSpeedLeft, motorSpeedRight);
    Serial.println("Belok Kanan");
  }

  // Tambahkan delay untuk memberikan waktu bagi stik PS3 untuk memproses input
  delay(20);
}

void moveForward(int speedLeft, int speedRight) {
  analogWrite(LPWMPin1, abs(speedLeft));
  analogWrite(RPWMPin1, abs(speedRight));
  
  analogWrite(LPWMPin2, abs(speedLeft));
  analogWrite(RPWMPin2, abs(speedRight));
  
  digitalWrite(L_ENPin1, HIGH);
  digitalWrite(R_ENPin1, HIGH);
  
  digitalWrite(L_ENPin2, HIGH);
  digitalWrite(R_ENPin2, HIGH);
}

void moveBackward(int speedLeft, int speedRight) {
  analogWrite(LPWMPin1, abs(speedLeft));
  analogWrite(RPWMPin1, abs(speedRight));
  
  analogWrite(LPWMPin2, abs(speedLeft));
  analogWrite(RPWMPin2, abs(speedRight));
  
  digitalWrite(L_ENPin1, HIGH);
  digitalWrite(R_ENPin1, HIGH);
  
  digitalWrite(L_ENPin2, HIGH);
  digitalWrite(R_ENPin2, HIGH);
}

void turnLeft(int speedLeft, int speedRight) {
  analogWrite(LPWMPin1, abs(speedLeft));
  analogWrite(RPWMPin1, abs(speedRight));
  
  analogWrite(LPWMPin2, abs(speedLeft));
  analogWrite(RPWMPin2, abs(speedRight));
  
  digitalWrite(L_ENPin1, LOW);
  digitalWrite(R_ENPin1, LOW);
  
  digitalWrite(L_ENPin2, HIGH);
  digitalWrite(R_ENPin2, HIGH);
}

void turnRight(int speedLeft, int speedRight) {
  analogWrite(LPWMPin1, abs(speedRight));
  analogWrite(RPWMPin1, abs(speedLeft));
  
  analogWrite(LPWMPin2, abs(speedLeft));
  analogWrite(RPWMPin2, abs(speedRight));
  
  digitalWrite(L_ENPin1, HIGH);
  digitalWrite(R_ENPin1, HIGH);
  
  digitalWrite(L_ENPin2, LOW);
  digitalWrite(R_ENPin2, LOW);
}

void stopRobot() {
  analogWrite(LPWMPin1, 0);
  analogWrite(RPWMPin1, 0);
  analogWrite(LPWMPin2, 0);
  analogWrite(RPWMPin2, 0);
  
  digitalWrite(L_ENPin1, LOW);
  digitalWrite(R_ENPin1, LOW);
  
  digitalWrite(L_ENPin2, LOW);
  digitalWrite(R_ENPin2, LOW);
}
