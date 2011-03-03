#include "timeframe.h"

#include <time.h>

#ifdef _WIN32
#  include <windows.h>
#  include <winbase.h>
#else
#  include <sys/time.h>
#  include <unistd.h>
#  include <utime.h>
#endif

void sleep(int ms)
{
#ifdef _WIN32
  Sleep(ms);
#else
  usleep(ms*1000);
#endif
}

double currentTime()
{
#ifdef _WIN32
  double dTime = GetTickCount() / 1000.0;
  return (dTime);
#else
  timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec+tv.tv_usec*1e-6;
#endif
}