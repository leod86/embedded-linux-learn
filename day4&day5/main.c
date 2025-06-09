#include "cpu.h"

int main()
{
    double usage = get_cpu_usage(); // 获取cpu使用率
    log_cpu_usage(usage);           //  写入日志
    return 0;
}
