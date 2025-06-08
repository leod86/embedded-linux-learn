#!/bin/bash
LOGFILE="cpu_log.txt"
echo "start CPUmonitor sh"
while true
do
	DATE=$(date '+%Y-%m-%d %H:%m:%s')
	CPU=$(top -bn1 | grep "Cpu(s)" | awk '{print $2 + $4}')
	echo "$DATE CPU: $CPU%" >> $LOGFILE
	sleep 5
done
