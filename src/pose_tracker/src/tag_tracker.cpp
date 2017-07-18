#include <iostream>
#include <algorithm>
#include <vector>
#include <ros/ros.h>
#include <apriltags_ros/AprilTagDetectionArray.h>
#include <apriltags_ros/AprilTagDetection.h>

void printPose(const apriltags_ros::AprilTagDetection tag)
{
    std::cout << "Tag: " << tag.id << std::endl;
    std::cout << "Position: (" << tag.pose.pose.position.x << ", "
                               << tag.pose.pose.position.y << ", "
                               << tag.pose.pose.position.z << ")" << std::endl;
    std::cout << "Orientation: (" << tag.pose.pose.orientation.x << ", "
                                  << tag.pose.pose.orientation.y << ", "
                                  << tag.pose.pose.orientation.z << ", "
                                  << tag.pose.pose.orientation.w << ")" << "\n\n";
}

void getPose(const apriltags_ros::AprilTagDetectionArray msg)
{
    for_each (msg.detections.begin(), msg.detections.end(), printPose);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "apriltags");
    ros::NodeHandle nh;
    ros::Subscriber tag_sub = nh.subscribe("tag_detections", 10, getPose);
    ros::spin();
    return 0;
}
