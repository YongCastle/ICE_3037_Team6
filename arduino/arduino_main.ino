#include <SoftwareSerial.h>
#include <DHT11.h>              //습도센서

//-------------------------------------//
//         Pin Configuration
//-------------------------------------//

//Analog
#define soundSensorPin    A0        // 소리감지센서

//Digital
#define GreenPin          13        // LED                //블루투스 확인용
#define RedPin            12        // LED                //소리센서 확인용
#define DHTPIN            A1        // 온도 / 습도센서
#define TRIG              9         //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO              8         //ECHO 핀 설정 (초음파 받는 핀)
//#define buttonPin         2         // 버튼

//Rx, Tx
SoftwareSerial bluetooth(0, 1);     // This is Bluetooth pin (Tx, Rx)


#define DHTTYPE DHT11               // DHT 11, DHT시리즈중 11을 선택
DHT dht(DHTPIN, DHTTYPE);           // Initialize DHT sensor for normal 16mhz Arduino

//Variables
String s;

int soundLevel = analogRead(soundSensorPin);
int buttonState = 0; //button state defalut

long duration, distance;


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(GreenPin, OUTPUT);    // LED
  pinMode(RedPin, OUTPUT);      // LED

  pinMode(TRIG, OUTPUT);      // 초음파거리센서
  pinMode(ECHO, INPUT);       // 초음파거리센서


  //pinMode(buttonPin, INPUT);
}

void loop() {
  //-----------------Serial Communication With Respberry PI-------------------------//
  // 습도와 온도값을 측정하고, 제대로 측정되었는지 확인해줍니다.
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // 온도와 습도값을 시리얼 모니터에 출력해 줍니다.
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");


  //This is Bluetooth Part
  if(bluetooth.available()){
    Serial.write(bluetooth.read());   //Bluetooth --> Serial monitor
  }
  if(Serial.available())              //Serial monitor --> bluetooth
    bluetooth.write(Serial.read());


  //소리센서
  Serial.print("Sound Level: ");
  Serial.println(soundLevel);
  if (soundLevel > 300) {                 // Adjust this threshold based on your sensor
    digitalWrite(RedPin, HIGH);
  } else {
    digitalWrite(RedPin, LOW);
  }
  delay(200);                            // Wait for 200 milliseconds before taking the next reading


  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)

 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  distance = duration * 17 / 1000; 

  //PC모니터로 초음파 거리값을 확인 하는 코드 입니다.

  Serial.println(duration ); //초음파가 반사되어 돌아오는 시간을 보여줍니다.
  Serial.print("\nDIstance : ");
  Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");

  delay(1000); //1초마다 측정값을 보여줍니다.
}
