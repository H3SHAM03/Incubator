
#include <Bonezegei_DHT11.h>
#include <SoftwareSerial.h>
#include <PulseSensorPlayground.h> 
Bonezegei_DHT11 dht(2);
const int LEDPIN = 7;
const int RELAY_PIN = 3;  // the Arduino pin, which connects to the IN pin of 
const int LDRpin = A0;
SoftwareSerial bluetooth (0, 1);
const int PulseWire = A1;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 550;   
// the setup function runs once when you press reset or power the board
PulseSensorPlayground pulseSensor;


void setup() {
  // initialize digital pin as an output.
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold); 
  pulseSensor.begin();
}

void loop() {
    if (dht.getData()) {
    float temp = dht.getTemperature();
    int hum = dht.getHumidity();
        String str  = "";
           str += temp;
           str += "/";
           str += hum;
           str += "/";
    Serial.print(str.c_str());
    if (temp > 26){
    digitalWrite(RELAY_PIN, HIGH);
    }else{
    digitalWrite(RELAY_PIN, LOW);
    }
    }

    if (Serial.available() > 0){
    String msg = Serial.readString();

    if (msg == "ON"){
      digitalWrite(LEDPIN, HIGH);
    }
    else if (msg == "OFF"){
      digitalWrite(LEDPIN, LOW);
    }
    }
    int LDRvalue = analogRead(LDRpin);
    LDRvalue = map(LDRvalue,0,1023,0,100);
    Serial.print(LDRvalue);
    Serial.print("/");
        if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
    int myBPM = pulseSensor.getBeatsPerMinute();               
    Serial.println(myBPM);
    }
    else{
      Serial.println("70");
    }

  delay(1000); // Adjust refresh rate as needed
}