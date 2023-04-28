// Define pins
const int trigPin1 = 2;
const int echoPin1 = 3;
const int buzzerPin1 = 11;

// Define distance thresholds
const int closeDistance = 20; // in centimeters
const int mediumDistance = 35; // in centimeters
const int farDistance = 50; // in centimeters

// Define sound on/off durations
const int closeOnDuration = 100; // in milliseconds
const int closeOffDuration = 100; // in milliseconds
const int mediumOnDuration = 250; // in milliseconds
const int mediumOffDuration = 250; // in milliseconds
const int farOnDuration = 500; // in milliseconds
const int farOffDuration = 500; // in milliseconds


const int trigPin2 = 4;
const int echoPin2 = 5;
const int buzzerPin2 = 12;
const int thresholdDistance = 12; // in cm
const int vmpothole = 8;


const int LEFT_IR_PIN = 6;    // the pin number of the left IR sensor
const int RIGHT_IR_PIN = 7;   // the pin number of the right IR sensor
const int vmleft = 9;
const int vmright = 10;


const int waterSensorPin = A0; // Analog input pin for the water sensor
const int buzzerPin = 13; // Digital output pin for the buzzer


int sensorPin = A1;    // define the LM393 sensor input pin
int threshold = 900;   // set the threshold for darkness detection

void setup() {
  // Define pin modes
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzzerPin1, OUTPUT);


  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(vmpothole, OUTPUT);


  pinMode(LEFT_IR_PIN, INPUT);   // set left IR pin as input
  pinMode(RIGHT_IR_PIN, INPUT);  // set right IR pin as input
  pinMode(vmleft, OUTPUT);
  pinMode(vmright, OUTPUT);


  // Set up the buzzer as an output
  pinMode(buzzerPin, OUTPUT);


  pinMode(sensorPin, INPUT); // set the sensor pin as input
}

void loop() {
  // Send a pulse to the ultrasonic sensor to start a measurement
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Measure the duration of the echo signal and calculate distance
  long duration1 = pulseIn(echoPin1, HIGH);
  int distance1 = duration1 / 58; // distance in centimeters

  // Sound the buzzer with fixed frequency and on/off durations based on distance
  if (distance1 <= closeDistance) {
    digitalWrite(buzzerPin1, HIGH);
    delay(closeOnDuration);
    digitalWrite(buzzerPin1, LOW);
    delay(closeOffDuration);
  } else if (distance1 <= mediumDistance) {
    digitalWrite(buzzerPin1, HIGH);
    delay(mediumOnDuration);
    digitalWrite(buzzerPin1, LOW);
    delay(mediumOffDuration);
  } else if (distance1 <= farDistance) {
    digitalWrite(buzzerPin1, HIGH);
    delay(farOnDuration);
    digitalWrite(buzzerPin1, LOW);
    delay(farOffDuration);
  } else {
    digitalWrite(buzzerPin1, LOW);
    delay(1000);
  }


  // Measure distance
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2; // convert duration to cm

  // Check for pothole
  if (distance2 >= thresholdDistance) {
    digitalWrite(buzzerPin2, HIGH);
    digitalWrite(vmpothole, HIGH);
    delay(500); // buzz for half a second
  }
  else {
    digitalWrite(buzzerPin2, LOW);
    digitalWrite(vmpothole, LOW);
  }


  int leftIrValue = digitalRead(LEFT_IR_PIN);   // read the left IR sensor value
  int rightIrValue = digitalRead(RIGHT_IR_PIN); // read the right IR sensor value
  
  if (leftIrValue == LOW) { // if obstacle is detected on the left side
    digitalWrite(vmleft, HIGH);
  } else if (rightIrValue == LOW) { // if obstacle is detected on the right side
    digitalWrite(vmright, HIGH);
  } else if (leftIrValue == LOW && rightIrValue == LOW) { // if obstacle is detected on both sides
    digitalWrite(vmleft, HIGH);
    digitalWrite(vmright, HIGH);
  } else { // if no obstacle is detected
    digitalWrite(vmleft, LOW);
    digitalWrite(vmright, LOW);
  }


  // Read the water sensor value
  int waterSensorValue = analogRead(waterSensorPin);

  // If the water sensor value is below a certain threshold, the sensor has detected water
  if (waterSensorValue > 300) {
    // Turn on the buzzer to alert the person
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }


  int sensorValue = analogRead(sensorPin); // read the sensor value
  if (sensorValue < threshold) { // if the value is below the threshold, it's dark
    digitalWrite(buzzerPin, LOW); // turn on the buzzer
  } else { // otherwise, it's light
    digitalWrite(buzzerPin, HIGH); // turn off the buzzer
  }
}
