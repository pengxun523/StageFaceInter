#pragma once

#include <vector>
#include <string>
#include "SimpleThread.h"
#include <map>
#include <stdint.h>
#include "IFlvMuxBuffer.h"
#include "buffer.h"

enum SRedirectState
{
    REDIRECT_SVR_REQ,
    REDIRECT_SVR_RSP,
    REDIRECT_END
};

enum SVideoState
{
    VIDEO_ON_STAGE_REQ,
    VIDEO_ON_STAGE_RSP,
    VIDEO_HEARTBEAT,
    VIDEO_UPLOAD_HEAD,
    VIDEO_UPLOAD_DATA
};

enum ErrorCodeEnum
{
    InitSocketFail = 1,
    ConnectRedirectFail,
    VideoReqFailed,
    VideoRspFailed,
    ConnectVideoFailed,
    StageReqFailed,
    StageReqSuccess,
    HearbeatStop
};

#define UI_KEY_FRAME_LEN 10
#define UI_NORMAL_FRAME_LEN 1

class IFlvMuxBuffer;
class MuxThread;

struct ReqProgrammer
{
    std::string strUuId;
    std::string strUserName;
    std::string strRoomId;
    std::string strAppName;
    std::string strToken;
    std::string strMachineId;
};


//定义一个函数指针
//typedef void (*ErrorEventCallBack)(int ErrorCode);

typedef void (^EventCallBackBlock)(ErrorCodeEnum ErrorCode);

class CStageThread : public base::SimpleThread
{
public:
    CStageThread(IFlvMuxBuffer * iFlvMuxBuffer);
    
    EventCallBackBlock callBackBlock;
    
    int startRequest(struct ReqProgrammer reqPro, EventCallBackBlock backBlock);
    
//    ErrorEventCallBack _errorEventcb;
//    int InitWithCallBack(const std::string& strUuId,const std::string& strUserName,const std::string& strRoomId,const std::string& strAppName,const std::string& strToken,const std::string& strMachineId,ErrorEventCallBack errorEventcb);

    ~CStageThread();
    CStageThread();
    virtual int Run();
    //错误描述
//    virtual void ErrorEvent(int ErrorCode,const char*ErrorDesciption) = 0;
    
    void stopRun();
    
    int Init();
    
    int SetUuId(const char* uuId);
    int SetRoomId(const char* roomId);
    int SetUserName(const char* userName);
    int SetAppName(const char* appName);
    int SetToken(const char* token);
    int SetMachineId(const char* machineId);
    
    int StartPlay(IFlvMuxBuffer * iFlvMuxBuffer);
    
    int CheckRunningState();
    
private:
    
    int InitSocket();
    int getRedirectSvrIp(std::string & ipStr);
    bool ConnectRedirectSvr(const std::string& strIP, unsigned short usPort);
    bool ConnectVideoSvr(const std::string& strIP, unsigned short usPort);
    
    int DoRedirectSvrReq();
    int DoRedirectSvrRsp(const time_t& timeout);
    
    int DoOnStageReq();
    int DoOnStageRsp(const time_t& timeout);
    int DoVideoHearbeat();
    int DoVideoUploadHead();
    int DoVideoUploadData();
    
    int ParseTcpMsg(const char *data, uint32_t data_len);
    int ParseRedirectSvrRsp(const char *data, uint32_t data_len);
    int ParseOnStageRsp(const char *data, uint32_t data_len);
    
private:
    int on_send(int socketFd, std::string funcStr);
    int on_recv(int socketFd, std::string funcStr, const time_t& timeout);
private:
    IFlvMuxBuffer *	 m_pIFlvMuxBuffer;
    
private:
    SRedirectState  m_oRedirectState;
    SVideoState		m_oState;
    time_t			m_tSendVideoSvrReqTime;
    time_t			m_tSendLoginReqTime;
    time_t			m_tSendHearbeatTime;
    bool			m_bStartPlay;
    
    char*			m_pSendBuf;
    char*			m_pRecvBuf;
    
    unsigned int	m_uiSendBufSize;
    unsigned int	m_uiRecvBufSize;
    
    bool			m_bHaveDataToSend;
    CVBuffer		m_oSendCVBuffer;
    unsigned int	m_uiSendIndex;
    
    unsigned int	m_uiRecvIndex;
    
private:
    int m_hRedirectSocket;
    int m_hVideoSvrSocket;
    
    std::string m_redirectServerIp;
    unsigned short m_redirectServerPort;
    
    std::string m_videoServerIp;
    unsigned short m_videoServerPort;
    unsigned int m_uiIpToRedirect;
    std::map<std::string, int (CStageThread::*)(const char *, uint32_t)> funcmap;
    
private:
    std::string m_strUuId;
    std::string m_strUserName;
    std::string m_strRoomId;
    std::string m_strAppName;
    std::string m_strToken;
    std::string m_strMachineId;
};

//typedef void (*ErrorEventCallBack)(int ErrorCode,const char* ErrorDesciption);
//
//class EventClass:public CStageThread
//{
//    public:
//    EventClass(){}  //默认构造函数
//    ErrorEventCallBack _errorEventcb;
//    EventClass(ErrorEventCallBack errorEventcb) //带参数构造函数
//    {
//        _errorEventcb = errorEventcb;
//    }
//    
//    void ErrorEvent(int ErrorCode,const char*ErrorDesciption)
//    {
//        _errorEventcb(ErrorCode,ErrorDesciption);
//    }
//};

