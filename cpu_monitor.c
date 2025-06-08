// cpu_monitor.c - 用 C 读取 /proc/stat 实时 CPU 使用率

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h> 
float get_cpu_usage() {
    FILE *fp;
    char line[256];
    long user1, nice1, system1, idle1;
    long user2, nice2, system2, idle2;

    // 第一次读取 /proc/stat
    fp = fopen("/proc/stat", "r");
    fgets(line, sizeof(line), fp);
    sscanf(line, "cpu %ld %ld %ld %ld", &user1, &nice1, &system1, &idle1);
    fclose(fp);

    sleep(1); // 间隔 1 秒

    // 第二次读取 /proc/stat
    fp = fopen("/proc/stat", "r");
    fgets(line, sizeof(line), fp);
    sscanf(line, "cpu %ld %ld %ld %ld", &user2, &nice2, &system2, &idle2);
    fclose(fp);

    long total1 = user1 + nice1 + system1 + idle1;
    long total2 = user2 + nice2 + system2 + idle2;
    long idle_diff = idle2 - idle1;
    long total_diff = total2 - total1;

    float cpu_usage = 100.0 * (1.0 - (float)idle_diff / total_diff);
    return cpu_usage;
}

int main() {
    FILE *log = fopen("cpu_log_c.txt", "a");
    if (!log) {
        perror("无法打开日志文件");
        return 1;
    }

    float usage = get_cpu_usage();

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(log, "%s CPU使用率: %.1f%%\n", time_str, usage);
    fclose(log);

    printf("✅ 数据已写入 cpu_log_c.txt\n");
    return 0;
}

