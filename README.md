明白了，你希望内容保留完整、结构清晰、逻辑分明。以下是根据你的原始笔记 + 30 天成长路线，**重新排版整理的 Markdown**，保留所有关键信息，并将 **学习计划列在最前面** 📅：

---

# 🚀 嵌入式 Linux 30 天学习计划（结构化整理版）

---

## 🗓️ 30 天任务总览

### 📦 阶段一：用户态工具（Day 1\~7）

| Day      | 内容简述                                 | 状态  |
| -------- | ------------------------------------ | --- |
| ✅ Day 1  | 安装 Ubuntu、练习终端命令、初始化 Git 仓库          | 完成  |
| ✅ Day 2  | 编写 monitor.sh 脚本，定时采集 CPU 使用率 + 写入日志 | 完成  |
| ✅ Day 3  | 用 C 写 CPU 采集程序，生成二进制工具               | 完成  |
| ✅ Day 4  | 写 Makefile、学 gcc 参数、打包二进制项目          | 完成  |
| ✅ Day 5  | gdb 调试、断点、单步分析运行流程                   | 完成  |
| ✅ Day 6  | Shell 脚本 + C 程序联动（系统行为组装）            | 完成  |
| 🔜 Day 7 | GitHub 上传 + 写 README + 总结反馈          | 待完成 |

---

### ⚙️ 阶段二：构建 rootfs（Day 8\~14）

| Day    | 内容                           |
| ------ | ---------------------------- |
| Day 8  | 安装交叉编译工具链，理解 host/target 架构  |
| Day 9  | 编译 BusyBox + 制作 rootfs       |
| Day 10 | QEMU 启动 rootfs，搭建最小 Linux 环境 |
| Day 11 | 添加程序脚本到 rootfs 中，实现自启动       |
| Day 12 | 学习 init、systemd、/etc/inittab |
| Day 13 | 构建完整系统镜像（含应用 + 日志）           |
| Day 14 | GitHub 提交：文档 + 镜像说明          |

---

### 🧩 阶段三：驱动开发（Day 15\~21）

| Day    | 内容                                 |
| ------ | ---------------------------------- |
| Day 15 | 编写 Hello 驱动模块，insmod 加载，dmesg 查看日志 |
| Day 16 | 实现简单字符设备 + 注册 /dev 节点              |
| Day 17 | 写用户空间程序读写驱动                        |
| Day 18 | 修改设备树，挂载自定义设备                      |
| Day 19 | 编写 platform\_driver 驱动，动态绑定        |
| Day 20 | 使用 busybox 系统测试驱动功能                |
| Day 21 | GitHub 提交驱动 demo + README          |

---

### 🌐 阶段四：项目整合（Day 22\~28）

| Day    | 内容                                   |
| ------ | ------------------------------------ |
| Day 22 | 项目选型：如温湿度采集 + 上传                     |
| Day 23 | 设计项目结构：drivers / app / script / docs |
| Day 24 | 整合脚本、服务、驱动，打包 rootfs                 |
| Day 25 | 实现 OTA 逻辑 / 版本管理                     |
| Day 26 | 项目运行录屏 / 截图 / 展示                     |
| Day 27 | 写英文项目 Readme + 简历内容                  |
| Day 28 | 整体推送 GitHub，打 tag                    |

---

### 🧾 阶段五：成果输出（Day 29\~30）

| Day    | 内容                     |
| ------ | ---------------------- |
| Day 29 | 项目展示整理：结构图 / 截图 / 部署说明 |
| Day 30 | 自我评估，确定是否深入转型路线        |

---

## ✅ 学习日志要点汇总（截至 Day 6）

---

### 📁 项目结构

```text
embedded-linux-learn/
├── day1/
├── day2/
│   └── monitor.sh
├── day3/
│   └── cpu_monitor.c
├── day4/
│   ├── cpu_monitor.c
│   └── Makefile
├── day5/
├── cpu_log/
│   └── 2025-06-10.log
```

---

### 🧠 C 编程知识

#### `main(int argc, char *argv[])`

* `argc`：参数个数（包含程序本身）
* `argv[1]`：你手动传入的参数，比如日志路径
* 示例：

  ```bash
  ./cpu_monitor ./cpu_log/2025-06-10.log
  ```

#### 文件操作

| 函数                      | 用法           |
| ----------------------- | ------------ |
| `fopen(path, "a")`      | 打开或创建文件，追加写入 |
| `fprintf()`             | 向文件写格式化数据    |
| `fgets()`               | 读取文本行        |
| `fclose()`              | 关闭文件         |
| `sscanf()`              | 字符串中提取数值     |
| `sleep()`               | 程序延时         |
| `time()` / `strftime()` | 获取系统时间并格式化   |

---

### 🧪 Shell 脚本 monitor.sh 功能

```bash
#!/bin/bash
# 检查并创建日志目录
# 检查 cpu_monitor 是否存在
# 调用 ./cpu_monitor 日志路径
```

作用：统一管理 CPU 采集任务，配合 cron 可实现周期性执行。

---

### ⚙️ Makefile（自动化构建）

```make
monitor: monitor.c
	gcc monitor.c -o monitor

clean:
	rm -f monitor
```

只需运行：

```bash
make        # 自动编译
make clean  # 清除目标
```

---

### 🧰 Git 操作备忘录

```bash
git init
git add .
git commit -m "day1~3 整理"
git branch -M main
git remote add origin git@github.com:xxx/embedded-linux-learn.git
git push -u origin main
```

---

### 🔍 GDB 调试流程（Day 5）

```bash
gcc -g cpu_monitor.c -o cpu_monitor    # 带调试符号
gdb ./cpu_monitor
(gdb) break main
(gdb) run ./log.txt
(gdb) next / print / continue
```

---

### 🧪 Shell 与 C 联动机制（Day 6）

* 脚本通过执行程序 + 参数方式调用 C 程序
* C 程序读取参数并写入文件
* 支持按日期归档

---

### 📘 总结：你目前掌握的

* Ubuntu 基本命令
* Git 本地操作 + 远程推送
* Shell 脚本基本结构与逻辑判断
* C语言文件操作、时间处理
* GDB 断点调试
* Makefile 自动构建

---
