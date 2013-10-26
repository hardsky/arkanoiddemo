#include "TimeService.h"
#include "Types.h"
#include "Log.h"

#include <time.h>
#include <cstdlib>
#include <algorithm>

namespace hsg {

TimeService::TimeService() :
	m_isActive(false),
	mElapsed(0.0f),
	mLastTime(0.0f),
	m_JobStorages(),
	m_Watcher(){

	Log::info("Creating TimeService.");
}

void TimeService::start() {
	HSG_DEBUG("Starting TimeService.");

	srand(time(NULL));

	mElapsed = 0.0f;
	mLastTime = now();
	m_isActive = true;
}

void TimeService::update() {
	//HSG_DEBUG("TimeService::update");

	if(!m_isActive)
		return;

	// Checks elapsed time since last frame. It is important to
	// work on double with current time to avoid losing accuracy
	// Then we can go back to float for elapsed time.
	double lCurrentTime = now();
	mElapsed = (lCurrentTime - mLastTime);
	mLastTime = lCurrentTime;

	m_Watcher.setElapsed(mElapsed);
	std::for_each(m_JobStorages.begin(), m_JobStorages.end(), m_Watcher);
}

double TimeService::now() {
	// Retrieves current time with a monotonic clock to ensure
	// time goes forward and is not subject to system changes.
	timespec lTimeVal;
	clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
	return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
}

float TimeService::elapsed() {
	return mElapsed;
}

void TimeService::stop() {
	m_isActive = false;
}

void TimeService::registerPeriodicJob(IPeriodicJob* pJob){
	FpsGovernor::ptr pFPS(new FpsGovernor(pJob->period()));
	PeriodicJobStorage storage = {pJob, pFPS};
	m_JobStorages.push_back(storage);
}

}
