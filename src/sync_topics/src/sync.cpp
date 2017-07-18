#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <camera_calibration_parsers/parse.h>

using namespace sensor_msgs;
using namespace message_filters;

ros::Publisher info_left_pub, info_right_pub, image_left_pub, image_right_pub;

void callback(const ImageConstPtr& image_left, const ImageConstPtr& image_right)
{
	const std::string left_info_path = "data/left_camera.yml";
	const std::string right_info_path = "data/right_camera.yml";
	CameraInfo left_info, right_info;
	std::string left_camera_name, right_camera_name;
	Image new_left, new_right;

	bool left = camera_calibration_parsers::readCalibration(left_info_path, left_camera_name, left_info);
	bool right = camera_calibration_parsers::readCalibration(right_info_path, right_camera_name, right_info);

	std_msgs::Header header;
	header.stamp = ros::Time::now();

	left_info.header = header;
	right_info.header = header;

	// memcpy(&new_left, image_left, sizeof(image_left));
	// memcpy(&new_right, image_right, sizeof(image_right));
	new_left.height = image_left->height;
	new_left.width = image_left->width;
	new_left.encoding = image_left->encoding;
	new_left.is_bigendian = image_left->is_bigendian;
	new_left.step = image_left->step;
	new_left.data = image_left->data;

	new_right.height = image_right->height;
	new_right.width = image_right->width;
	new_right.encoding = image_right->encoding;
	new_right.is_bigendian = image_right->is_bigendian;
	new_right.step = image_right->step;
	new_right.data = image_right->data;

	new_left.header = header;
	new_right.header = header;

	info_left_pub.publish(left_info);
	info_right_pub.publish(right_info);
	image_left_pub.publish(new_left);
	image_right_pub.publish(new_right);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "sync");

	ros::NodeHandle nh;
	ros::NodeHandle pub;

	info_left_pub = pub.advertise<CameraInfo>("/sync/left/camera_info", 10);
	image_left_pub = pub.advertise<Image>("/sync/left/image_raw", 10);
	info_right_pub = pub.advertise<CameraInfo>("/sync/right/camera_info", 10);
	image_right_pub = pub.advertise<Image>("/sync/right/image_raw", 10);

	message_filters::Subscriber<Image> image_left_sub(nh, "left_rgb/image", 1);
	message_filters::Subscriber<Image> image_right_sub(nh, "right_rgb/image", 1);

	typedef sync_policies::ApproximateTime<Image, Image> stereoSync;
	Synchronizer<stereoSync> sync(stereoSync(10), image_left_sub, image_right_sub);
	sync.registerCallback(boost::bind(&callback, _1, _2));

	ros::spin();

	return 0;
}