#include <SoftwareSerial.h>



int blueRx = 4;

int blueTx = 5;

unsigned char commandReadyFlag = 0;

unsigned char command, power;

SoftwareSerial mySerial(blueRx,blueTx);



#define BLACK 0

#define WHITE 1

 

#define CW  1 

#define CCW 0   

  

#define MOTOR_LEFT 0

#define MOTOR_RIGHT 1



const byte PWMA = 3;      

const byte PWMB = 11; 

const byte DIRA = 12;   

const byte DIRB = 13;  



int sensor0, sensor1; 

int sensorLeft, sensorRight; 





void setup() {

  Serial.begin(9600);

  mySerial.begin(9600);

  setupArdumoto();     

}



void loop() {



  communication();

    

  if (command == 1)

  {

  readSensors();



  sensorRight = colorFinder(sensor0);

  sensorLeft  = colorFinder(sensor1);



  robotControl(sensorLeft,sensorRight); 

  }

  else

  robotStop();

}

void setupArdumoto()

{

  // All pins should be setup as outputs:

  pinMode(PWMA, OUTPUT);

  pinMode(PWMB, OUTPUT);

  pinMode(DIRA, OUTPUT);

  pinMode(DIRB, OUTPUT);



  digitalWrite(PWMA, LOW);

  digitalWrite(PWMB, LOW);

  digitalWrite(DIRA, LOW);

  digitalWrite(DIRB, LOW);

}



void driveArdumoto(byte motor, byte dir, byte spd)

{

  if(motor == MOTOR_RIGHT)

  {

    digitalWrite(DIRA, dir);

    analogWrite(PWMA, spd);

  }

  else if(motor == MOTOR_LEFT)

  {

    digitalWrite(DIRB, dir);

    analogWrite(PWMB, spd);

  }  

}



void robotForward(int powerLeft, int powerRight)

{

  driveArdumoto(MOTOR_RIGHT,CW,powerRight);

  driveArdumoto(MOTOR_LEFT,CCW,powerRight);

}



void robotBackward(int powerLeft, int powerRight)

{

  driveArdumoto(MOTOR_RIGHT,CCW,powerRight);

  driveArdumoto(MOTOR_LEFT,CW,powerRight);

}



void robotRight(int powerLeft, int powerRight)

{

  driveArdumoto(MOTOR_RIGHT,CCW,powerRight);

  driveArdumoto(MOTOR_LEFT,CCW,powerRight);

}



void robotLeft(int powerLeft, int powerRight)

{

  driveArdumoto(MOTOR_RIGHT,CW,powerRight);

  driveArdumoto(MOTOR_LEFT,CW,powerRight);

}



void robotStop()

{

  stopArdumoto(MOTOR_LEFT);

  stopArdumoto(MOTOR_RIGHT);

}



void stopArdumoto(byte motor)

{

  driveArdumoto(motor, 0, 0);

}



void readSensors(){

  sensor0 = 1023 - analogRead(A0);  // sensor Right

  sensor1 = 1023 - analogRead(A1);  // sensor Left

}



char colorFinder(int sensorValue) {

   char color;

   const int THRESHOLD = 800;

  if(sensorValue > THRESHOLD)

    color = WHITE;

   else

     color = BLACK;

   return color;

}



void robotControl(int sensorLeft, int sensorRight){

  if (sensorLeft == BLACK && sensorRight == BLACK){

      robotForward(100,100);

   

  }

            

   else if (sensorLeft == BLACK && sensorRight == WHITE) {

              robotLeft(100,100);

              delay(30);

    }

   else if (sensorLeft == WHITE && sensorRight == BLACK) {

              robotRight(100,100);

              delay(30);

    }

   else

              robotStop();

 }



void communication(){

  if (mySerial.available() >= 4){

    Serial.println("data arrived ");

    unsigned char buffer[4];



    for (char i=0; i<4; i++){

      buffer[i] = mySerial.read();

    }

    

    if ( buffer[0]== 255 && buffer[3] == 100) {

         command = buffer[1];

         power = buffer[2];   



         Serial.print("command:");

         Serial.println(command);

          Serial.print("power:");

         Serial.println(power);

    }    

  }

}
