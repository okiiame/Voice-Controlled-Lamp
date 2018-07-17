#include<Servo.h>
Servo base;
Servo upper; //upper arm
Servo forearm;

int relay = 8;

int ldr = A0;

int dt = 40; //delay time

int in = 2; 
int state = HIGH;  
int r;           
int p = LOW;    
long time = 0;       
long debounce = 200;   

String voice;
String angle;

void setup() {
  Serial.begin(9600);
  base.attach(9);
  upper.attach(7);
  forearm.attach(12);
  base.write(10);
  upper.write(90);
  forearm.write(0);
  pinMode(relay, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(in, INPUT);
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
      if(moveAngle>10 && moveAngle<110){
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
    else if(voice.indexOf("up") != -1 || voice.indexOf("op") != -1) {
      int count = 0;
      Serial.println(voice);
      angle = voice.substring(3, voice.lastIndexOf("d"));
      Serial.println(angle);
      int moveAngle = forearm.read() - angle.toInt();
      Serial.println(moveAngle);
      if(moveAngle>10 && moveAngle<110){
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
    else if(voice.indexOf("on") != -1 || voice.indexOf("lumos") != -1) {
      Serial.println(voice);
      state = HIGH;
      p = HIGH;
      digitalWrite(relay, state);
      delay(40);
    }
    else if(voice.indexOf("off") != -1) {
      Serial.println(voice);
      state = LOW;
      p = HIGH;
      digitalWrite(relay, state);
      delay(40);
    }
    else if(voice.indexOf("reset") != -1) {
      reset();
    }
    else if(voice.indexOf("sense") != -1 || voice.indexOf("science") != -1 || voice.indexOf("thanks") != -1) {
      int a = analogRead(ldr);
      Serial.println(a);

      if(a>150){
        state = LOW;
        p = HIGH;
        digitalWrite(relay, state);
        delay(1000);
      }
      else{
        state = HIGH;
        p = HIGH;
        digitalWrite(relay, state);
        delay(500);
      }
    }
    voice = "";
  }
  
  r = digitalRead(in);
  if (r == HIGH && p == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else 
      state = HIGH;
    time = millis();    
  }
  digitalWrite(relay, state);
  p = r;
}

void reset(){
  for(int i = base.read(); i >= 0; i--){
    base.write(i);
    delay(dt);
  }
  upper.write(90);
  for(int i = forearm.read(); i >= 0; i--){
    forearm.write(i);
    delay(dt);
  }
}

