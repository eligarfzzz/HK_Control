#pragma once

#ifdef HKCONTROL_EXPORTS
#define HKCAPI  __declspec(dllexport)
#else
#define HKCAPI __declspec(dllimport)
#endif // HKCONTROL_EXPORTS
//默认云台速度
#define DEFAULTSPEED 3

#include<Windows.h>
#include<string>
#include<vector>


 /**
  * @brief 对海康威视摄像机API简单封装，方便调用
  * 注意使用Dll后无需手动NET_DVR_Init和NET_DVR_Cleanup，由Dll内的一个静态全局对象自动Init和Cleanup
 */
 class HK_Control
{
private:
	//ip
	std::string _ip;
	//端口
	int _port = 8000;
	//用户名
	std::string _user;
	//密码
	std::string _pwd;
	//播放窗口hwnd
	HWND _hwnd = NULL;
	//登录成功后的id
	long _loginID = -1;
	//播放通道
	long _channel = 1;
	//播放id
	long _playID = -1;
	//正在录象？
	bool _isRecording = false;
public:
	/**
	 * @brief 登录与播放参数初始化
	 * @param ip ip
	 * @param port 端口
	 * @param user 用户名
	 * @param pwd 密码
	 * @param channel 播放通道，默认为 1
	 * @return  
	*/
	HKCAPI HK_Control(std::string ip, int port, std::string user, std::string pwd, long channel = 1);
	/**
	 * @brief 析构，并检查是否退出登录、停止播放等
	 * @return 
	*/
	HKCAPI ~HK_Control();
	/**
	 * @brief 登录
	 * @return 成功返回0，失败返回错误码
	*/
	HKCAPI DWORD Login();
	/**
	 * @brief 是否已经登陆而未退出
	 * @return true已经登陆而未退出，false已退出
	*/
	HKCAPI bool IsLogin();
	/**
	 * @brief 正在播放
	 * @return true正在播放，fasle未正在播放
	*/
	HKCAPI bool IsPlay();
	/**
	 * @brief 是否正在播放
	 * @return 
	*/
	HKCAPI bool IsRecording();
	/**
	 * @brief 播放预览
	 * @param hwnd 预览画面所渲染的hwnd
	 * @return 成功返回0，失败返回错误码
	*/
	HKCAPI DWORD Play(HWND hwnd);
	/**
	 * @brief 进行一次抓图，格式为jpg
	 * @param filename 抓图文件名
	 * @return 成功返回0，失败返回错误码
	*/
	HKCAPI DWORD CaptureJPG(std::string filename);
	/**
	 * @brief 进行一次抓图，格式为bpm
	 * @param filename 抓图文件名
	 * @return 成功返回0，失败返回错误码
	*/
	HKCAPI DWORD CaptureBMP(std::string filename);
	/**
	 * @brief 开始录像
	 * @exception std::exception 如果连续开始录像，而未停止上一次录像，会抛出重复录像异常。
	 * @param filename 录像文件名 
	 * @return 成功返回0，失败返回错误码
	*/
	HKCAPI DWORD StartRecord(std::string filename);
	/**
	 * @brief 停止录像
	 * @return 成功返回0，失败返回错误码
	*/
	HKCAPI DWORD EndRecord();

	/**
	 * @brief 停止播放
	 * @return 
	*/
	HKCAPI DWORD StopPlay();
	/**
	 * @brief 注销登录
	 * @return 
	*/
	HKCAPI DWORD Logout();
	/**
	 * @brief 添加目前位置到预置位
	 * @param dwPresetIndex 预置位序号
	 * @return 
	*/
	HKCAPI BOOL AddCameraPreset( DWORD dwPresetIndex);
	/**
	 * @brief 相机移动到预置位
	 * @param dwPresetIndex 预置位序号
	 * @return 
	*/
	HKCAPI BOOL MoveCameraToPreset( DWORD dwPresetIndex);
	//以下是云台控制
	//up static
	HKCAPI void MoveCameraUpStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraUpStop(DWORD speed = DEFAULTSPEED);
	//down static
	HKCAPI void MoveCameraDownStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraDownStop(DWORD speed = DEFAULTSPEED);
	//left static
	HKCAPI void MoveCameraLeftStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraLeftStop(DWORD speed = DEFAULTSPEED);
	//right static
	HKCAPI void MoveCameraRightStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraRightStop(DWORD speed = DEFAULTSPEED);
	//Zoom in
	HKCAPI void ZoomInStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void ZoomInStop(DWORD speed = DEFAULTSPEED);
	//Zoom out
	HKCAPI void ZoomOutStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void ZoomOutStop(DWORD speed = DEFAULTSPEED);
	//Focus near
	HKCAPI void FocusNearStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void FocusNearStop(DWORD speed = DEFAULTSPEED);
	//Focus far
	HKCAPI void FocusFarStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void FocusFarStop(DWORD speed = DEFAULTSPEED);
	//IRIS open
	HKCAPI void IRISOpenStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void IRISOpenStop(DWORD speed = DEFAULTSPEED);
	//IRIS close
	HKCAPI void IRISCloseStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void IRISCloseStop(DWORD speed = DEFAULTSPEED);

	HKCAPI DWORD GetLastCameraError();
};

