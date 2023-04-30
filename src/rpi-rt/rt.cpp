#include "rpi-rt/rt.hpp"

#include <sched.h>
#include <cstring>
#include <string>
#include <stdexcept>
#include <pthread.h>

namespace rpi_rt{

std::runtime_error getError(std::string msg,int result){
    return std::runtime_error(msg+" Reason:"+std::string(std::strerror(result)));
}

void rt_settings::applyAffinity() const {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    const auto aff = static_cast<std::underlying_type<CPUS>::type>(affCPU);
    CPU_SET(aff, &cpuset);  
    auto result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        throw getError("Failed to attach affinity",result);
    }
}

void rt_settings::applyPriority() const {
    struct sched_param params;
    const auto maxPrior = sched_get_priority_max(SCHED_FIFO);
    (maxPrior < this->priority)?params.sched_priority = maxPrior : params.sched_priority = this->priority;
    auto result = pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);
    if ( result!= 0) {
        throw getError("Failed to set priority",result);
    }
}

void rt_settings::applyMemoryLock() const {

}

void rt_settings::applyHighPerfModeToAllCPUs() const {
    // Set CPU governor to "performance"
    for (int i = 0; i < 4; i++) {
        std::ofstream cpuGovFile("/sys/devices/system/cpu/cpu" + std::to_string(i) + "/cpufreq/scaling_governor");
        if (!cpuGovFile.is_open()) {
            throw getError("Failed to open /sys/devices/system/cpu/cpu" + std::to_string(i) + "/cpufreq/scaling_governor",0);
        }
        cpuGovFile << "performance";
        if(cpuGovFile.bad()){
            throw getError("Failed to write performance to /sys/devices/system/cpu/cpu" + std::to_string(i) + "/cpufreq/scaling_governor",0);
        }
        cpuGovFile.close();
    }
}

void rt_settings::applySchedulingTimeChange() const {

    std::ofstream rt_runtime("/proc/sys/kernel/sched_rt_runtime_us",std::ios::out);

    if (!rt_runtime.is_open()) {
        throw getError("Failed to open /proc/sys/kernel/sched_rt_runtime_us",0);
    }
    //TODO@VR: Add a way to configure this parameter
    rt_runtime << "-1";
    if (rt_runtime.bad()) {
        throw getError("Failed to write /proc/sys/kernel/sched_rt_runtime_us",0);
    }

    rt_runtime.close();
    return;
}

void rt_settings::setCPUDmaLatency() {
    dma_latency.open("/dev/cpu_dma_latency", std::ios::out);
    if (!dma_latency.is_open()) {
        throw getError("Failed to Open /proc/sys/kernel/sched_rt_runtime_us",0);
    }
    dma_latency << "0";
    if (dma_latency.bad()) {
        throw getError("Failed to write 0 to /dev/cpu_dma_latency",0);
    }
}

rt_settings::~rt_settings() {
    dma_latency.close();
}

}// namespace rpi_rt
