int sensorValue0=0;

int sum = 0;

int average = 0;

void setup() {

  Serial.begin(9600);

}

void loop() {

  int sensorValue0=analogRead(A0);

  if (true) {

    for (int i =0; i<5; i++) {

      sum = sum + sensorValue0;

    }

    average = sum / 5;

    sum = 0;

    Serial.print(" :");

    Serial.println(average);

    }

  }
