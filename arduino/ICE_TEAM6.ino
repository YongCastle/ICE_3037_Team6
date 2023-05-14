#include <ArduCAM.h>

#include "ICE_3037.h"


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(GreenPin, OUTPUT);  // LEDs
  pinMode(RedPin, OUTPUT);    // LEDs

  //pinMode(TRIG, OUTPUT);      // ultrasonic distance sensor
  //pinMode(ECHO, INPUT);       // ultrasonic distance sensor

  Serial.println("===================================================");
  Serial.println("                      SETUP                        ");
  Serial.println("===================================================");
  //print_dht
  print_dht_setup();
  Serial.println(F("DHT Setup Complete"));
  //print arducam
  arduCam_Setup();
  Serial.println(F("AruCam Setup Complete"));
  Serial.println("===================================================");
}




//BlueTooth Serial 9600

// Serial.Read can read up to 64 bytes

// |====================================+
// |            BlueTooth Input         |
// |-------+----------------------------|
// | Input | Describe                   |
// |-------+----------------------------|
// | mode0 | no Camera
// | mode1 |
// / mode2 |


uint8_t input_mode;

void loop() {

  String str_input = "";
  while(bluetooth.available()) {
    Serial.println("=====================================");
    Serial.println("         BlueTooth READ ...          ");
    Serial.println("=====================================");
    char bluetooth_data = bluetooth.read(); // Read a byte from Bluetooth
    if(bluetooth_data == '\n'){
      break;
    }
    str_input += bluetooth_data;
    delay(3);
  }
  Serial.println("BlueTooth Input : " + str_input);

  delay(300);
  
  if(true){    
    Serial.println("=====================================");
    Serial.println("          Read Temp & Humid          ");
    Serial.println("=====================================");
    readTempHumidity();

    if(temper != NULL && humid != NULL){
      Serial.println("=====================================");
      Serial.println("         BlueTooth Write(T & H)      ");
      Serial.println("=====================================");
      bluetooth_Write_TH();
    }

    Serial.println("=====================================");
    Serial.println("          Read Sound Level           ");
    Serial.println("=====================================");
    soundSensor();
    //MeasureDistance();
  }

  while (!Serial.available()) {
    // do nothing
  }
  //ArduCam Use
  Serial.println("=====================================");
  Serial.println("            ArduCam Using            ");
  Serial.println("=====================================");
  arduCam_control();
  _Capture_mode1();
  _Capture_mode2();
  _Capture_mode3();

}
