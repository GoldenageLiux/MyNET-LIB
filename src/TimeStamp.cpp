/**
 * @Author: liuxin
 * @Date:   2022-06-10 11:10:26
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-04 19:21:06
 */
#include "TimeStamp.h"
#include <time.h>
using namespace std;

TimeStamp::TimeStamp(int64_t microSecondSinceEpoch) : microSecondSinceEpoch_(microSecondSinceEpoch){}

TimeStamp TimeStamp::nowTime() //返回当前时间 这是一个static函数
{
    return TimeStamp(time(NULL));
}

string TimeStamp::toString() const //把int64_t的时间转换为字符串
{
    char buf[128] = {0};
    tm *tm_time = localtime(&microSecondSinceEpoch_);  //localtime函数返回的结构体类型tm如下所示。
    snprintf(buf, 128, " %4d/%02d/%02d %02d:%02d:%02d", 
        tm_time->tm_year+1900, 
        tm_time->tm_mon+1, 
        tm_time->tm_mday, 
        tm_time->tm_hour, 
        tm_time->tm_min, 
        tm_time->tm_sec);
    return buf;
}

