/*
 * Code for rotating the base of the lamp
 * using my voice.
 */

#include<Servo.h>
Servo base;

String voice;
String angle;

void setup() {
  Serial.begin(9600);
  base.attach(9);
}

void loop() {
  //forming the word
  //whenever serial gets a signal
  while(Serial.available()) {
    delay(10);
    char c = Serial.read();
    Serial.println(c);
    if(c == '#'){
      break;
    }
    voice += c;
    Serial.println(voice);
  }
  //testing if it is counterclockwise or not
  if(voice.length() > 0) { 
     if(voice.indexOf("counterclockwise") != -1) {
       Serial.println(voice);
       angle = voice.substring(17, voice.indexOf("d"));
       int moveAngle = base.read() + angle.toInt();
       base.write(moveAngle);
       voice = "";
       delay(100);
    }
  }
}
