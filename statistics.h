#ifndef STATISTICS_H
#define STATISTICS_H

#include <chrono>

class statistics
{
private:
    unsigned long long m_totalReceiveTime {0};
    unsigned long long m_totalPackagesReceived {0};
    unsigned long m_totalPackagesLost {0};
    unsigned long m_maxReceiveTime {0};

    bool m_isMeasuring {false};

    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_stopTime;

public:
    statistics(/* args */);

    void startMeasurement();
    void stopMeasurement();
    void interruptMeasurement();

    void printStatistics();

    ~statistics();
};



#endif /* STATISTICS_H */
