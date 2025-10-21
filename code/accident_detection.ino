#include <SoftwareSerial.h>
SoftwareSerial gsm(9,10);
SoftwareSerial gps(4,5);

int vibrationPin = 7;
bool accidentDetected = false;

void setup() {
  pinMode(vibrationPin, INPUT);
  Serial.begin(9600);
  gsm.begin(9600);
  gps.begin(9600);
  Serial.println("System ready...");
}

void loop() {
  int vibration = digitalRead(vibrationPin);
  if(vibration == HIGH && accidentDetected == false) {
    accidentDetected = true;
    Serial.println("Accident detected!");
    
    String location = getGPSLocation();
    sendAlert(location);
    delay(10000);
  }
}

String getGPSLocation() {
  String lat = "17.3850"; // sample data
  String lon = "78.4867"; // sample data
  return "Lat:" + lat + ", Lon:" + lon;
}

void sendAlert(String location) {
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS="+911234567890"");
  delay(1000);
  gsm.print("Accident detected! Vehicle location: ");
  gsm.print(location);
  gsm.write(26);
  Serial.println("Alert sent successfully!");
}
