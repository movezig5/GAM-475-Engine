//---------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"
#include "MathEngine.h"

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST(Get_Accessors, vector_tests)
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);

	CHECK(A.x() == 2.0f);
	CHECK(A.y() == 3.0f);
	CHECK(A.z() == 4.0f);
	CHECK(A.w() == 5.0f);
}

float constTestAccessor(const Vect &t)
{
	return (t.x() + t.y() + t.z() + t.w());
}

TEST(Get_Accessors_const, vector_tests)
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);

	float sum = constTestAccessor(A);

	CHECK(sum == 14.0f);

	CHECK(A.x() == 2.0f);
	CHECK(A.y() == 3.0f);
	CHECK(A.z() == 4.0f);
	CHECK(A.w() == 5.0f);
}


TEST(Set_Accessors, vector_tests)
{
	Vect A(0.0f, 0.0f, 0.0f, 0.0f);

	CHECK(A.x() == 0.0f);
	CHECK(A.y() == 0.0f);
	CHECK(A.z() == 0.0f);
	CHECK(A.w() == 0.0f);

	A.x() = 2.0f;
	A.y() = 3.0f;
	A.z() = 4.0f;
	A.w() = 5.0f;

	CHECK(A.x() == 2.0f);
	CHECK(A.y() == 3.0f);
	CHECK(A.z() == 4.0f);
	CHECK(A.w() == 5.0f);
}

TEST(Set_Accessors_get, vector_tests)
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);

	CHECK(A.x() == 2.0f);
	CHECK(A.y() == 3.0f);
	CHECK(A.z() == 4.0f);
	CHECK(A.w() == 5.0f);

	float tx, ty, tz, tw;

	tx = A.x();
	ty = A.y();
	tz = A.z();
	tw = A.w();

	CHECK(tx == 2.0f);
	CHECK(ty == 3.0f);
	CHECK(tz == 4.0f);
	CHECK(tw == 5.0f);
}

// ---  End of File ---------------
