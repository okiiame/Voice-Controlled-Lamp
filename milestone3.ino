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
  upper.write(180);
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
       angle = voice.substring(17, voice.lastIndexOf("d"));
       int moveAngle = base.read() + angle.toInt();
       if(moveAngle>10 && moveAngle<170){
         for(int pos = base.read(); pos <= moveAngle; pos += 1)  {                                  
           base.write(pos);             
           delay(dt);                       
         } 
       }
    }
    else if(voice.indexOf("clockwise") != -1) {
      Serial.println(voice);
      angle = voice.substring(10, voice.lastIndexOf("d"));
      int moveAngle = base.read() - angle.toInt();
      if(moveAngle>10 && moveAngle<170){
        for(int pos = base.read(); pos >= moveAngle; pos -= 1){                                  
          base.write(pos);             
          delay(dt);                       
        } 
      }
    }
    else if(voice.indexOf("down") != -1) {
      int count = 0;
      Serial.println(voice);
      angle = voice.substring(5, voice.lastIndexOf("d"));
      Serial.println(angle);
      int moveAngle = forearm.read() + angle.toInt();
      Serial.println(moveAngle);
      if(moveAngle>10 && moveAngle<170){
        for(int pos = forearm.read(); pos <= moveAngle; pos += 1){                           
          forearm.write(pos);
          if(count%5==0){
            upper.write(upper.read()-1);
          }
          delay(dt);
          count++;
          Serial.println(upper.read());                                           
        } 
      }
    }         
    else if(voice.indexOf("up") != -1) {
      int count = 0;
      Serial.println(voice);
      angle = voice.substring(3, voice.lastIndexOf("d"));
      Serial.println(angle);
      int moveAngle = forearm.read() - angle.toInt();
      Serial.println(moveAngle);
      if(moveAngle>10 && moveAngle<170){
        for(int pos = forearm.read(); pos >= moveAngle; pos -= 1){                              
          forearm.write(pos);
          if(count%5==0){
            upper.write(upper.read()+1);
          }
          delay(dt);
          count++;
          Serial.println(upper.read());                               
        } 
      }
    }
    else if(voice.indexOf("on") != -1) {
      Serial.println(voice);
      digitalWrite(relay, HIGH);
      delay(40);
    }
    else if(voice.indexOf("off") != -1) {
      Serial.println(voice);
      digitalWrite(relay, LOW);
      delay(40);
    }

    voice = "";
  }
}
