#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <mclmcrrt.h>
#include <mclcppclass.h>



// 



#ifndef TEMPLATE_H
#define TEMPLATE_H


// From RTC::CameraImage to cv::Mat 
cv::Mat operator>>(const RTC::CameraImage src, cv::Mat& dst);
cv::Mat operator<<(cv::Mat& dst, const RTC::CameraImage src);

// From cv::Mat to RTC::CameraImage
RTC::CameraImage operator>>(const cv::Mat src, RTC::CameraImage& dst);
RTC::CameraImage operator<<(RTC::CameraImage& dst, const cv::Mat src);

// From mwArray to cv::Mat
cv::Mat operator>>(const mwArray src, cv::Mat& dst);
cv::Mat operator<<(cv::Mat& dst, const mwArray src);

// From cv::Mat to mwArray
mwArray operator>>(const cv::Mat src, mwArray& dst);
mwArray operator<<(mwArray& dst, const cv::Mat src);

#endif // TEMPLATE_H
