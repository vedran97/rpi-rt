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

void rt_settings::applyHighPerformancemode() const {

}

void rt_settings::applySchedulingTimeChange() const {

}

}