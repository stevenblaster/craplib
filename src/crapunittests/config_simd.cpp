#include "UnitTest++.h"

//lib includes
#include "config/simd.h"

namespace
{

TEST(ConfigSimdTitle)
{
    std::cout << "Testing \"config/simd.h\"" << std::endl;
}

TEST(ConfigSimdMacros)
{
	std::cout << "\tSIMD Version: " << CRAP_SIMD_VERSION << ", Named: " << CRAP_SIMD_NAME << std::endl;
}

}   // namespace

