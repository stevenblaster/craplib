#include "UnitTest++.h"
#include "crap.h"

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
    std::cout << "Testing \"control/copyobject.h\" (copy_array)" << std::endl;
	std::cout << "\tTesting copy_array" << std::endl;
}

TEST(ControlCopyobjectVT)
{


	hasvt* tmp = (hasvt*) malloc( sizeof(hasvt)*3);
	tmp[0].somedata = 1;
	tmp[1].somedata = 2;
	tmp[2].somedata = 3;

	hasvt* tmp2 = (hasvt*) malloc( sizeof(hasvt)*3);
	memset(tmp2, 0, sizeof(hasvt) * 3);

	crap::copy_array<hasvt>(tmp, tmp2, 3);

	CHECK_EQUAL(1, tmp2[0].somedata );
	CHECK_EQUAL(2, tmp2[1].somedata );
	CHECK_EQUAL(3, tmp2[2].somedata );
}

TEST(ControlCopyobjectNVT)
{


	hasnvt* tmp = (hasnvt*) malloc( sizeof(hasnvt)*3);
	tmp[0].somedata = 1;
	tmp[1].somedata = 2;
	tmp[2].somedata = 3;

	hasnvt* tmp2 = (hasnvt*) malloc( sizeof(hasnvt)*3);
	memset(tmp2, 0, sizeof(hasnvt) * 3);

	crap::copy_array<hasnvt>(tmp, tmp2, 3);

	CHECK_EQUAL(1, tmp2[0].somedata );
	CHECK_EQUAL(2, tmp2[1].somedata );
	CHECK_EQUAL(3, tmp2[2].somedata );
}

}   // namespace
