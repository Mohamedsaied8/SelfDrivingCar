#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <wiringPi.h>
#define PwmPin 18




void dir_callback(const geometry_msgs::Twist& msg ) {
ROS_INFO_STREAM( " recieved distance =  "<< msg.linear.x << "recieved Angle = "<< msg.angular.z) ;

float mapped_angle =((msg.angular.z/180)*100)+100 ; //duty cycle mapped from milliseconds to scale 2000 ,equavilent to angle needed
pwmWrite(PwmPin , mapped_angle);




}

int main(int argc , char **argv){
setenv("WIRINGPI_GPIOMEM","1",1);
ros::init(argc ,argv,"listener");
ros::NodeHandle nh ;

//cout<<("Starting servo test\n");
  int rc = wiringPiSetupGpio();

  if (rc != 0) {
    //cout<<("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  pinMode(PwmPin, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(192);
  pwmSetRange(2000);

ros::Subscriber sub = nh.subscribe("car_dir" ,1000, &dir_callback);
ros::spin();

}


