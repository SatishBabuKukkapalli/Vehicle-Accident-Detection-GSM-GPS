#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial(4, 3);   // RX, TX for GPS
SoftwareSerial gsmSerial(7, 8);   // RX, TX for GSM
TinyGPSPlus gps;

String phoneNumber = "+919876543210";

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);
  delay(2000);

  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1");  // SMS text mode
  delay(1000);

  Serial.println("System Ready. Waiting for GPS fix...");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    String googleMapLink = "https://www.google.com/maps/search/?api=1&query=";
    googleMapLink += String(latitude, 6);
    googleMapLink += ",";
    googleMapLink += String(longitude, 6);

    sendSMS(phoneNumber, googleMapLink);
    delay(10000);
  }
}

void sendSMS(String number, String message) {
  gsmSerial.println("AT+CMGF=1");
  delay(500);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(number);
  gsmSerial.println("\"");
  delay(500);
  gsmSerial.print("Accident Alert! Vehicle Location:\n");
  gsmSerial.print(message);
  delay(500);
  gsmSerial.write(26);  // Ctrl+Z to send
  delay(2000);

  Serial.println("SMS Sent: " + message);
}
