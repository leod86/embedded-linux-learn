#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// 从 /proc/stat 读取 CPU 使用率
float get_cpu_usage() {
    FILE *fp;
    char line[256];
    long user1, nice1, system1, idle1;
    long user2, nice2, system2, idle2;

    fp = fopen("/proc/stat", "r");
    fgets(line, sizeof(line), fp);
    sscanf(line, "cpu %ld %ld %ld %ld", &user1, &nice1, &system1, &idle1);
    fclose(fp);

    sleep(1);

    fp = fopen("/proc/stat", "r");
    fgets(line, sizeof(line), fp);
    sscanf(line, "cpu %ld %ld %ld %ld", &user2, &nice2, &system2, &idle2);
    fclose(fp);

    long total1 = user1 + nice1 + system1 + idle1;
    long total2 = user2 + nice2 + system2 + idle2;
    long idle_diff = idle2 - idle1;
    long total_diff = total2 - total1;

    float usage = 100.0 * (1.0 - (float)idle_diff / total_diff);
    return usage;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("请传入日志文件路径\n");
        return 1;
    }

    FILE *log_fp = fopen(argv[1], "a");
    if (!log_fp) {
        perror("无法打开日志文件");
        return 1;
    }

    float cpu_usage = get_cpu_usage();

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(log_fp, "%s CPU使用率: %.1f%%\n", time_str, cpu_usage);
    fclose(log_fp);

    printf("✅ 数据已写入 %s\n", argv[1]);
    return 0;
}
