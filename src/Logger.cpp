/**
 * @Author: liuxin
 * @Date:   2022-06-10 11:10:26
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-04 19:43:18
 */
#include "Logger.h"
#include <iostream>
#include "TimeStamp.h"
using namespace std;


Logger& Logger::Instance()
{
    static Logger logger;
    return logger;
}
void Logger::setLogLevel(int level)
{
    level_ = level;
}
void Logger::log(string msg)
{
    // 写日志 [级别信息] time : msg
    switch(level_)
    {
        case INFO:
        {
            cout << "[INFO]";
            break;
        }
        case ERROR:
        {
            cout << "[ERROR]";
            break;
        }
        case FATAL:
        {
            cout << "[FATAL]";
            break;
        }
        case DEBUG:
        {
            cout << "[DEBUG]";
            break;
        }
        default:
            break;
    }
    //打印时间和消息
    cout << TimeStamp::nowTime().toString() << " : " << msg << endl;
}


// int main() {
// //   std::cout << TimeStamp::nowTime().toString() << std::endl;
//   LOG_INFO("TcpConnection::deletor[%s] at fd=%d state=%d \n", 
//         "hello", 1, 2);
//   return 0;
// }