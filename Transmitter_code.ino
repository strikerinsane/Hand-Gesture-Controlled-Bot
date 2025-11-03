#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ADXL345 0x53

RF24 transmitter(2, 3);

const byte address[6] = "00001";

struct data {
  float xAxis;
  float yAxis;
};

data payload;

float X_out, Y_out;

void accelerometerSetup() {
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
}

void transmitterSetup() {
  transmitter.begin();
  transmitter.openWritingPipe(address);
  transmitter.setPALevel(RF24_PA_MIN);
  transmitter.setPayloadSize(sizeof(payload));
  transmitter.stopListening();
}

void readAccelerometerData() {
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  // Read 6 registers total, each axis value is stored in 2 registers
  Wire.requestFrom(ADXL345, 6, true);

  X_out = (Wire.read() | Wire.read() << 8);   // X-axis value
  X_out = X_out / 256;
  payload.xAxis = X_out;

  Y_out = (Wire.read() | Wire.read() << 8);   // Y-axis value
  Y_out = Y_out / 256;
  payload.yAxis = Y_out;

  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print("  Ya= ");
  Serial.println(Y_out);
}

void setup() {
  Serial.begin(9600);
  // ADXL Setup
  accelerometerSetup();
  // Transmitter Setup
  transmitterSetup();
}

void loop() {
  // Get ADXL Data
  readAccelerometerData();

  // Transmit data
  transmitter.write(&payload, sizeof(payload));

  // Print data
  Serial.println(payload.xAxis);
}

