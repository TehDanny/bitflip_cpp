#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <stdlib.h>
#include <ctime>

int main(int argc, char **argv) {
	ros::init(argc, argv, "wind_data_transmitter");

	ros::NodeHandle n;

	ros::Publisher wind_data_topic_pub = n.advertise<std_msgs::String>("wind_data_topic", 1000);

	ros::Rate loop_rate(1);

	srand(time(NULL));

	time_t now = time(0);
	

	while (ros::ok()) {
		std_msgs::String msg;

	    std::stringstream ss;

	    int windSpeed = rand() % 9 + 2;
	    tm *ltm = localtime(&now);
	    std::string formatedDate = std::to_string(ltm->tm_mday) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(1900 + ltm->tm_year);

	    ss << windSpeed << " " << formatedDate;
	    msg.data = ss.str();

	    wind_data_topic_pub.publish(msg);

	    ROS_INFO("%s", msg.data.c_str());

	    ros::spinOnce();

	    loop_rate.sleep();
	}

	return 0;
}