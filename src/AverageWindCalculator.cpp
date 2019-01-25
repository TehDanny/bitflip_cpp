#include "ros/ros.h"
#include "std_msgs/String.h"
#include "bitflip_cpp/WindData.h"

void chatterCallback(const bitflip_cpp::WindData msg)
{
	char dateCharArr[1024];
	strcpy(dateCharArr, msg.date.c_str());

	ROS_INFO("#%i message received. Wind speed: %i km/h, Date: %s.", msg.id, msg.windSpeed, dateCharArr);
	
	if (msg.windSpeed < 2 || msg.windSpeed > 10)
	{
		ROS_WARN("BITFLIP EXCEPTION AT #%i: Data is out of nominal bounds.", msg.id);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "average_wind_calculator");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("wind_data_topic", 1000, chatterCallback);

	ros::spin();

	return 0;
}