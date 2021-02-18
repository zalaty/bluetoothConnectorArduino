#include <SoftwareSerial.h> // use the software uart
SoftwareSerial bluetooth(10,11); // RX (11), TX(10)

unsigned long p
eviousMillis = 0;        // will store last time
const long interval = 500;           // interval at which to delay
static uint32_t tmp; // increment this
char received;


const int pin13 = 13; // Led01
const int pin08 = 8;  // Led02
const int pin07 = 7;  // Led03
const int pin05 = 5;   // Buzzer01
const int delay01 = 200;
const int delay02 = 800;
const int delay03 = 3000;
const int tone01 = 200;
const int tone02 = 800;

void setup() {

  pinMode(pin13, OUTPUT);
  pinMode(pin08, OUTPUT);
  pinMode(pin07, OUTPUT);
  pinMode(pin05, OUTPUT);
  
  pinMode(9,OUTPUT); 
  digitalWrite(9,HIGH);
  Serial.begin(9600);
  
  pinMode(13, OUTPUT); // for LED status
  bluetooth.begin(38400); // start the bluetooth uart at 9600 which is its default
  delay(delay01); // wait for voltage stabilize
  //bluetooth.print("AT+NAMEmcuhq.com"); // place your name in here to configure the bluetooth name.
                                       // will require reboot for settings to take affect. 
  delay(delay03); // wait for settings to take affect. 
}

void loop() {
  if (bluetooth.available()) { // check if anything in UART buffer

    received = bluetooth.read();
    bluetooth.print(received);
    Serial.print(received);
    
    if(received == '1'){
      //opcionUno();
      turnOnLeds();
    } else if(received == '2'){
      turnOffLeds();
    } else if(received == '3'){
      beep(tone01);
    } else if(received == '4'){
      lightsDance01();
    } else if(received == '5'){
      lightsDance02();
    } else if(received == '6'){
      beep(tone02);
    }

  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //bluetooth.print(tmp++); // print this to bluetooth module
  }

}

void opcionUno(){
  digitalWrite(13,!digitalRead(13));
}

void turnOnLeds(){
  digitalWrite(pin13, HIGH);
  digitalWrite(pin08, HIGH);
  digitalWrite(pin07, HIGH);
}

void turnOffLeds(){
  digitalWrite(pin13, LOW);
  digitalWrite(pin08, LOW);
  digitalWrite(pin07, LOW);
}

void turnOnLeds(int first, int second, int third){
  digitalWrite(pin13, first);
  digitalWrite(pin08, second);
  digitalWrite(pin07, third);
}

void lightsDance01(){
  turnOnLeds();
  delay(delay01);
  turnOffLeds();
  delay(delay01);
  turnOnLeds();
  delay(delay01);
  turnOffLeds();
  delay(delay01);
  turnOnLeds();
  delay(delay01);
  turnOffLeds();
  delay(delay01);
}

void lightsDance02(){
  turnOnLeds(HIGH, LOW, LOW);
  delay(delay01);
  turnOnLeds(LOW, HIGH, LOW);
  delay(delay01);
  turnOnLeds(LOW, LOW, HIGH);
  delay(delay01);
  turnOnLeds(HIGH, LOW, LOW);
  delay(delay01);
  turnOnLeds(LOW, HIGH, LOW);
  delay(delay01);
  turnOnLeds(LOW, LOW, HIGH);
  delay(delay01);
  turnOnLeds(HIGH, LOW, LOW);
  delay(delay01);
  turnOnLeds(LOW, HIGH, LOW);
  delay(delay01);
  turnOnLeds(LOW, LOW, HIGH);
  delay(delay01);
  turnOffLeds();
  delay(delay01);
}

void beep(int tone){
  analogWrite(pin05, tone);
  delay(delay02);
  analogWrite(pin05, 0);
  delay(delay01);
}
