#include "main.h"



//=================================================================
//                      Port Defination
//=================================================================

// Analog
#define soundSensorPin  A5    // sound sensor

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

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(GreenPin, OUTPUT);  // LEDs
  pinMode(RedPin, OUTPUT);    // LEDs

  pinMode(TRIG, OUTPUT);      // ultrasonic distance sensor
  pinMode(ECHO, INPUT);       // ultrasonic distance sensor

  //print_dht
  print_dht_setup();

  //print arducam
  arduCam_Setup();

}

void loop() {
  
  if (Serial.available()) {
    bluetooth.write(Serial.read()); //Serial monitor --> bluetooth
  }
  
  readTempHumidity();
  bluetoothCommunication();
  soundSensor();
  measureDistance();

  //ArduCam Use
  audoCam_control()
  _Capture_mode1()
  _Capture_mode2()
  _Capture_mode3()
}
