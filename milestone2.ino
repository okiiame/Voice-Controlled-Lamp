/*
 *Turn LED on and off using voice 
 */
 
int relay_pin = 8;
String voice;
void setup(){ 
  Serial.begin(9600);
  pinMode(relay_pin,OUTPUT);
}
void loop(){
  //because the bluetooth module sends characters
  //we have to form the word ourselves using a whileloop
  while(Serial.available()) {
    delay(10);
    char c = Serial.read();
    if(c == '#'){
      break;
    }
    voice += c;
  }

  //word testing
  if(voice.indexOf("on") != -1) {
    digitalWrite(relay_pin, HIGH);
    voice = "";
    delay(1000);
  }
  else if(voice.indexOf("off") != -1) {
    digitalWrite(relay_pin, LOW);
    voice = "";
    delay(1000);
  }
}
