#include "../precompiled.hpp"
#include "job_base.hpp"
#include "singletons/job_dispatcher.hpp"
using namespace Poseidon;

JobBase::~JobBase(){
}

void JobBase::pend(){
	JobDispatcher::pend(virtualSharedFromThis<JobBase>());
}
