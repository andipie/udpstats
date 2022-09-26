#include "statistics.h"

#include <iostream>

statistics::statistics(/* args */)
{
}

statistics::~statistics()
{
}

void statistics::startMeasurement()
{
    if (m_isMeasuring) {
        interruptMeasurement();
    }

    m_isMeasuring = true;

    m_startTime = std::chrono::high_resolution_clock::now();
}

void statistics::stopMeasurement()
{
    if (!m_isMeasuring) return;
    m_isMeasuring = false;

    m_stopTime = std::chrono::high_resolution_clock::now();

    long long deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(m_stopTime - m_startTime).count();

    if (deltaTime > m_maxReceiveTime) {
        m_maxReceiveTime = deltaTime;
    }

    m_totalReceiveTime += deltaTime;
    m_totalPackagesReceived++;
}

void statistics::interruptMeasurement()
{
    if (!m_isMeasuring) return;

    m_totalPackagesLost++;
}

void statistics::printStatistics()
{
    std::cout << "Total packages received: " << m_totalPackagesReceived << std::endl;
    std::cout << "Total packages lost: " << m_totalPackagesLost << std::endl;
    std::cout << "Total receive time: " << m_totalReceiveTime << " microseconds" << std::endl;
    std::cout << "Average receive time: " << m_totalReceiveTime / m_totalPackagesReceived << " microseconds" << std::endl;
    std::cout << "Max receive time: " << m_maxReceiveTime << " microseconds" << std::endl;
}
