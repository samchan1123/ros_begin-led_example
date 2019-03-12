#include <ros.h>
#include <arduino_trial/ultrasonic.h>
#include <arduino_trial/ledmsg.h>

#define led_pin 6
#define trig 30
#define echo 31

ros::NodeHandle nh;
arduino_trial::ultrasonic ultrasonic;
ros::Publisher p("distance", &ultrasonic);

void messageCb( const arduino_trial::ledmsg& msg)
{
  int brightness= msg.led[0];
  analogWrite(led_pin,brightness);// blink the led
}

ros::Subscriber<arduino_trial::ledmsg> s("led_brightness", &messageCb);

float distance_cal()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  float distance = pulseIn(echo,HIGH,960000);
  distance=distance/58;
  if (distance<5 || distance>60)
  {
    distance=0;
  }
  return distance;
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT_PULLUP);
  nh.initNode();
  ultrasonic.distance_length=1;
  ultrasonic.distance=new float;
  nh.advertise(p);
  nh.subscribe(s);
 // Serial.begin(9600);
}

void loop()
{
  ultrasonic.distance[0]=distance_cal();
  Serial.println(distance_cal());
  p.publish(&ultrasonic);
  nh.spinOnce();
  delay(10);
}
