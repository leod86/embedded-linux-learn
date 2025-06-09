#!/bin/bash
# monitor.sh —— 运行 cpu_monitor 程序，并按日期保存日志

# 设置日志文件夹
LOG_DIR="./cpu_log"

# 生成文件名：比如 2025-06-10.log
LOG_FILE="$LOG_DIR/$(date +%F).log"

# 如果日志目录不存在就自动创建
if [ ! -d "$LOG_DIR" ]; then
    mkdir "$LOG_DIR"
fi

# 检查 cpu_monitor 是否存在
if [ ! -f "./cpu_monitor" ]; then
    echo "❌ 未找到 cpu_monitor，请先编译"
    exit 1
fi

# 执行 cpu_monitor，传入日志路径
./cpu_monitor "$LOG_FILE"

# 提示完成
echo "✅ 日志已保存至 $LOG_FILE"
