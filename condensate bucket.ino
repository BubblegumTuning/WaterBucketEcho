
#include "LowPower.h"


float duration, distance;
#define triggerPin 12
#define echoPin 10
#define LedPin 4
#define beeperPin 5
#define bucketFullDistance 6 //distance in centimeters
#define serialSpeed 9600
#define BeeperTone 2500
#define BeepLenght 500
#define BeepPause 1000

void setup() {
  Serial.begin (serialSpeed);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LedPin, OUTPUT);

}

void loop() {
 //pulse the sensor trigger pin to measure distance

digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin, LOW);


duration = pulseIn(echoPin, HIGH);

//speed of sound at 25ºC divided to and back, to be more accurate, we would need to add a temperature sensor to modify the speed of sound in real time
distance = (duration / 2) * 0.034618;




//send results to serial monitor





Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
     Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  delay(500);

  if (distance <=bucketFullDistance ) {
    Serial.println("Empty condensate bucket!"); 
    digitalWrite(LedPin, HIGH);
    tone(beeperPin, BeeperTone, BeepLenght);
    delay (BeepPause);
    tone(beeperPin, BeeperTone, BeepLenght);
    delay (BeepPause);
    tone(beeperPin, BeeperTone, BeepLenght);
  }
  else{
      // Blink LED before going to sleep to show the device is working
      digitalWrite(LedPin, HIGH);
      delay (5);
      digitalWrite(LedPin, LOW);
    // Enter power down state for 8 s with ADC and BOD module disabled
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  }



}