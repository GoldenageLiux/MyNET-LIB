/**
 * @Author: liuxin
 * @Date:   2022-06-10 11:10:26
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-04 19:21:12
 */
#pragma once
#include <iostream>
#include <string>

class TimeStamp{
    public:
        TimeStamp();
        //禁止隐式转换
        explicit TimeStamp(int64_t microSecondSinceEpoch);
        //返回当前时间
        static TimeStamp nowTime();
        std::string toString() const;

    private:
       //muduo中用了一个int64_t作为当前时间，单位为微秒
        int64_t microSecondSinceEpoch_; 
};