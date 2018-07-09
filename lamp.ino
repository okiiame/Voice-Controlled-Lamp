#include <Brain.h>

#include<Servo.h>
Servo base;
Servo upper; //upper arm
Servo forearm;

int relay = 8;

int dt = 40; //delay time

String voice;
String angle;

void setup() {
  Serial.begin(9600);
  base.attach(9);
  base.write(10);
  upper.attach(7);
  upper.write(60);
  forearm.attach(12);
  forearm.write(0);
  pinMode(relay, OUTPUT);
}

void loop() {
  while(Serial.available()) {
    delay(10);
    char c = Serial.read();
    //Serial.println(c);
    if(c == '#'){
      break;
    }
    voice += c;
    //Serial.println(voice);
  }
  if(voice.length() > 0) { 
     if(voice.indexOf("counterclockwise") != -1) {
       Serial.println(voice);
       angle = voice.substring(17, voice.indexOf("d"));
       int moveAngle = base.read() + angle.toInt();
       if(moveAngle>10 && moveAngle<170){
         for(int pos = base.read(); pos <= moveAngle; pos += 1)  
         {                                  
           base.write(pos);             
           delay(dt);                       
         } 
       }
       voice = "";
    }
    else if(voice.indexOf("clockwise") != -1) {
      Serial.println(voice);
      angle = voice.substring(10, voice.indexOf("d"));
      int moveAngle = base.read() - angle.toInt();
      if(moveAngle>10 && moveAngle<170){
        for(int pos = base.read(); pos >= moveAngle; pos -= 1){                                  
          base.write(pos);             
          delay(dt);                       
        } 
      }
      voice = "";
    }
    else if(voice.indexOf("down") != -1) {
      int count = 0;
      Serial.println(voice);
      angle = voice.substring(8, voice.indexOf("d"));
      int moveAngle = base.read() + angle.toInt();
      if(moveAngle>10 && moveAngle<170){
        for(int pos = base.read(); pos <= moveAngle; pos += 1){                                  
          forearm.write(pos);
          if(count%5==0){
            upper.write(upper.read()-1);
          }
          count++;             
          delay(dt);                       
        } 
      }
      voice = "";
    }         
    else if(voice.indexOf("up") != -1) {
      int count = 0;
      Serial.println(voice);
      angle = voice.substring(9, voice.indexOf("d"));
      int moveAngle = base.read() - angle.toInt();
      if(moveAngle>60 && moveAngle<120){
        for(int pos = base.read(); pos >= moveAngle; pos -= 1){                                  
          forearm.write(pos);
          if(count%5==0){
            upper.write(upper.read()+1);
          }
          count++;             
          delay(dt);                       
        } 
      }
      voice = "";
    }
    /*
    else if(voice.indexOf("down") != -1) {
      Serial.println(voice);
      angle = voice.substring(5, voice.indexOf("d"));
      int moveAngle = base.read() + angle.toInt();
      if(moveAngle>10 && moveAngle<170){
        for(int pos = base.read(); pos <= moveAngle; pos += 1){                                  
          forearm.write(pos);             
          delay(dt);                       
        } 
      }
      voice = "";
    }
    else if(voice.indexOf("up") != -1){
      Serial.println(voice);
      angle = voice.substring(3, voice.indexOf("d"));
      int moveAngle = base.read() - angle.toInt();
      if(moveAngle>10 && moveAngle<170){
        for(int pos = base.read(); pos >= moveAngle; pos -= 1){                                  
          forearm.write(pos);             
          delay(dt);                       
        } 
      }
      voice = "";
    }
    */
    else if(voice.indexOf("on") != -1) {
      Serial.println(voice);
      digitalWrite(relay, HIGH);
      voice = "";
      delay(40);
    }
    else if(voice.indexOf("off") != -1) {
      Serial.println(voice);
      digitalWrite(relay, LOW);
      voice = "";
      delay(40);
    }
  }
}
