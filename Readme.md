
## This library has been written for RPI-Model 4B, running a Ubuntu 20.04 Server

1. It has Real time settings which one can apply in a thread,to extract max performance from an RPI.
2. With Great power,comes great responsibility
3. ROS Noetic is used as a packaging and build system for it.

## Requirements:

0. Please Ensure you have the RPI patched with a PREEMPT_RT patch, otherwise you wouldnt be able to apply a RT priority to SCHED_FIFO
1. For using this library, your user will need to have root permissions.
2. Secondly, to set RT priorities, please set ulimit configs in the following way:
    1. Add your user to a group, in this example, called "rtprio"
    2. Give this group root permissions:<br> 
    ```sudo groupadd rtprio``` <br>
    ``sudo usermod -a -G rtprio <username>``<br>
    ```sudo chmod 4750 /usr/bin/chrt ``` <br>
    3. Now you have to configure hard and soft priority limits which the group can use:
    5. Open /etc/security/limits.conf in an editor of your choice and add the following lines:<br>
    ```<username> hard rtprio 99``` <br>
    ```<username> soft rtprio 99```
    6. Reference for the above: https://stackoverflow.com/questions/10704983/operation-not-permitted-while-setting-new-priority-for-thread
    7. One way to programatically change soft and hard limit : https://man7.org/linux/man-pages/man2/getrlimit.2.html

