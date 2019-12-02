/* for distance sensor */
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;

void setup() {
  pinMode (led, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(19200);
  AFMS.begin();
  leftMotor->setSpeed(70);
  rightMotor->setSpeed(70);
  fanMotor->setSpeed(40);
  
  Serial.println("Startup");
}

void forward() {
  Serial.print("Moving forward...");
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
  delay(100);
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
  Serial.println("Stopped");
}

void fan() {
  fanMotor->run(FORWARD);
  delay(250);
}

void turnleft() {
  Serial.print("Turning left...");
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
  delay(700);
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
  Serial.println("Stopped");
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 40) {
    turnleft();
    fan();
    digitalWrite (led, LOW);
    digitalWrite (led2, HIGH);
  }
  else {
    forward();
    fan();
    digitalWrite (led, HIGH);
    digitalWrite (led2, LOW);
  }
}
