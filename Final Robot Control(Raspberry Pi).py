from PyMata.pymata import PyMata
import time
#Pin
PWMA = 3 #모터의 파워를 설정하기 위한 핀 설정
DIRA = 12 #모터의 방향을 설정하기 위한 핀 설정
PWMB = 11 #모터의 파워를 설정하기 위한 핀 설정
DIRB = 13 #모터의 방향을 설정하기 위한 핀 설정
rightIrSensorPin = 1 #오른쪽 적외선센서 핀 설정
leftIrSensorPin = 0 #왼쪽 적외선센서 핀 설정
trig = 9 #초음파센서의 trig핀 설정
echo = 8 #초음파센서 echo핀 설정
#Motor settings
CW = 1 #시계 방향을 1로 설정
CCW = 0 #반시계 방향을 0으로 설정
MOTOR_LEFT = 0 #왼쪽 모터를 0으로 설정
MOTOR_RIGHT = 1 #오른쪽 모터를 1로 설정
BLACK = 0 #흰색을 0으로 설정
WHITE = 1 #검정색을 1로 설정
#connection port
PORT = '/dev/ttyACM0' #포트를 '/dev/ttyACM0'로 설정
board = PyMata(PORT,verbose=True) #보드 설정
#analog pin setting
board.set_pin_mode(rightIrSensorPin,board.INPUT,board.ANALOG) #rightIrSensorPin으로 적외선센서 값 받기
board.set_pin_mode(leftIrSensorPin,board.INPUT,board.ANALOG) #leftIrSensorPin으로 적외선센서 값 받기
board.sonar_config(trig,echo) #trig, echo 핀으로 초음파센서 값 받기
#functions
def readIrSensor(pin): #적외선센서 값을 받기 위한 함수 생성
value = 1023 - board.analog_read(pin) #적외선 센서로 받은 값을 1023과 뺀 값을 변수 value에 넣기
return value #value 반환
def colorFinder(sensorValue): #색을 판단하기 위한 함수 생성
THRESHOULD_IR = 800 #색을 판단하기 위한 기준값을 800으로 설정
WHITE = 1 #흰색을 1로 설정
BLACK = 0 #검은색을 0으로 설정
color = WHITE if sensorValue > THRESHOULD_IR else BLACK #파라미터로 받은 값이 기준값 보다 크면 흰색으로, 기준값 보다 낮다면 검은색으로 판단
return color #color 반환
def setMotor(PWM,DIR): #모터를 설정하기 위한 함수 생성
board.set_pin_mode(PWM,board.PWM,board.DIGITAL) #핀 모드 설정
board.set_pin_mode(DIR,board.OUTPUT,board.DIGITAL) #핀 모드 설정
def setRightandLeftMotors(): #오른쪽과 왼쪽 모터를 설정하기 위한 함수 생성
setMotor(PWMA,DIRA) #PWMA핀과 DIRA핀으로 모터 설정
setMotor(PWMB,DIRB) #PWMB핀과 DIRB핀으로 모터 설정
def driveMotor(motor,direction,speed): #모터,방향,속도를 파라미터로 받는 driveArdumoto 함수 생성
if(motor == MOTOR_RIGHT): #오른쪽 모터
board.analog_write(PWMA,speed) #속도를 파라미터로 받은 speed로 설정
board.digital_write(DIRA,direction) #방향을 파라미터로 받은 direction으로 설정
elif (motor == MOTOR_LEFT): #왼쪽 모터
board.analog_write(PWMB,speed) #속도를 파라미터로 받은 speed로 설정
board.digital_write(DIRB,direction) #방향을 파라미터로 받은 direction으로 설정
#ROBOT MOTION CONTROL
def robotForward(power): #직진
driveMotor(MOTOR_RIGHT,CCW,power) #오른쪽 모터를 반시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
driveMotor(MOTOR_LEFT,CW,power) #왼쪽 모터를 시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
def robotBackward(power): #후진
driveMotor(MOTOR_RIGHT,CW,power) #오른쪽 모터를 시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
driveMotor(MOTOR_LEFT,CCW,power) #왼쪽 모터를 반시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
def robotRight(power): #우회전
driveMotor(MOTOR_RIGHT,CW,power) #오른쪽 모터를 시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
driveMotor(MOTOR_LEFT,CW,power) #왼쪽 모터를 시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
def robotLeft(power): #좌회전
driveMotor(MOTOR_LEFT,CCW,power) #오른쪽 모터를 반시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
driveMotor(MOTOR_RIGHT,CCW,power) #왼쪽 모터를 반시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
def robotStop(): //정지
power = 0 //멈춤으로 속도를 0으로 설정
driveMotor(MOTOR_RIGHT,CW,power) #오른쪽 모터를 시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
driveMotor(MOTOR_LEFT,CW,power) #왼쪽 모터를 시계 방향으로 하고 속도를 파라미터로 받은 power로 설정
def robotControl(colorL,colorR):
if (colorL == BLACK and colorR == BLACK): #왼쪽 센서, 오른쪽 센서 모두 검정색이라면
robotForward(120) #직진
elif(colorL == BLACK and colorR == WHITE): #왼쪽 센서는 검은색, 오른쪽 센서는 흰색이라면
robotLeft(120) #좌회전
time.sleep(0.03) #0.03초 동안
elif(colorL == WHITE and colorR == BLACK): #왼쪽 센서는 흰색, 오른쪽 센서는 검정색이라면
robotRight(120) #우회전
time.sleep(0.03) #0.03초 동안
else: #왼쪽 센서, 오른쪽 센서 모두 흰색이라면
robotStop() #로봇을 멈춤
time.sleep(1) #1초동안
robotForward(120) #선을 찾기 위해 직진
time.sleep(0.5) #0.5초 동안
setRightandLeftMotors() #오른쪽 모터와 왼쪽 모터 설정
while True:
data = board.get_sonar_data() #초음파센서로 받은 값을 data에 넣기
distance = data[trig] #data값을 변수 distance에 넣기
realdistance = distance[1] #장애물을 만나자마자 반응하기 위해 distance[1]값으로 장애물과의 거리를 설정
cutdistance = 7 #최소회피거리를 7로 설정
if (realdistance > cutdistance): #앞에 장애물이 없다면
rightIrSensor = readIrSensor(rightIrSensorPin) #오른쪽 초음파센서로 받은 값을 rightIrSensor에 넣기
leftIrSensor = readIrSensor(leftIrSensorPin) #왼쪽 초음파센서로 받은 값을 leftIrSensor에 넣기
colorR = colorFinder(rightIrSensor) #오른쪽 초음파센서의 색 판단
colorL = colorFinder(leftIrSensor) #왼쪽 초음파센서의 색 판딘
robotControl(colorL,colorR) #오른쪽과 왼쪽의 판단된 색으로 로봇 제어
if(realdistance <= cutdistance): #앞에 장애물이 있다면
robotStop() #로봇을 정지
time.sleep(0.5) #0.5초 동안
robotLeft(120) #로봇이 장애물을 피해서 갈 수 있도록 주행방향을 전면에서 왼쪽으로 바꿈
time.sleep(0.6) #0.6초 동안
robotForward(120) #주행방향이 왼쪽으로 바뀐 상태에서 직진
time.sleep(1.3) #1.3초 동안
robotRight(120) #주행방향이 왼쪽으로 바뀐 상태에서 너무 라인에서 멀리 벗어나지 않도록 반대방향인 오른쪽으로 주행방향을 바꿈으로써 로봇이 전면을 보게함
time.sleep(0.75) #0.75초 동안
robotForward(130) #주행방향이 전면이 된 상태에서 앞으로 직진
time.sleep(2.5) #2.5초 동안
robotRight(120) #다시 라인을 찾아가기 위해 주행방향을 라인이 있는 오른쪽으로 바꿈
time.sleep(0.8) #0.8초 동안
robotForward(145) #라인을 찾아가기 위해 주행방향이 오른쪽인 상태로 직진
time.sleep(3.5) #3.5초 동안
