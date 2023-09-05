#include <iostream>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"


void scan_callback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    /* 
    This callback is triggered each time a message is received 
    on the /scan topic. The message data is availble in the 
    form of a pointer, and the fields are defined in 
    "sensor_msgs/LaserScan"

    This callback is designed to find the largest value in the
    "ranges" feild and print the max value to the terminal 
    */

    float largest = 0.0;
    int numberOfElements = msg->ranges.size();

    for (int i = 0; i < numberOfElements; i++) {
        if (msg->ranges[i] > largest && msg->ranges[i] < 1000) { //Want values less than 1000 to avoid "inf" values
            largest = msg->ranges[i];
        }
    }

    std::cout << "Largest Value is: " << largest << std::endl;
}

int main(int argc, char **argv) {
    
    //Initialize ROS node with default name: max value
    ros::init(argc, argv, "max_value");

    //Create a NodeHandle object called nh
    ros::NodeHandle nh;
    
    /* Create a ros subscriber object attached to our node, nh
    There are many different parameters to a subscriber object
    the arguments are: 
    topic name: /scan
    buffer queue size: 1000 messages
    callback to execute: scan_callback
    */
    ros::Subscriber scan_sub = nh.subscribe("/scan", 1000, scan_callback);

    ros::spin();


    return 0;
}
