// Setup Ultrasonic Sensor pins
#define trigPin 8
#define echoPin 9
#define piezoPin 12

#include <Servo.h>
Servo myservo;

void setup() {
  
   Serial.begin(9600); 
   // Configure the pin modes for the Ultrasonic Sensor
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

   // Turn pin into servo driver. Calls pinMode. Returns 0 on failure.
   myservo.attach(7, 500, 2500);
   myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  //DistanceSound();
  /*int dist = distance();
  if(dist < 50)
  {
    MoveHeadFast();
  }
  if(dist < 10)
  {
    alarm();
  }*/
}

void DistanceSound()
{
  int dist = distance();
  
  if(dist > 30)
    return;

  tone(piezoPin, 3000, 50);
  delay(10 * dist);
  Serial.println(dist);
}

int angle = 0;
int headSpeed = 50;
bool forward = true;
int stepsize = 10;
int maxAngle = 135;
int minAngle = 45;
void MoveHeadFast()
{
  delay(headSpeed);
  
  if(forward == true)
    angle = angle + stepsize;
  if(forward == false)
    angle = angle - stepsize;
    
  if(angle > maxAngle)
  {
    angle = maxAngle;
    forward = false;
  }
  if(angle <= minAngle)
  {
    angle = minAngle;
    forward = true;
  }
  myservo.write(angle);
}

// Setup Ultrasonic Sensor distance measuring
int distance() {
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if(distance < 0)
    distance = distance * -1;
  return distance;
}

//------------------------------------- MORSE CODE -------------------------------------//

int note = 2500;
int mShort = 50;

void alarm()
{
  int mLong = mShort * 3;
  
  int delayBetweenNotes = mShort * 1;
  int delayBetweenLeters = mShort * 3;
  int delayBetweenWords = mShort * 7;

  Serial.println("P");
  
  // P
  tone(piezoPin, note, mShort);
  delay(delayBetweenNotes + mShort);
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);
  tone(piezoPin, note, mShort);
  delay(delayBetweenNotes + mShort);

  // letter pause
  delay(delayBetweenLeters);

  Serial.println("U");

  // U
  tone(piezoPin, note, mShort);
  delay(delayBetweenNotes + mShort);
  tone(piezoPin, note, mShort);
  delay(delayBetweenNotes + mShort);
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);

  // letter pause
  delay(delayBetweenLeters);

  Serial.println("T");

  // T
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);

  // letter pause
  delay(delayBetweenLeters);

  Serial.println("O");
  
  // O
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);
  tone(piezoPin, note, mLong);
  delay(delayBetweenNotes + mLong);

  // letter pause
  delay(delayBetweenLeters);

  // word pause
  delay(delayBetweenWords);

}
