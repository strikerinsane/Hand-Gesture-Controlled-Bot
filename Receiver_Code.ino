#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#define ENA 3
#define ENB 10
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 6

RF24 receiver(7, 8);  // CE = 7, CSN = 8

const byte address[6] = "00001";

struct data {
  float xAxis;
  float yAxis;
};

data payload;

// =================== MOTOR SETUP ===================
void motorDriverSetup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// =================== MOVEMENT FUNCTIONS ===================
void moveRight() {
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void moveLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void moveBack() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void moveForward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

// =================== NRF RECEIVER SETUP ===================
void receiverSetup() {
  receiver.begin();
  receiver.setPALevel(RF24_PA_MIN);
  receiver.setPayloadSize(sizeof(payload));
  receiver.openReadingPipe(0, address);
  receiver.startListening();
}

void loop() {
  if (receiver.available()) {
    receiver.read(&payload, sizeof(payload));

    float X = payload.xAxis;
    float Y = payload.yAxis;

    Serial.println("Received Data:");
    Serial.print("X value: ");
    Serial.println(X);
    Serial.print("Y value: ");
    Serial.println(Y);

    if (Y > 0.3) {
      moveRight();
    } else if (Y < -0.3) {
      moveLeft();
    } else if (X > 0.5) {
      moveBack();
    } else if (X < -0.5) {
      moveForward();
    } else {
      stop();
    }
  }
}
