#ifndef _SIMPLE_THREAD_H_
#define _SIMPLE_THREAD_H_

#include <pthread.h>

namespace base
{

class SimpleThread
{
public:
    SimpleThread();

    virtual ~SimpleThread();

    // �����߳�, ��֤Start()��������ʱ���߳��Ѿ���ʼִ��
    virtual void Start();

    virtual void Stop();

    virtual bool IsStop();

    // �ȴ��̹߳ر�
    virtual void Join();

    // ������Ҫ���ش˺���
    // Run()�����������½����߳���
    virtual int Run() = 0;

	// �鿴��ǰ�̵߳�״̬
	virtual int State();

    pthread_t ThreadId() { return thread_id_; }

    int ThreadMain();

private:
    pthread_t thread_id_;
    bool is_stop_;
};

} // namespace Thread

#endif // _SIMPLE_THREAD_H_
