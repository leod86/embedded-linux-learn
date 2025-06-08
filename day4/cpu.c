#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cpu.h"

double get_cpu_usage(void)
{
    FILE *fp;
    char line[256];
    long user1, nice1, system1, idle1;
    long user2, nice2, system2, idle2;
    // 第一次读取CPU使用率
    fp = fopen("/proc/stat", "r"); // 打开文件
    fgets(line, sizeof(line), fp);
    sscanf(line, "cpu %ld %ld %ld %ld", &user1, &nice1, &system1, &idle1);
    fclose(fp); // 读完关闭文件
    sleep(1);

    // 第二次读取CPU使用率
    fp = fopen("/proc/stat", "r");
    fgets(line, sizeof(line), fp);
    sscanf(line, "cpu %ld %ld %ld %ld", &user2, &nice2, &system2, &idle2);
    fclose(fp);

    long total1 = user1 + nice1 + system1 + idle1;
    long total2 = user2 + nice2 + system2 + idle2;
    long idle_diff = idle2 - idle1;
    long total_diff = total2 - total1;
    return 100.0 * (1.0 - (doubel)idle_diff / total_diff);
}

void log_cpu_usage(void)
{
    FILE *log_file = fopen("cpu_usage.log", "a");
    if (log_file == NULL)
        return;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(log_file, "%s CPU使用率: %.2f%%\n", time_str, usage);
    fclose(log_file);
}