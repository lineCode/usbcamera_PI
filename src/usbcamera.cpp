// -*- C++ -*-
/*!
 * @file  usbcamera.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "usbcamera.h"
using namespace std;
// Module specification
// <rtc-template block="module_spec">
static const char* usbcamera_spec[] =
  {
    "implementation_id", "usbcamera",
    "type_name",         "usbcamera",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "kazuki urabe",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.viewer", "0:OFF",
    // Widget
    "conf.__widget__.viewer", "radio",
    // Constraints
    "conf.__constraints__.viewer", "(1:ON,0:OFF)",
    ""
  };
// </rtc-template>//

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
usbcamera::usbcamera(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inputIn("input", m_input),
    m_outputOut("output", m_output)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
usbcamera::~usbcamera()
{
}
//
/*
//m_input>>inputFrame;
cv::Mat operator>>(const RTC::CameraImage src, cv::Mat& dst)
{
	if(dst.empty())
		dst.create(cvSize(src.width,src.height),src.bpp);
	if(dst.size().height != src.height || dst.size().width != src.width || dst.type() != src.bpp || dst.size().height * dst.size().width * dst.elemSize() != (int)src.pixels.length())
	{
    dst.release();
		dst.create(cvSize(src.width,src.height),src.bpp);
	}
	memcpy(dst.data,(void *)&(src.pixels[0]),src.pixels.length());
	return dst;
}
//inputFrame<<m_input
cv::Mat operator<<(cv::Mat& dst, const RTC::CameraImage src)
{
	return src>>dst;
}


//outputFrame>>m_output
RTC::CameraImage operator>>(const cv::Mat src, RTC::CameraImage& dst)
{
	dst.pixels.length(src.size().height * src.size().width * src.elemSize());
	dst.height	= src.size().height;
	dst.width	= src.size().width;
	dst.bpp	= src.type();
	memcpy((void *)&(dst.pixels[0]),src.data,src.size().height * src.size().width * src.elemSize());
	return dst;
}
//m_output<<outputFrame
RTC::CameraImage operator<<(RTC::CameraImage& dst, const cv::Mat src)
{
	return src>>dst;
}
*/

RTC::ReturnCode_t usbcamera::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("input", m_inputIn);
  
  // Set OutPort buffer
  addOutPort("output", m_outputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("viewer", m_viewer, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t usbcamera::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t usbcamera::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t usbcamera::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t usbcamera::onActivated(RTC::UniqueId ec_id)
{
	m_output.width = 0;
	m_output.height = 0;
	//viewer flag
	prevflg = 0;
/*	if(m_view==1)
	{
		prevflg = 0;
		cout<<m_outputOut.getName()<<" viewer ON"<<endl;
		cv::namedWindow(m_outputOut.getName(), CV_WINDOW_AUTOSIZE);
	}
*/
  return RTC::RTC_OK;
}


RTC::ReturnCode_t usbcamera::onDeactivated(RTC::UniqueId ec_id)
{
	inputFrame.release();
	outputFrame.release();

	//バッファの初期化
	while(m_inputIn.isNew()) m_inputIn.read();

	switch_viewer(outputFrame, m_outputOut.getName(), prevflg, 0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t usbcamera::onExecute(RTC::UniqueId ec_id)
{
  // Check input image is new
  if (!m_inputIn.isNew())
  {	
	return RTC::RTC_OK;
  }
  m_inputIn.read();

	//画像が空、または画像のサイズ、チャンネルが変化
	m_input>>inputFrame;
	inputFrame<<m_input;	

	/*inputFrame -> outputFrame
	 *　
	 *　以下の行を書き換えて、処理内容を記述.
	 *　
	 */
	cvtColor( inputFrame, outputFrame, CV_BGR2GRAY);
	//outputFrame = inputFrame;	//shallow copy
	
	outputFrame>>m_output;
	m_output<<outputFrame;
	
	//viwer
	switch_viewer(outputFrame, m_outputOut.getName(), prevflg, m_viewer);
	m_outputOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t usbcamera::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t usbcamera::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t usbcamera::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t usbcamera::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t usbcamera::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

//bool comp_template::SizeChange(const RTC::CameraImage img, int& old[])
/*bool comp_template::SizeChange(const RTC::CameraImage img, const cv::Mat mat)
{
//	if(old[0] != img.height || old[1] != img.width || old[2] != img.bpp || old[3] != (int)img.pixels.length())
	if(mat.size().height != img.height || mat.size().width != img.width || mat.type() != img.bpp || mat.size().height * mat.size().width * mat.elemSize() != (int)img.pixels.length())
	{
    return true;
	}

    return false;

}
*/

void usbcamera::switch_viewer(const cv::Mat& src, const std::string name, int& prev, const int curr)
{
	if(curr != prev)	//flg changed
	{	
		if(prev == 1)
		{		
			prev = 0;
			cout<<name<<" viewer OFF"<<endl;
			cv::destroyWindow(name);
		}
		else
		{		
			prev = 1;
			cout<<name<<" viewer ON"<<endl;
			cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
		}
	}	
	if(curr == 1){
		#if (!defined WIN32) || (!defined WIN64)
   			cvStartWindowThread();
		#endif
		cv::imshow(name,src);
	}
}

extern "C"
{
 
  void usbcameraInit(RTC::Manager* manager)
  {
    coil::Properties profile(usbcamera_spec);
    manager->registerFactory(profile,
                             RTC::Create<usbcamera>,
                             RTC::Delete<usbcamera>);
  }
  
};


