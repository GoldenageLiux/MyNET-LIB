/**
 * @Author: liuxin
 * @Date:   2022-09-09 11:02:17
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-09 16:59:01
 */
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <atomic>
#include "threadpool.h"

// 维护一个原子标志哈希表
std::unordered_map<std::string, std::atomic<bool>> flags;

int test(int i){
    std::cout  << i << "help" << std::endl;
    return 1;
}

int main(int argc, char const *argv[])
{
    ThreadPool pool(4);
    std::vector< std::future<int> > results;
 
    for(int i = 0; i < 12; ++i) {
        results.emplace_back(
            pool.Add("thread" + i, [&]  {
                test(i);
                return 1;
            }));
        flags["thread" + i].store(false);
    }

    for(int i = 0; i < 12; ++i)
    {
        // 通过对应原子标志将线程归还线程池
        flags["thread" + i].store(true);
        std::cout << "future result is " << results[i].get() << std::endl;
        std::cout << "第" << i << "个线程被结束" << std::endl;
    }
}