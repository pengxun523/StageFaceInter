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

    // 启动线程, 保证Start()函数结束时，线程已经开始执行
    virtual void Start();

    virtual void Stop();

    virtual bool IsStop();

    // 等待线程关闭
    virtual void Join();

    // 子类需要重载此函数
    // Run()函数运行在新建的线程内
    virtual int Run() = 0;

	// 查看当前线程的状态
	virtual int State();

    pthread_t ThreadId() { return thread_id_; }

    int ThreadMain();

private:
    pthread_t thread_id_;
    bool is_stop_;
};

} // namespace Thread

#endif // _SIMPLE_THREAD_H_
