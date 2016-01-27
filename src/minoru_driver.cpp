#include <ros/ros.h>
#include "opencv2/opencv.hpp"

using namespace std;

class MinoruDriver
{
  ros::NodeHandle nh_;
  ros::NodeHandle nh_private_;

  int left_dev_idx_, right_dev_idx_;

public:
  MinoruDriver() : nh_private_("~")
  {
    nh_private_.param("left_dev_idx", left_dev_idx_, 0);
    nh_private_.param("right_dev_idx", right_dev_idx_, 1);
  }

  void stream()
  {
    // Open left
    cv::VideoCapture l_cap(left_dev_idx_);
    cv::VideoCapture r_cap(right_dev_idx_);

    if(!l_cap.isOpened())
    {
      ROS_ERROR("Error opening left camera");
      return;
    }
    if(!r_cap.isOpened())
    {
      ROS_WARN("Error opening right camera");
      return;
    }

    // Setup
    l_cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    l_cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    l_cap.set(CV_CAP_PROP_FPS, 15);

    r_cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    r_cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    r_cap.set(CV_CAP_PROP_FPS, 15);

    while(ros::ok())
    {
      cv::Mat l_frame, r_frame;

      // Left frame
      l_cap >> l_frame;

      ros::Duration(0.5).sleep();

      // Right frame
      r_cap >> r_frame;

      ROS_INFO_STREAM("FRAME PROCESSED: " << l_frame.cols << "x" << l_frame.rows << "   |   "  << r_frame.cols << "x" << r_frame.rows);
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return;
  }

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "minoru_driver");
  MinoruDriver node;
  node.stream();
  ros::spin();
  return 0;
}

