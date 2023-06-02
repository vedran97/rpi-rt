#ifndef RPI_RT_H_
#define RPI_RT_H_

#include  <stddef.h>
#include  <assert.h>
#include <fstream>

namespace rpi_rt{
/// @brief Enum class to represent CPU Cores
enum class CPUS:size_t{
CPU1,
CPU2,
CPU3,
CPU4
};
/// @brief This settings class has all the settings that are required to be applied to a thread to make it a RT thread on Raspberry Pi 4
class rt_settings
{
private:
    /* data */
    const CPUS affCPU;
    const int priority;
    const int memoryToBeLocked;
    std::ofstream dma_latency;
public:

    /// @brief Constructor for rt_settings
    /// @param affCPUs CPU Core to which the calling thread needs to be pinned
    /// @param priority Thread priority to be assigned to a caller thread
    /// @param memoryToBeLocked Amount of memory to be locked for the caller thread in bytes
    rt_settings(CPUS affCPUs,int priority,int memoryToBeLocked)
    :affCPU(affCPUs),
    priority(priority),
    memoryToBeLocked(memoryToBeLocked)
    {
        assert((this->priority)>0);
        assert((this->memoryToBeLocked)>0);
    }
    /// @brief Pins the calling thread to a CPU Core mentioned in the constructor
    /// @throws std::runtime_error if the function fails to attach affinity
    void applyAffinity()const;

    /// @brief Applies specified thread priority to the calling thread
    /// @throws std::runtime_error if the thread priority fails to be set
    void applyPriority()const;

    /**
     * @brief Allocates and locks memory for the caller
     * @note  This function is not implemented yet
    */
    void applyMemoryLock()const;

    /// @brief Changes power governance mode of CPU to high performance mode
    /// @note This function is not tested yet
    /// @throws std::runtime_error if the program fails to apply high performance mode
    void applyHighPerfModeToAllCPUs()const;

    /**
     * @brief Changes sched_rt_runtime_us time to -1, Find more information here: https://www.kernel.org/doc/Documentation/scheduler/sched-rt-group.txt
     * This will basically allow a RT thread to run for infinite time
     * @throws std::runtime_error if the file /proc/sys/kernel/sched_rt_runtime_us is not accessible, or if the write fails
     */
    void applySchedulingTimeChange()const;

    /// @brief Set CPU  DMA Latency to 0, Find more information here:https://access.redhat.com/articles/65410
    /// @throws std::runtime_error if the method fails to set CPU DMA Latency
    /// @note This function is not tested yet
    void setCPUDmaLatency();

    /// @brief Destructor for rt_settings
    virtual ~rt_settings();
};

};
#endif // RPI_RT_H_
