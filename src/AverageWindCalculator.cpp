#include "ros/ros.h"
#include "std_msgs/String.h"
#include "bitflip_cpp/WindData.h"

void chatterCallback(const bitflip_cpp::WindData msg)
{
	// ROS_INFO("Message received. Wind speed: [%s], Date: [%s]", msg->windSpeed.c_str(), msg->date.c_str());
	// The above line gives errors, so std::cout is used instead
	
	std::cout << "#" << msg.id << " message received. Wind speed: " << msg.windSpeed << "km/h, Date: " << msg.date << std::endl;
	
	if (msg.windSpeed < 2 || msg.windSpeed > 10)
	{
		std::cout << "\033[1;31mBITFLIP EXCEPTION: Data is out of nominal bounds.\033[0m" << std::endl;
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