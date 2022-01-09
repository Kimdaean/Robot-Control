const unsigned int TRIG_PIN=9;

const unsigned int ECHO_PIN=8;

#define CW 1

#define CCW 0

#define MOTOR_LEFT 0

#define MOTOR_RIGHT 1

const byte PWMA =3;

const byte DIRA =12;

const byte PWMB =11;

const byte DIRB =13;

void setup() {

  pinMode(PWMA, OUTPUT);

  pinMode(PWMB, OUTPUT);

  pinMode(DIRA, OUTPUT);

  pinMode(DIRB, OUTPUT);

  digitalWrite(PWMA,LOW);

  digitalWrite(PWMB,LOW);

  digitalWrite(DIRA,LOW);

  digitalWrite(DIRB,LOW);

  pinMode(TRIG_PIN, OUTPUT);

  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);

}

void loop() {

  robotForward(90);

   digitalWrite(TRIG_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

const unsigned long duration = pulseIn(ECHO_PIN, HIGH);

int distance = duration/29/2;

  if (distance <= 20){

    robotStop();

    delay(5000);

  }

}

  void robotForward(unsigned char velocity)

  {

    driveARdumoto(MOTOR_RIGHT,CW,velocity);

    driveARdumoto(MOTOR_LEFT,CCW,velocity);

  }

  void robotStop() {

    driveARdumoto(MOTOR_RIGHT,CW,0);

    driveARdumoto(MOTOR_LEFT,CW,0);

  }

  void driveARdumoto(byte motor, byte dir, byte spd) {

    if(motor == MOTOR_LEFT) {

      digitalWrite(DIRA, dir);

      analogWrite(PWMA, spd);

    }

    else if (motor == MOTOR_RIGHT)

    {

      digitalWrite(DIRB, dir);

      analogWrite(PWMB, spd);

    }

  }
