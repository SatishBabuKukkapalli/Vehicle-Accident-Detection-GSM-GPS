# Automatic Vehicle Accident Detection and Messaging System

This Arduino-based project detects vehicle accidents using vibration and accelerometer sensors. When an accident occurs, it sends an alert message with GPS coordinates via GSM module to a pre-coded phone number.

## Components Used
- Arduino UNO
- GSM module (SIM800L or SIM900)
- GPS module (NEO-6M)
- Accelerometer Sensor (ADXL335/ADXL345)
- Vibration Sensor
- LCD Display
- Speed Sensor
- Power Supply and Connecting Wires

## Working Principle
Whenever a vehicle meets an accident, the accelerometer/vibration sensor detects sudden impact. The Arduino collects GPS location through NEO-6M and sends a message to a pre-stored phone number using GSM. The message contains vehicle's latitude and longitude.

## Objectives
- Automatically detect accidents in real-time
- Send GPS coordinates through SMS immediately
- Reduce emergency response time
- Save lives through technological intervention

## Software Used
- Arduino IDE

## Advantages
- Detects accident location accurately
- Sends alert messages automatically
- Provides faster response time
- Low cost and reliable for all vehicles

## Applications
- Use in cars, buses, and heavy vehicles
- Can be connected with airbag systems
- Used in smart transport monitoring

## Future Scope
- Integration with cloud servers and IoT applications
- Addition of camera module for evidence
- Detection of driver drowsiness and alcohol levels
