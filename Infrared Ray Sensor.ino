int sensorValue0 = 0;

int sensorValue1 = 0;

void setup() {

  Serial.begin(9600); 

}

void loop() {

 sensorValue0 = analogRead(A0);

  sensorValue1 = analogRead(A1);

  delay(100);

  Serial.print("A0:");

  Serial.println(sensorValue0);

  Serial.print("A1:");

  Serial.println(sensorValue1);

}
