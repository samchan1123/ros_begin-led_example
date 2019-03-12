#!/usr/bin/env python
import rospy
from arduino_trial.msg import ledmsg
from arduino_trial.msg import ultrasonic
 
 #initialize node, topic and msg
brightness=ledmsg()
rospy.init_node('led_control', anonymous=True)
pub=rospy.Publisher('led_brightness',ledmsg,queue_size=10)
rate=rospy.Rate(1000)

#initiaize parameter
distance=0

#calculate the brightness of led
def cal_brightness(distance):
    brightness.led=[distance*6]
    #set the range
    brightness.led[0]=min(255,max(0,brightness.led[0]))
    rospy.loginfo('brightness: %Lf',brightness.led[0])

#obtain data -> processing -> publish 
def led_control (ultrasonic):
#pbtain data
    global distance 
    distance = ultrasonic.distance[0]
#processing
    cal_brightness(distance)
    rospy.loginfo('%Lf',distance)
#publish
    pub.publish(brightness)

#subscibe topic and response for topic
def send_brightness():
    rospy.Subscriber('distance', ultrasonic, led_control)
        
  
if __name__=='__main__':
    try:
        send_brightness()
        rate.sleep()  
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
