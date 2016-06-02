#ifndef __SSKJ_LOG_H__
#define __SSKJ_LOG_H__


#define LOG_TAG "mediaMuxSend"

#define LOG(fmt...)	 printf(fmt);printf("\n")
#define LOGW(fmt...) printf(fmt);printf("\n")
#define LOGD(fmt...) printf(fmt);printf("\n")
#define LOGE(fmt...) printf(fmt);printf("\n")
#define LOGI(fmt...) printf(fmt);printf("\n")
class LOG_Trace
{
public:
    LOG_Trace(const char * pszFuncName)
    {
    	m_pFuncName = pszFuncName;
		LOG("Enter [%s]", m_pFuncName);
	}
    ~LOG_Trace()
	{
		LOG("Out [%s]", m_pFuncName);
	}
private:
	const char* m_pFuncName;
    LOG_Trace();
};

#define LOGTRACE()   LOG_Trace LogTrace(__FUNCTION__)

#endif
