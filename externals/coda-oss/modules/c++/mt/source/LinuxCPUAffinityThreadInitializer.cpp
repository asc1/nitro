/* =========================================================================
 * This file is part of mt-c++ 
 * =========================================================================
 * 
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
 *
 * mt-c++ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program; If not, 
 * see <http://www.gnu.org/licenses/>.
 *
 */


#include "mt/LinuxCPUAffinityThreadInitializer.h"

#if !defined(__APPLE_CC__)
#if defined(__linux) || defined(__linux__)

mt::LinuxCPUAffinityThreadInitializer::
LinuxCPUAffinityThreadInitializer(const cpu_set_t& cpu)
{
    for (int i = 0; i < CPU_SETSIZE; ++i)
    {
	CPU_CLR(i, &mCPU);
	if (CPU_ISSET(i, &cpu))
	    CPU_SET(i, &mCPU);
    }
    
}

void mt::LinuxCPUAffinityThreadInitializer::initialize()
{
    pid_t tid = 0;
    tid = ::gettid();
    if ( ::sched_setaffinity(tid, sizeof(mCPU), &mCPU) == -1 )
    {
	sys::Err e;
	std::ostringstream errStr;
	errStr << "Failed setting processor affinity: " << e.toString();
	throw except::Exception(Ctxt(errStr.str()));
    }
}
#endif
#endif
