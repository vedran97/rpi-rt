
## This library has been written for RPI-Model 4B, running a Ubuntu 20.04 Server

1. It has Real time settings which one can apply in a thread,to extract max performance from an RPI.
2. With Great power,comes great responsibility
3. ROS Noetic is used as a packaging and build system for it.

## CPU settings:

sudo chmod 777 /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
sudo chmod 777 /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
sudo chmod 777 /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor
sudo chmod 777 /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor

sudo echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor

sudo echo performance > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor

sudo echo performance > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor

sudo echo performance > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor

echo -1 >/proc/sys/kernel/sched_rt_runtime_us