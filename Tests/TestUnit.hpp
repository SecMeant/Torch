#ifndef TESTUNIT_H
#define TESTUNIT_H

#include "../utility/stdshared.hpp"
#include "../Level/Level.hpp"
#include <stdio.h>

#include <assert.h>

class TestUnit
{
public:

	// Checks if Level class have its objects placed
	// in table at offset that are coords of an object
	void crashTestLevelClass();
};

#endif // TESTUNIT_H
