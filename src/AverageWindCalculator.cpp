#include "ros/ros.h"
#include "std_msgs/String.h"
#include "bitflip_cpp/WindData.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Message received: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "average_wind_calculator");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("wind_data_topic", 1000, chatterCallback);

	ros::spin();

	return 0;
}