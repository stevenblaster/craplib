#include "UnitTest++.h"

//lib includes
#include "control/copyobject.h"

class hasvt
{
public:
    int somedata;
    hasvt(int fun) : somedata(fun) {}
    virtual ~hasvt(){}
};

class hasnvt
{
public:
    int somedata;
    hasnvt(int fun) : somedata(fun) {}
    ~hasnvt(){}
};

namespace
{

TEST(ControlCopyobjectTitle)
{
    std::cout << "Testing \"control/copyobject.h\" (copy_object)" << std::endl;
	std::cout << "\tTesting copy_object" << std::endl;
}

TEST(ControlCopyobjectVT)
{


	hasvt tmp(4);
	hasvt tmp2(0);

	crap::copy_object<hasvt>(&tmp, &tmp2);

	CHECK_EQUAL(4, tmp2.somedata );
}

TEST(ControlCopyobjectNVT)
{


	hasnvt tmp(4);
	hasnvt tmp2(0);

	crap::copy_object<hasnvt>(&tmp, &tmp2);

	CHECK_EQUAL(4, tmp2.somedata );
}

}   // namespace
