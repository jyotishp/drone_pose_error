#include <iostream>
#include <algorithm>
#include <vector>
#include <ros/ros.h>
#include <apriltags_ros/AprilTagDetectionArray.h>
#include <geometry_msgs/Pose.h>

geometry_msgs::Pose initial_pose;

void getPose(const apriltags_ros::AprilTagDetectionArray msg)
{
	if (! msg.detections.empty())
	{
		
		if (msg.detections[0].pose.pose.position.x == msg.detections[0].pose.pose.position.y == msg.detections[0].pose.pose.position.z == msg.detections[0].pose.pose.orientation.x == msg.detections[0].pose.pose.orientation.y == msg.detections[0].pose.pose.orientation.z == msg.detections[0].pose.pose.orientation.w == 0)
			initial_pose = msg.detections[0].pose.pose;

		std::cout << "Position: (" << msg.detections[0].pose.pose.position.x - initial_pose.position.x << ", "
								   << msg.detections[0].pose.pose.position.y - initial_pose.position.y << ", "
								   << msg.detections[0].pose.pose.position.z - initial_pose.position.z << ")" << std::endl;
		std::cout << "Orientation: (" << msg.detections[0].pose.pose.orientation.x - initial_pose.orientation.x << ", "
									  << msg.detections[0].pose.pose.orientation.y - initial_pose.orientation.y << ", "
									  << msg.detections[0].pose.pose.orientation.z - initial_pose.orientation.z << ", "
									  << msg.detections[0].pose.pose.orientation.w - initial_pose.orientation.w << ")" << "\n\n";
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "apriltags");
	ros::NodeHandle nh;
	ros::Subscriber tag_sub = nh.subscribe("tag_detections", 10, getPose);
	ros::spin();
	return 0;
}
