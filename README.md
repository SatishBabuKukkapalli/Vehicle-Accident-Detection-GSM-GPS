# 🚗 Automatic Vehicle Accident Detection System using GPS and GSM

### 📘 Project Overview
This project is designed to *detect vehicle accidents automatically* and *send the live location* of the vehicle to a pre-saved mobile number via *SMS* using *GPS and GSM modules*.  
The goal is to minimize response time after road accidents by immediately alerting emergency contacts with the *exact Google Maps location*.

---

## 🧠 Concept

Whenever a vehicle meets with an accident, the system automatically detects the impact using sensors such as an *accelerometer* or *vibration sensor*.  
After detecting the accident, it:
1. Reads the vehicle's *latitude and longitude* using the GPS module.  
2. Converts them into a *clickable Google Maps link*.  
3. Sends this link to a *predefined mobile number* through the GSM module.  

This ensures that help can reach the spot *as quickly as possible*.

---

## ⚙ Components Used

| Component | Function |
|------------|-----------|
| *Arduino UNO / Mega / ESP32* | Main microcontroller to process data |
| *GPS Module (NEO-6M)* | Provides latitude and longitude of the vehicle |
| *GSM Module (SIM800L / SIM900A)* | Sends SMS alert with Google Maps link |
| *Accelerometer (MPU6050)* | Detects sudden impact (accident) |
| *Vibration Sensor (SW-420)* | Detects heavy vibrations during collision |
| *Smoke Sensor (MQ-2)* (optional) | Detects fire/smoke after collision |
| *Temperature Sensor (LM35 / DHT11)* (optional) | Detects rise in temperature |
| *Buzzer / LED* | Local alert indication |
| *Power Supply (12V / Li-ion Battery)* | To power the system reliably |

---

## 📡 How It Works

1. The sensors (accelerometer, vibration) constantly monitor the vehicle’s movement.  
2. When a sudden impact or high vibration is detected, the Arduino assumes an accident has occurred.  
3. The Arduino then reads *latitude and longitude* from the GPS module.  
4. It creates a *Google Maps link* in this format: https://www.google.com/maps/search/?api=1&query=

##Example
https://www.google.com/maps/search/?api=1&query=15.8333,78.0333

6. The link is sent via *SMS* to a predefined phone number using the GSM module.
7. When the receiver taps the link, *Google Maps opens directly*, showing the accident location.

---

## 🧭 Google Maps Link Creation in Code and ardunio code

```cpp
double latitude = gps.location.lat();
double longitude = gps.location.lng();

String googleMapLink = "https://www.google.com/maps/search/?api=1&query=";
googleMapLink += String(latitude, 6);
googleMapLink += ",";
googleMapLink += String(longitude, 6);

##Arduino code
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
