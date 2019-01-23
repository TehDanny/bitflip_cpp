#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdlib.h>
#include <ctime>
#include "bitflip_cpp/WindData.h"

std::string SimulateDate(int dateCount)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::tm t = {};
	t.tm_year = ltm->tm_year;
    t.tm_mon  = ltm->tm_mon;
    t.tm_mday = ltm->tm_mday;

    t.tm_mday += dateCount;
    std::mktime(&t);

    std::string date = std::to_string(t.tm_year + 1900) + "/" + std::to_string(t.tm_mon + 1) + "/" + std::to_string(t.tm_mday);

    return date;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "wind_data_transmitter");

	ros::NodeHandle n;

	ros::Publisher wind_data_topic_pub = n.advertise<bitflip_cpp::WindData>("wind_data_topic", 1000);

	ros::Rate loop_rate(1);

	srand(time(NULL));
	
	int dateCount = 0;
	int windDataCount = 0;

	while (ros::ok())
	{
		bitflip_cpp::WindData msg;

	    msg.windSpeed = rand() % 9 + 2;
	    msg.date = SimulateDate(dateCount);

	    wind_data_topic_pub.publish(msg);

	    // ROS_INFO("Wind speed: %s, Date: %s", msg.windSpeed, msg.date;
	    // The above line gives errors, so std::cout is used instead

	    std::cout << "Wind speed: " << msg.windSpeed << ", Date: " << msg.date << std::endl;

	    ros::spinOnce();

	    loop_rate.sleep();
	    
	    windDataCount++;
	    
		if (windDataCount == 10)
		{
			windDataCount = 0;
			dateCount++;
		}
	}

	return 0;
}