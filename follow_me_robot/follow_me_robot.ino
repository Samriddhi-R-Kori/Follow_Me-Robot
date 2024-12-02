#include <Servo.h>

Servo servo;
int servoP = 10;

int ena = 9;
int m1p1 = 4;
int m1p2 = 5;

int enb = 8;
int m2p1 = 6;
int m2p2 = 7;

int r = A3;
int l = A2;
int  rv, lv;

int trigPin = 11;
int echoPin = 12;
long duration;
int d;


void setup()
{
  servo.attach(servoP);
  servo.write(0);
  Serial.begin(9600);

  pinMode(r, INPUT);
  pinMode(l, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  d = duration * 0.034 / 2;
  
  Serial.print("d=");
  Serial.println(d);

  rv = digitalRead(r);
  lv = digitalRead(l);
  Serial.print("right=");
  Serial.print(r);
  Serial.print("   left=");
  Serial.println(l);

  if((rv==1) && (d>=10 && d<=30) &&(lv==1))
  {
    Serial.println("forward");
      digitalWrite(m1p1, HIGH);
      digitalWrite(m1p2, LOW);
      digitalWrite(m2p1, LOW);
      digitalWrite(m2p2, HIGH);
      analogWrite(ena, 255);
      analogWrite(enb, 255);
  }
  else if ((rv==0) && (lv==1))
  {
     Serial.println("right");
      digitalWrite(m1p1, LOW);
      digitalWrite(m1p2, HIGH);
      digitalWrite(m2p1, LOW);
      digitalWrite(m2p2, LOW);
      analogWrite(ena, 255);
      analogWrite(enb, 0);
  }
  else if ((rv==1) && (lv==0))
  {
    Serial.println("left");
      digitalWrite(m1p1, LOW);
      digitalWrite(m1p2, LOW);
      digitalWrite(m2p1, HIGH);
      digitalWrite(m2p2, LOW);
      analogWrite(ena, 0);
      analogWrite(enb, 255);
  }
  else if((rv==1)&&(lv==1) || (d>1&&d<10))
  {
     Serial.println("Stop");
      digitalWrite(m1p1, LOW);
      digitalWrite(m1p2, LOW);
      digitalWrite(m2p1, LOW);
      digitalWrite(m2p2, LOW);
      analogWrite(ena, 0);
      analogWrite(enb, 0);
  }
}
