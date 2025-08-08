#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 
#define CE_PIN 7
#define CSN_PIN 8
RF24 radio(CE_PIN, CSN_PIN);
// int ENA = 3;
// int ENB = 10;
int MotorA1 = 2; 
int MotorA2 = 3;
int MotorB1 = 4;
int MotorB2 = 5;
const byte address[6] = "00001"; 
//NRF24L01 buffer limit is 32 bytes (max struct size) 
struct payload { 
	 float data1; 
	 float data2; 
}; 
payload payload; 
void setup() 
{ 
	 Serial.begin(9600);  
	 radio.begin();
  //  pinMode(ENA,OUTPUT);
  //  pinMode(ENB,OUTPUT);
   pinMode(MotorA1,OUTPUT);
   pinMode(MotorA2,OUTPUT);
   pinMode(MotorB1,OUTPUT);
   pinMode(MotorB2,OUTPUT);
   radio.setPALevel(RF24_PA_MIN); 
	 //Default value is the maximum 32 bytes1 
	 radio.setPayloadSize(sizeof(payload)); 
	 //Act as receiver 
	 radio.openReadingPipe(0, address); 

	 radio.startListening(); 
} 
void loop() 
{ 
	  
	 if (radio.available() > 0) { 
	   radio.read(&payload, sizeof(payload)); 
	   Serial.println("Received"); 
	   Serial.print("X:"); 
	   Serial.println(payload.data1); 
	   Serial.print("Y:"); 
	   Serial.println(payload.data2);
     if(payload.data2>0.3)
     {
        //  analogWrite(ENA,130);
        //  analogWrite(ENB,130);
         digitalWrite(MotorA1,1);
         digitalWrite(MotorA2,0);
         digitalWrite(MotorB1,1);
         digitalWrite(MotorB2,0); 
     }
     else if(payload.data2<-0.3)
     {
        //  analogWrite(ENA,150);
        //  analogWrite(ENB,150);
         digitalWrite(MotorA1,0);
         digitalWrite(MotorA2,1);
         digitalWrite(MotorB1,0);
         digitalWrite(MotorB2,1); 
     }
     else if(payload.data1>0.5)
     {
        //  analogWrite(ENA,150);
        //  analogWrite(ENB,150);
         digitalWrite(MotorA1,0);
         digitalWrite(MotorA2,1);
         digitalWrite(MotorB1,1);
         digitalWrite(MotorB2,0); 
     }
     else if(payload.data1<-0.5)
     {
        //  analogWrite(ENA,150);
        //  analogWrite(ENB,150);
         digitalWrite(MotorA1,1);
         digitalWrite(MotorA2,0);
         digitalWrite(MotorB1,0);
         digitalWrite(MotorB2,1); 
     }
     else
     {
        // analogWrite(ENA,0);
        // analogWrite(ENB,0);
        digitalWrite(MotorA1,0);
        digitalWrite(MotorA2,0);
        digitalWrite(MotorB1,0);
        digitalWrite(MotorB2,0);
     } 
    //  delay(500);
	 } 
	 
}