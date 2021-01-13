#ifndef __RAY_JOBS_HPP__
#define __RAY_JOBS_HPP__

#include <thread>
#include <mutex>
#include <queue>

class Job {

};

class RayJobs {
	public:
		RayJobs(int numThread);
		j

	private:
		std::queue<Job> jobQ;
		std::mutex		jobM;
};

#endif
