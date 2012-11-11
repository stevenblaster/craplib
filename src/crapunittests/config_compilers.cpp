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
}

TEST(ConfigCompilerDelete)
{
	delete test_compiler_type;
}

}   // namespace
