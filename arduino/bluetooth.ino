#include <SoftwareSerial.h>
SoftwareSerial bluetooth(0, 1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bluetooth.available())
    Serial.write(bluetooth.read());

  if(Serial.avialable())
    bluetooth.write(Serial.read());
}
