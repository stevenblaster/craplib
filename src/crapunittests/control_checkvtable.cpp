#include "UnitTest++.h"

//lib includes
#include "control/checkvtable.h"

namespace
{

TEST(ControlCheckvtableTitle)
{
    std::cout << "Testing \"control/checkvtable.h\"" << std::endl;
}

TEST(ControlCheckvtableTrue)
{
	std::cout << "\tChecking positive virtual table" << std::endl;

	class vTrue
	{
		int number;
		virtual void method( void ) {}
	};

	CHECK_EQUAL( true, crap::has_vtable<vTrue>::RESULT );
}

TEST(ControlCheckvtableFalse)
{
	std::cout << "\tChecking negative virtual table" << std::endl;

	class vFalse
	{
		int number;
		void method( void ) {}
	};

	CHECK_EQUAL( false, crap::has_vtable<vFalse>::RESULT );
}

}   // namespace
