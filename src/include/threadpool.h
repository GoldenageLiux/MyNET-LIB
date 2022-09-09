/**
 * @Author: liuxin
 * @Date:   2022-09-09 10:43:03
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-09 16:24:56
 */
#pragma once
#include <condition_variable>  // NOLINT
#include <functional>
#include <future>  // NOLINT
#include <memory>
#include <mutex>  // NOLINT
#include <queue>
#include <thread>  // NOLINT
#include <utility>
#include <vector>
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

class ThreadPool
{
    public:
        ThreadPool(unsigned int size = std::thread::hardware_concurrency());
        ~ThreadPool();

        // -> 尾返回类型（trailing return type）,利用 auto 关键字将返回类型后置
        // std::result_of 用于推导模板返回值的类型，在这个地方用于推导线程返回结果类型
        template <class F, class... Args>
        auto Add(const std::string &threadName, F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>;

    private:
        std::queue<std::pair<std::string, std::function<void ()>>> m_tasks_;
        std::vector<std::thread> m_workers_;
        std::mutex m_queue_mutex_;
        std::condition_variable m_condition_variable_;
        bool m_stop_{false};

};


// 不能放在cpp文件，C++编译器不支持模版的分离编译
template <class F, class... Args>
auto ThreadPool::Add(const std::string &threadName, F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type> {

  
  using return_type = typename std::result_of<F(Args...)>::type;

  // std::forward 完美转发参数
  // std::packaged_task 封装任何可以调用的目标, 从而用于实现异步的调用 
  auto task =
      std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
  
  // std::future 访问异步操作结果
  // 获取线程返回结果, 异步传输线程返回
  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(m_queue_mutex_);

    // don't allow enqueueing after stopping the pool
    if (m_stop_) {
      throw std::runtime_error("enqueue on stopped ThreadPool");
    }

    m_tasks_.emplace(std::pair<std::string, std::function<void ()>>(threadName, [task] () { (*task)(); }));  // 将线程加入线程池
    
  }
  m_condition_variable_.notify_one();
  return res;
}

#endif /* __THREADPOOL_H__ */
