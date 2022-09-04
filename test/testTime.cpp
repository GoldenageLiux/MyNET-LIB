/**
 * @Author: liuxin
 * @Date:   2022-06-10 11:10:26
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-09-04 19:44:03
 */
#include "TimeStamp.h"
#include "Logger.h"
#include <iostream>

int main() {
//   std::cout << TimeStamp::nowTime().toString() << std::endl;
  LOG_INFO("TcpConnection::deletor[%s] at fd=%d state=%d \n", 
  "hello", 1, 2);
  LOG_DEBUG("TcpConnection::deletor[%s] at fd=%d state=%d \n", 
  "hello", 1, 2);
  LOG_ERROR("TcpConnection::deletor[%s] at fd=%d state=%d \n", 
  "hello", 1, 2);
  LOG_FATAL("TcpConnection::deletor[%s] at fd=%d state=%d \n", 
  "hello", 1, 2);
  return 0;
}