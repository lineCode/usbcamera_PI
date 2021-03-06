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
    "conf.default.device_num", "0",
    // Widget
    "conf.__widget__.viewer", "radio",
    // Constraints
    "conf.__constraints__.viewer", "(1:ON,0:OFF)",
    "conf.__widget__.device_num", "text",
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


RTC::ReturnCode_t usbcamera::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("output", m_outputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("viewer", m_viewer, "0");
  bindParameter("device_num", m_device_num, "0");
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
	videoCapture.open(m_device_num);
	if (!videoCapture.isOpened())
	{
		cout<<"No Camera Device"<<endl;
		return RTC::RTC_ERROR;		
	}
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
	videoCapture.release();

	outputFrame.release();
	count = 0;
	switch_viewer(outputFrame, m_outputOut.getName(), prevflg, 0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t usbcamera::onExecute(RTC::UniqueId ec_id)
{
	if (!videoCapture.isOpened())
		 return RTC::RTC_OK;
	//videoCapture>>inputFrame;
	if (!videoCapture.read(outputFrame))
		return RTC::RTC_OK;

	outputFrame>>m_output;
	
	//viwer
	switch_viewer(outputFrame, m_outputOut.getName(), prevflg, m_viewer);
	m_outputOut.write();
  if (count > 100)
  {
		count = 0;
		coil::TimeValue tm;
		tm = coil::gettimeofday();

		double sec(tm - tm_pre);

		if (sec > 1.0 && sec < 1000.0)
		{
			  std::cout << 100/sec << " [FPS]" << std::endl;
		}

		tm_pre = tm;
  }
  ++count;
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


