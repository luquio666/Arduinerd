// Setup the servo motor
#include <Servo.h>
Servo myservo;
int servposnum = 0;
int servpos = 0;

// Setup Motor A (front and rear) pins
int enableA = 1;
int pinA1 = 3;
int pinA2 = 2;

// Setup Motor B (front and rear) pins
int enableB = 6;
int pinB1 = 5;
int pinB2 = 4;

// Setup Ultrasonic Sensor pins
#define trigPin 8
#define echoPin 9

int initialDelay = 5;
int angle = 0;
bool forward = true;
int speed = 50; // 1000 = 1 sec
int stepsize = 5;
int maxAngle = 135;
int minAngle = 45;
int initialAngle = 90;
bool moveHead = false;
int distanceToStopMoving = 80;

void setup() 
{
   // console
   Serial.begin(9600); 
  
   // Configure the pin modes for the Ultrasonic Sensor
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

   // Turn pin into servo driver. Calls pinMode. Returns 0 on failure.
   myservo.attach(7, 500, 2500);
   myservo.write(initialAngle);
   angle = myservo.read();
}

void loop() 
{
  return;
  
  // write distance
  int dist = distance();
  
  ShowDistanceLog(dist);
  
  if(moveHead == false)
  {
    delay(initialDelay * 1000);
    moveHead = true;
  }
  
  if(dist > distanceToStopMoving)
  {
    MoveHead();
  }
  
}

void ShowDistanceLog(int dist)
{
  Serial.print("Distance: ");
  Serial.println(dist);
}

void MoveHead()
{
  delay(speed);
  
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
