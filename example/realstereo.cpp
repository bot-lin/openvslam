#include "realstereo.h"

realstereo::realstereo():rows(800),cols(848),fisheye_left_idx(1),fisheye_right_idx(2)
{
    frame_left = cv::Mat::zeros(800,848,CV_8UC1);
    frame_right = cv::Mat::zeros(800,848,CV_8UC1);
    b_Open = false;
}

void realstereo::open()
{
    // Enable fisheye and pose streams
    //cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
    cfg.enable_stream(RS2_STREAM_FISHEYE, 1);
    cfg.enable_stream(RS2_STREAM_FISHEYE, 2);
    // Start pipeline with chosen configuration
    rs2::pipeline_profile pipe_profile = pipe.start(cfg);

    b_Open = true;

    std::cout <<"DEVICE FOUND AND OPENED...."<<std::endl;
}

bool realstereo::IsOpen()
{
    return b_Open;
}

bool realstereo::read_stereo_frames(cv::Mat & cvframe_left, cv::Mat & cvframe_right)
{
    {
        // Wait for the next set of frames from the camera
        auto rs_frames = pipe.wait_for_frames(5000);

        // Get a frame from the fisheye stream
        rs2::video_frame fisheye_frame_left = rs_frames.get_fisheye_frame(fisheye_left_idx);
        rs2::video_frame fisheye_frame_right = rs_frames.get_fisheye_frame(fisheye_right_idx);

        // rs frame to opencv frame
        cvframe_left = cv::Mat(cv::Size(cols,rows), CV_8UC1, (void*)fisheye_frame_left.get_data(), cv::Mat::AUTO_STEP);
        cvframe_right = cv::Mat(cv::Size(cols,rows), CV_8UC1, (void*)fisheye_frame_right.get_data(), cv::Mat::AUTO_STEP);

        // By closing the current scope we let frames be deallocated, so we do not fill up librealsense queues while we do other computation.
    }

    if(!cvframe_left.empty() && !cvframe_right.empty())
        return true;
    else
        return false;
}


