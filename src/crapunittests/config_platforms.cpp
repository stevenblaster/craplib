#include "UnitTest++.h"

//lib includes
#include "config/platforms.h"

namespace
{

crap::os* test_os;

TEST(ConfigPlatformsTitle)
{
    std::cout << "Testing \"config/platforms.h\"" << std::endl;
}

TEST(ConfigPlatformsCreate)
{
	test_os = new crap::os;
}

TEST(ConfigPlatformsDelete)
{
	delete test_os;
}

}   // namespace

