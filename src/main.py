import os
import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))



import serial

ser = serial.Serial('/dev/ttyACM0', 9600) # 아두이노와 연결된 포트 번호와 시리얼 통신 속도를 설정합니다.

while True:
    try:
        data = ser.readline().decode('utf-8').rstrip()
        print(data)
    except KeyboardInterrupt:
        break

ser.close()