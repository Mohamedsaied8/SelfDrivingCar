//first program
#include <ros/ros.h>

int main(int argc,char ** argv){


//initialize ros
ros::init(argc,argv,"hello_ros");
ros::NodeHandle n1;

ROS_INFO_STREAM("SelfDriving");
return 0;
}

