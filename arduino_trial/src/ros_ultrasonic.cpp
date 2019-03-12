#include "ros/ros.h"
#include "arduino_trial/ultrasonic.h"
#include <sstream> // can del


int main(int argc, char **argv)
{
ros::init(argc, argv, "ultrasonic_send");
ros::NodeHandle n;
ros::Publisher pub= n.advertise<arduino_trial::ultrasonic>("ultrasonic", 1000);
ros::Rate loop_rate(1); //Hz
int count = 0;
 while (ros::ok())
{
arduino_trial::ultrasonic reading;
reading.distance.clear();
reading.distance.resize(5);
reading.distance[0]=5.33;
reading.distance[1]=6.55;
//std::cout << reading.distance[0] << std::endl;
//ROS_INFO("msg sent");
pub.publish(reading);
ros::spinOnce();
loop_rate.sleep();
++count;
}
return 0;
}