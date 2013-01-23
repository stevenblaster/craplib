#include "UnitTest++.h"

//lib includes
#include "config/compilers.h"

namespace
{

crap::compiler_type* test_compiler_type;

TEST(ConfigCompilerTitle)
{
    std::cout << "Testing \"config/compiler.h\"" << std::endl;
}

TEST(ConfigCompilerCreate)
{
	test_compiler_type = new crap::compiler_type;
	*test_compiler_type = crap::compiler;
}

TEST(ConfigCompilerOutput)
{
	switch(*test_compiler_type)
	{
	case crap::gcc:
		std::cout << "\tEnum: GCC Macro:" << CRAP_COMPILER_NAME << std::endl;
		break;
	case crap::vc:
		std::cout << "\tEnum: VS-compiler Macro:" << CRAP_COMPILER_NAME << std::endl;
		break;
	case crap::borland:
		std::cout << "\tEnum: Borland compiler Macro:" << CRAP_COMPILER_NAME << std::endl;
		break;
	case crap::intel:
		std::cout << "\tEnum: Intel compiler Macro:" << CRAP_COMPILER_NAME << std::endl;
		break;
	default:
		std::cout << "\tEnum: None Macro:" << CRAP_COMPILER_NAME << std::endl;
	};
}

TEST(ConfigCompilerDelete)
{
	delete test_compiler_type;
}

}   // namespace
