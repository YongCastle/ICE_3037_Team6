# Describe
  This project finally implements a smart baby cradle as part of the 2023-Spring-SKKU-ICE_3037 class.
Raspberry Pi4 and Arduino were used.

# Summary
## Arduino
### Control
* DC모터제어 - 바퀴 움직임 (뒷바퀴)
* 서보모터제어 - 방향 제어 (앞바퀴)

### Communicate 
* 블루투스 모듈(with 핸드폰)
- 온도/센서 데이터
- 수면 패턴 정보기능


### Sensor
* 온도/습도 센서 --> LED 켜
* 소리감지 센서 --> 라즈베리파이 camera on

## Respberry Pi 4
* Face Recog(AI)
--> AI(아기의 수면 패턴을 파악)
--> 아두이노로 전송
* LIDAR


## APP Inventor
* 아기 수면 패턴 확인 가능 / 언제자고 언제 일어났는지
* 방의 온도, 습도 감지
