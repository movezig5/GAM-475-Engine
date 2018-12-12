//----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
//----------------------------------------------------------------------------
// UnitTest 
//    v.2.1.0
//    v.2.1.1  - fixed C5038 warning
//    v.2.5
//    v.2.5.1 - Teardown - rework
//    v.2.6   - Baseline
//    v.2.6.1 - fixed warning TestRegistry
//    v.2.7   - Baseline
//    v.2.8   - warning 5039 windows.h
//    v.2.9   - fence
//    v.2.10  - msc_ver 1914, win 10.0.17
//    v.2.11  - warning fixes 
//    v.2.12  - mutex on all trace::out
//    v.2.13  - fixed warnings on mutex and default copy const / assignment
//    v.2.14  - FileIO remove new... so you can overload new/delete
//    v.2.15  - number tests pass reformat
//    v.2.16  - fixing static analysis issues
//    v.2.17  - missing deleted copy constructor and assignment operator in macro
//    v.2.18  - teardown issue
//---------------------------------------------------------------------------- 

#include "Framework.h"

Test::Test(const char * const pTestName) noexcept
	:UnitSLink(),
	pName(pTestName)
{
	// functional pointer
	this->testFunc = this;
	// register it
	TestRegistry::AddTest(this);

}

// ---  End of File ---------------
