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
	*test_cpu = crap::processor;
}

TEST(ConfigCompilerOutput)
{
	switch(*test_cpu)
	{
	case crap::x86:
		std::cout << "\tEnum: x86, Macro:" << CRAP_PROCESSOR_NAME << std::endl;
		break;
	case crap::x86_64:
		std::cout << "\tEnum: x68_64, Macro:" << CRAP_PROCESSOR_NAME << std::endl;
		break;
	case crap::arm:
		std::cout << "\tEnum: Arm, Macro:" << CRAP_PROCESSOR_NAME << std::endl;
		break;
	case crap::power_pc:
		std::cout << "\tEnum: PPC, Macro:" << CRAP_PROCESSOR_NAME << std::endl;
		break;
	case crap::ia64:
		std::cout << "\tEnum: IA64, Macro:" << CRAP_PROCESSOR_NAME << std::endl;
		break;
	default:
		std::cout << "\tEnum: None Macro:" << CRAP_PROCESSOR_NAME << std::endl;
	};
}

TEST(ConfigProcessorsDelete)
{
	delete test_cpu;
}

}   // namespace

