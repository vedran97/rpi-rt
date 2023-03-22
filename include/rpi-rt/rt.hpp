#ifndef RPI_RT_H_
#define RPI_RT_H_

#include  <stddef.h>
#include  <assert.h>
namespace rpi_rt{
enum class CPUS:size_t{
CPU1,
CPU2,
CPU3,
CPU4
};
class rt_settings
{
private:
    /* data */
    const CPUS affCPU;
    const int priority;
    const int memoryToBeLocked;
public:
    rt_settings(CPUS affCPUs,int priority,int memoryToBeLocked)
    :affCPU(affCPUs),
    priority(priority),
    memoryToBeLocked(memoryToBeLocked)
    {
        assert((this->priority)>0);
        assert((this->memoryToBeLocked)>0);
    }
    /// @brief Pins the calling thread to a CPU Core mentioned in the constructor
    void applyAffinity()const;

    /// @brief Applies specified thread priority to the calling thread
    void applyPriority()const;

    /// @brief Allocates and locks memory for the caller
    void applyMemoryLock()const;

    /// @brief Changes power governance mode of CPU to high performance mode
    void applyHighPerformancemode()const;

    /// @brief Changes RT_SCHED time to -1
    void applySchedulingTimeChange()const;
};

};
#endif // RPI_RT_H_
