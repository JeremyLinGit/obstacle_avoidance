#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>
#include <stdlib.h>

float min_range,min_range_angle;

ros::Publisher vel_pub;
geometry_msgs::Twist cmdvel;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
 // printf("Position: [%f] [%f]\n", msg->range_min,msg->range_max);
	min_range=msg->ranges[0];
	min_range_angle=0;
	srand(time(0));
	//printf(" ranges[0] = %f\n",min_range);
	for(int j=0;j<360;j++) //increment by one degree
		{
			
			if(msg->ranges[j]<min_range)
			{
				min_range=msg->ranges[j];
				min_range_angle=j;
			}
			//printf("%f ,  %f  ",msg->ranges[j],min_range_angle=j);
		}
		printf("minimum range is [%f] at an angle of [%f]\n",min_range,min_range_angle);
	if(min_range<=0.4 && min_range_angle<90)  // min_range<=0.5 gave box pushing like behaviour, min_range<=1.2 gave obstacle avoidance
	{
		cmdvel.angular.z=-0.4;
		cmdvel.linear.x=0;
		printf("right\n");
	}
	else if(min_range<=0.3 && min_range_angle>270)
	{
		cmdvel.angular.z=0.4;
		cmdvel.linear.x=0;
		printf("left\n");
	}
	else
	{	
		//cmdvel.linear.x=0.5;
		//cmdvel.angular.z= 0;
		cmdvel.linear.x= 0.5*double(rand())/double(RAND_MAX);
		cmdvel.angular.z= 0.5*double(rand())/double(RAND_MAX);
		printf("random walk\n");
	}
	 
	 vel_pub.publish(cmdvel);

}
int main( int argc, char** argv){
	ros::init(argc, argv, "viewlaserscan");
	ros::NodeHandle n;
  	ros::NodeHandle nh;

	vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
	srand(time(0));
	ros::Rate rate(2);
	cmdvel.linear.x=0;
	cmdvel.linear.y=0;
	cmdvel.linear.z=0;
	cmdvel.angular.x=0;
	cmdvel.angular.y=0;
	cmdvel.angular.z=0; 
	ros::Subscriber sub = n.subscribe("/scan", 10, scanCallback);
	ros::spin();
	return 0;
}
