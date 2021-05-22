#ifndef REALSTEREO_H
#define REALSTEREO_H

#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

class realstereo
{
public:
    realstereo();
    void open();
    bool IsOpen();
    bool read_stereo_frames(cv::Mat&, cv::Mat&);
    void displayCameras();

    cv::Mat frame_left, frame_right;
    bool b_Open;
    const int rows, cols;
    // T265 has two fisheye sensors, we can choose any of them (index 1 or 2)
    const int fisheye_left_idx; //FOR LEFT
    const int fisheye_right_idx; //FOR RIGHT

    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;
};

#endif // REALSTEREO_H
