//
// Created by dell on 2020/11/8.
//
#include <ros/ros.h>
#include "jaka_robot/robot.hpp"

int main(int argc, char **argv) {
    ros::init(argc, argv, "jaka_robot_node");

    RobotBase *robot;
    if (argc > 1) {
        auto *_robot = new JAKARobot();
        std::string ip(argv[1]);
        _robot->init(ip);
        robot = _robot;
        ROS_INFO("Using real robot: %s", ip.c_str());
    } else {
        auto *_robot = new VirtualRobot();
        ROS_WARN("Using virtual robot");
    }
    ros::NodeHandle nh;

//    nh.getParam("/ip", ip);
    ros::spin();
    return 0;
}