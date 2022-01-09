#include <Ultrasonic.h> //초음파센서
#include <SoftwareSerial.h> //블루투스
int blueRx = 4; //블루투스 연결기 핀 설정
int blueTx = 5; //블루투스 연결기
char trig = 9; //초음파센서 핀 설정
char echo = 8; //초음파센서 핀 설정
unsigned char commandReadyFlag = 0;
unsigned char command, power; //블루투스로 받는 값을 받기 위한 변수
SoftwareSerial mySerial(blueRx,blueTx); ///블루투스 핀으로 블루투스 연결 실행
Ultrasonic ultrasonic(trig,echo); //초음파센서 핀으로 초음파센서 실행
int distance; //초음파센서로 거리를 받기 위한 distance 변수 생성
#define BLACK 0 //BLACK을 0으로 설정
#define WHITE 1 //WHITE를 1로 설정
#define CW 1 //시계방향 CW를 1로 설정
#define CCW 0 //반시계방향 CCW를 0으로 설정
#define MOTOR_LEFT 0 //왼쪽 모터를 0으로 설정
#define MOTOR_RIGHT 1 //오른쪽 모터를 1로 설정
const byte PWMA = 3; //모터의 힘을 설정하기 위한 핀 설정
const byte PWMB = 11; //모터의 힘을 설정하기 위한 핀 설정
const byte DIRA = 12; //모터의 방향을 설정하기 위한 핀 설정
const byte DIRB = 13; //모터의 방향을 설정하기 위한 핀 설정
int sensor0, sensor1; //적외선센서로 받은 값을 받기 위한 변수 sensor0, sensor1 생성
int sensorLeft, sensorRight; //왼쪽 적외선센서 값을 받기 위한 변수 sensorLeft, 오른쪽 적외선센서 값을 받기 위한 변수 sensorRight 생성
void setup() {
Serial.begin(9600); //시리얼통신 속도를 9600으로 설정
mySerial.begin(9600); //블루투스 통신 속도를 9600으로 설정
setupArdumoto(); //setupArdumoto 함수 실행
}
void loop() {
int cutDistance = 5; //최소회피거리를 5로 설정
communication(); //블루투스 연결
ultra(); //초음파센서로 거리 값 받기
if (command == 1) //블루투스로 값이 들어오면
{
if (distance > cutDistance){ //앞에 장애물이 없으면
readSensors(); //적외선센서로 값 입력받기
sensorRight = colorFinder(sensor1); //입력받은 값으로 검은색인지 흰색인지 판단
sensorLeft = colorFinder(sensor0); //입력받은 값으로 검은색인지 흰색인지 판단
robotControl(sensorLeft,sensorRight); //입력받은 색으로 로봇 제어
}
if (distance <= cutDistance) { //앞에 장애물이 있다면
robotStop(); //로봇을 잠시 멈춤
delay(1000); //1초 동안
robotLeft(100,100); //로봇이 장애물을 피해서 갈 수 있도록 주행방향을 전면에서 왼쪽으로 바꿈
delay(300); //0.3초 동안
robotForward(100,100); //주행방향이 왼쪽으로 바뀐 상태에서 직진
delay(1000); //1초동안
robotRight(100,100); //주행방향이 왼쪽으로 바뀐 상태에서 너무 라인에서 멀리 벗어나지 않도록 반대방향인 오른쪽으로 주행방향을 바꿈으로써 로봇이 전면을 보게함
delay(350); //0.35초 동안
robotForward(110,110); //주행방향이 전면이 된 상태에서 앞으로 직진
delay(1000); //1초 동안
robotRight(100,100); //다시 라인을 찾아가기 위해 주행방향을 라인이 있는 오른쪽으로 바꿈
delay(350); //0.35초 동안
robotForward(110,110); //라인을 찾아가기 위해 주행방향이 오른쪽인 상태로 직진
delay(1000); //1초 동안
}
}
}
void ultra() { //ultra 함수 생성
distance = ultrasonic.read(); //초음파센서로 읽은 값을 변수 distance에 넣기
}
void setupArdumoto() //setupArdumoto 함수 생성
{
pinMode(PWMA, OUTPUT); //PWMA를 OUTPUT로 설정
pinMode(PWMB, OUTPUT); //PWMB를 OUTPUT로 설정
pinMode(DIRA, OUTPUT); //DIRA를 OUTPUT로 설정
pinMode(DIRB, OUTPUT); //DIRB를 OUTPUR로 설정
digitalWrite(PWMA, LOW); //PWMA를 LOW로 설정
digitalWrite(PWMB, LOW); //PWMB를 LOW로 설정
digitalWrite(DIRA, LOW); //DIRA를 LOW로 설정
digitalWrite(DIRB, LOW); //DIRB를 LOW로 설정
}
void driveArdumoto(byte motor, byte dir, byte spd) //모터,방향,속도를 파라미터로 받는 driveArdumoto 함수 생성
{
if(motor == MOTOR_RIGHT) //오른쪽 모터
{
digitalWrite(DIRA, dir); //방향을 파라미터로 받는 dir로 설정
analogWrite(PWMA, spd); //속도를 파라미터로 받는 spd로 설정
}
else if(motor == MOTOR_LEFT) //왼쪽 모터
{
digitalWrite(DIRB, dir); //방향을 파라미터로 받는 dir로 설정
analogWrite(PWMB, spd); //속도를 파라미터로 받는 spd로 설정
}
}
void robotForward(int powerLeft, int powerRight) //로봇을 직진하게 하는 함수 생성
{
driveArdumoto(MOTOR_RIGHT,CCW,powerRight); //오른쪽 모터를 반시계방향으로 하고, 속도는 파라미터로 받는 powerRight로 함
driveArdumoto(MOTOR_LEFT,CW,powerLeft); //왼쪽 모터를 시계방향으로 하고, 속도는 파라미터로 받는 powerLeft로 함
}
void robotBackward(int powerLeft, int powerRight) //로봇을 후진하게 하는 함수 생성
{
driveArdumoto(MOTOR_RIGHT,CW,powerRight); //오른쪽 모터를 시계방향으로 하고, 속도는 파라미터로 받는 powerRight로 함
driveArdumoto(MOTOR_LEFT,CCW,powerLeft); //왼쪽 모터를 반시계방향으로 하고, 속도는 파라미터로 받는 powerLeft로 함
}
void robotRight(int powerLeft, int powerRight) //로봇을 우회전하기 위한 함수 생성
{
driveArdumoto(MOTOR_RIGHT,CW,powerRight); //오른쪽 모터를 시계방향으로 하고, 속도는 파라미터로 받는 powerRight로 함
driveArdumoto(MOTOR_LEFT,CW,powerLeft); //왼쪽 모터를 시계방향으로 하고, 속도는 파라미터로 받는 powerLeft로 함
}
void robotLeft(int powerLeft, int powerRight) //로봇을 좌회전하기 위한 함수 생성
{
driveArdumoto(MOTOR_RIGHT,CCW,powerRight); //오른쪽 모터를 반시계방향으로 하고, 속도는 파라미터로 받는 powerRight로 함
driveArdumoto(MOTOR_LEFT,CCW,powerLeft); //왼쪽 모터를 반시계방향으로 하고, 속도는 파라미터로 받는 powerLeft로 함
}
void robotStop()//로봇을 멈추는 함수 생성
{
stopArdumoto(MOTOR_LEFT); //움직이지 않으므로 방향과 속도 값을 받지 않음
stopArdumoto(MOTOR_RIGHT); //움직이지 않으므로 방향과 속도 값을 받지 않음
}
void stopArdumoto(byte motor) //로봇을 멈추는 함수 생성
{
driveArdumoto(motor, 0, 0); //움직이지 않으므로 속도를 0으로 설정
}
void readSensors(){
sensor0 = 1023 - analogRead(A0); //아날로그핀 A0으로 받은 값을 1023에 뺀 값으로 sensor0을 설정
sensor1 = 1023 - analogRead(A1); //아날로그핀 A1으로 받은 값을 1023에 뺀 값으로 sensor1을 설정
}
char colorFinder(int sensorValue) { //적외선센서로 입력 받은 값을 색을 판단하기 위한 coloFinder 함수 생성
char color; //color 함수 생성
const int THRESHOLD = 800; //흰색인지 검은색인지 판단하기 위한 기준 값을 800으로 설정
if(sensorValue > THRESHOLD) //파라미터로 받은 sensorValue의 값이 기준값 보다 높다면
color = WHITE; //하얀색으로 판단
else //파라미터로 받은 sensorValue의 값이 기준값 보다 낮다면
color = BLACK; //검정색으로 판단
return color; //받은 값을 반환
}
void robotControl(int sensorLeft, int sensorRight){ //로봇을 제어하기 위한 함수
if (sensorLeft == BLACK && sensorRight == BLACK){ //왼쪽 센서, 오른쪽 센서 모두 검정색이라면
robotForward(100,100); //직진
}
else if (sensorLeft == BLACK && sensorRight == WHITE) { //왼쪽 센서는 검은색, 오른쪽 센서는 흰색이라면
robotLeft(100,100); //오른쪽은 선이 없음으로 좌회전
delay(30); //0.03초 동안
}
else if (sensorLeft == WHITE && sensorRight == BLACK) { //왼쪽 센서는 흰색이고, 오른쪽 센서는 검은색이라면
robotRight(100,100); //왼쪽은 선이 없음으로 우회전
delay(30); //0.03초 동안
}
else //왼쪽 센서, 오른쪽 센서 모두 흰색이라면
robotStop(); //선이 없음으로 멈춤
delay(1000); //1초동안
robotForward(100,100); //선을 찾기 위해 로봇을 직진
delay(500); //0.5초 동안
}
//블루투스 통신하기 위한 함수 communication 생성
void communication(){
if (mySerial.available() >= 4){ //블루투스로 값을 입력 받으면
Serial.println("data arrived "); //값을 입력 받았다는 문구 출력
unsigned char buffer[4]; //buffer 배열 생성
for (char i=0; i<4; i++){
buffer[i] = mySerial.read(); //입력받은 값을 buffer 배열에 넣기
}
if ( buffer[0]== 255 && buffer[3] == 100) {
command = buffer[1]; //변수 command를 buffer 배열의 인덱스 값으로 설정
power = buffer[2]; //변수 power를 buffer 배열의 인덱스 값으로 설정
}
}
}
