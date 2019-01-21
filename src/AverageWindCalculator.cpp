#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s] km/h", msg->data.c_str());
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "average_wind_calculator");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("wind_data_topic", 1000, chatterCallback);

	ros::spin();

	return 0;
}