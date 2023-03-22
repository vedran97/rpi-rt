#ifndef RPI_RT_H_
#define RPI_RT_H_
namespace rpi_rt{
enum class CPUS{
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

    }
    /// @brief Pins the calling thread to a CPU Core mentioned in the constructor
    void applyAffinity();

    /// @brief Applies specified thread priority to the calling thread
    void applyPriority();

    /// @brief Allocates and locks memory for the caller
    void applyMemoryLock();

    /// @brief Changes power governance mode of CPU to high performance mode
    void applyHighPerformancemode();

    /// @brief Changes RT_SCHED time to -1
    void applySchedulingTimeChange();
};

};
#endif // RPI_RT_H_
