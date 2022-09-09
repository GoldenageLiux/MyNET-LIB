/**
 * @Author: liuxin
 * @Date:   2022-09-09 10:51:44
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-09 16:12:52
 */
#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned int size) {
    for(unsigned int i = 0; i < size; ++i){  //  启动size个线程
        m_workers_.emplace_back(std::thread([this](){  //定义每个线程的工作函数
            while(true){    
                std::function<void()> task;
                {   //在这个{}作用域内对std::mutex加锁, 出了作用域会自动解锁, 不需要调用unlock()
                    std::unique_lock<std::mutex> lock(m_queue_mutex_);
                    m_condition_variable_.wait(lock, [this](){     //等待条件变量, 条件为任务队列不为空或线程池停止
                        return m_stop_ || !m_tasks_.empty();
                    });
                    if(m_stop_ && m_tasks_.empty()) return;   //任务队列为空并且线程池停止, 退出线程
                    task  = std::move(m_tasks_.front().second);   //从任务队列头取出一个任务
                    m_tasks_.pop();
                }
                task();     //执行任务
            }
        }));
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_queue_mutex_);
        m_stop_ = true;
    }
    m_condition_variable_.notify_all();
    // 在对象的析构函数中调用线程的join函数, 等待资源回收
    for (std::thread &th: m_workers_) {
        if (th.joinable())
        {
            th.join();
        }
    }
}
