#ifndef _PACKT_TIMESERVICE_HPP_
#define _PACKT_TIMESERVICE_HPP_

#include "Interfaces/IPeriodicJob.h"
#include "PeriodicJobWatcher.h"
#include "PeriodicJobStorage.h"

#include <vector>

namespace hsg {
    class TimeService {
    public:
        TimeService();

        void start();
        void stop();
        void update();
        void registerPeriodicJob(IPeriodicJob* pJob);

    private:
        bool m_isActive;
        float mElapsed;
        double mLastTime;
        std::vector<PeriodicJobStorage> m_JobStorages;
        PeriodicJobWatcher m_Watcher;

        double now();
        float elapsed();
    };
}
#endif
