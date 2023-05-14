//=================================================================
//                         Include
//=================================================================

//Libarary Include
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//User File Include
#include "arducam_util.h"


//=================================================================
//                      Port Defination
//=================================================================

// Analog
#define soundSensorPin  A1    // sound sensor

// Digital
#define DHTPIN          8    // temperature / humidity sensor
#define GreenPin        6    // LED //for Bluetooth confirmation
#define RedPin          5    // LED //for checking sound sensor
#define TRIG            8    // Set the TRIG pin (ultrasound sending pin)
#define ECHO            9    // ECHO pin setup (ultrasonic receiving pin)

#define BT_RXD          2
#define BT_TXD          3

// Rx, Tx
SoftwareSerial bluetooth(BT_RXD, BT_TXD); // This is Bluetooth pin (Tx, Rx)

#define DHTTYPE DHT11 // Select 11 among DHT 11 and DHT series
DHT_Unified dht(DHTPIN, DHTTYPE);



//=================================================================
//                      Set Variables
//=================================================================

// Variables  
String s;
uint32_t delayMS;

String A="";
String t_data="";
int soundLevel  = 0;
int buttonState = 0; //button state default
long duration   = 0;
long distance   = 0;

float temper;
float humid;


// void setup() {
//     Serial.begin(9600);
//     bluetooth.begin(9600);

//     pinMode(GreenPin, OUTPUT);  // LEDs
//     pinMode(RedPin, OUTPUT);    // LEDs

//     pinMode(TRIG, OUTPUT);      // ultrasonic distance sensor
//     pinMode(ECHO, INPUT);       // ultrasonic distance sensor

//     print_dht_setup();

// }

// void loop() {
//     readTempHumidity();
//     bluetoothCommunication();
//     soundSensor();
//     measureDistance();
// }









//=================================================================
//                      SETUP
//=================================================================

void print_dht_setup() {
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println  (F("Min Delay:   ")); Serial.print(sensor.min_delay);
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  delay(delayMS);
}



//=================================================================
//                      MOTER CONTROL(Reserved)
//=================================================================

//=================================================================
//                      Sensor
//=================================================================

// Function to read sound sensor and turn on/off LED based on sound level
void soundSensor() {
  soundLevel = analogRead(soundSensorPin);
  Serial.print("Sound Level: ");
  Serial.println(soundLevel);
  if (soundLevel > 300) { // Adjust this threshold based on your sensor
    digitalWrite(RedPin, HIGH);
  } else {
    digitalWrite(RedPin, LOW);
  }
}

// Function to measure distance using ultrasonic sensor
void measureDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); // Store the time of the ultrasonic wave reflected from the object in a variable.
  
  // Convert duration to distance in cm
  distance = duration * 17 / 1000;

  Serial.print("\nDuration : ");
  Serial.println(duration); //Shows the time when ultrasonic waves are reflected back.
  Serial.print("\nDIstance : ");
  Serial.print(distance); //Shows the distance value (cm value) from the measured object.
  Serial.println(" Cm");
}


//=================================================================
//                     Read Temp & Humid
//=================================================================

// Function to read temperature and humidity using DHT11 sensor
void readTempHumidity() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    temper = event.temperature;
    Serial.print(temper);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    humid = event.relative_humidity;
    Serial.print(humid);
    Serial.println(F("%"));
  }
}
//=================================================================
//                      BlueTooth Communicate
//=================================================================
// Function to handle Bluetooth communication
void bluetooth_Write_TH(){
  t_data = "T:" + String(temper) + " H:" + String(humid);
  Serial.println("BlueTooth Wirte : "+t_data); // optional: print the t_data to the Serial Monitor
  bluetooth.write(t_data.c_str(), t_data.length()); // send the t_data via Bluetooth
  // put the rest of your code here
  delay(300);
}
