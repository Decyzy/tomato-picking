//
// Created by dell on 2020/11/3.
//

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <ros/ros.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <cstdio>
#include <tf2/LinearMath/Quaternion.h>

double degree2rad(double degree) {
    return degree / 180.0 * M_PI;
}

int main(int argc, char **argv) {
    // ros::init(argc, argv, "jaka_node");

    ros::init(argc, argv, "static_tf2_broadcaster");
    if (argc != 7) {
        ROS_ERROR(
                "Invalid number of parameters\nusage: static_turtle_tf2_broadcaster child_frame_name x y z roll pitch yaw");
        return -1;
    }
    ROS_INFO("x y z roll pitch yaw (m/degree)");
    static tf2_ros::StaticTransformBroadcaster static_broadcaster;
    geometry_msgs::TransformStamped static_transformStamped;

    static_transformStamped.header.stamp = ros::Time::now();
    static_transformStamped.header.frame_id = "/ns1/base_link";
    static_transformStamped.child_frame_id = "kinect2_link";
    static_transformStamped.transform.translation.x = strtod(argv[1], nullptr);
    static_transformStamped.transform.translation.y = strtod(argv[2], nullptr);
    static_transformStamped.transform.translation.z = strtod(argv[3], nullptr);
    tf2::Quaternion quat;
    quat.setRPY(degree2rad(strtod(argv[4], nullptr)), degree2rad(strtod(argv[5], nullptr)), degree2rad(strtod(argv[6], nullptr)));
    static_transformStamped.transform.rotation.x = quat.x();
    static_transformStamped.transform.rotation.y = quat.y();
    static_transformStamped.transform.rotation.z = quat.z();
    static_transformStamped.transform.rotation.w = quat.w();
    static_broadcaster.sendTransform(static_transformStamped);
//    ROS_INFO("Spinning until killed publishing %s to world", static_turtle_name.c_str());
    ros::spin();
    return 0;

//    JAKAZuRobot robot;
//    char ip_list[1024] = {};
//    errno_t res = robot.get_controller_ip(nullptr, ip_list);
//    sleep(1);
//    std::cout << ip_list << std::endl;
//    JAKAZuRobot robot;

//    ros::NodeHandle jointPubNode;
////    jointPublisherNode.pu
//    ros::Publisher jointPub = jointPubNode.advertise<sensor_msgs::JointState>("jaka_joint_states", 1);
//    ros::Rate loopRate(100);
//    sensor_msgs::JointState j;
//    j.name.resize(6);
//    j.name[0] = "joint_1";
//    j.name[1] = "joint_2";
//    j.name[2] = "joint_3";
//    j.name[3] = "joint_4";
//    j.name[4] = "joint_5";
//    j.name[5] = "joint_6";
//    j.position.resize(6);
//    int i = 0;
//    while (ros::ok()) {
//        j.header.stamp = ros::Time::now();
//        j.position[0] = float(i++) / 1000;
//        j.position[1] = 1;
//        j.position[2] = 1;
//        j.position[3] = 1;
//        j.position[4] = 1;
//        j.position[5] = 1;
//        ROS_INFO("%d", i);
//        jointPub.publish(j);
//        ros::spinOnce();
//        loopRate.sleep();
//    }
//    return 0;
}