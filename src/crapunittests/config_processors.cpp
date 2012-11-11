#include "UnitTest++.h"

//lib includes
#include "config/processors.h"

namespace
{

crap::cpu* test_cpu;

TEST(ConfigProcessorsTitle)
{
    std::cout << "Testing \"config/processors.h\"" << std::endl;
}

TEST(ConfigProcessorsCreate)
{
	test_cpu = new crap::cpu;
}

TEST(ConfigProcessorsDelete)
{
	delete test_cpu;
}

}   // namespace

