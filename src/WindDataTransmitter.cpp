#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "wind_data_transmitter");

	ros::NodeHandle n;

	ros::Publisher wind_data_topic_pub = n.advertise<std_msgs::String>("wind_data_topic", 1000);

	ros::Rate loop_rate(1);

	// Add a date object here

	srand(time(NULL));

	while (ros::ok()) {
		std_msgs::String msg;

	    std::stringstream ss;
	    ss << rand() % 10 + 2 << " km/h";		// Random number between 2 and 10
	    msg.data = ss.str();

	    wind_data_topic_pub.publish(msg);

	    ROS_INFO("%s", msg.data.c_str());

	    ros::spinOnce();

	    loop_rate.sleep();
	}

	return 0;
}