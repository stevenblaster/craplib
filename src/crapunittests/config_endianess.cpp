#include "UnitTest++.h"

//lib includes
#include "config/endianness.h"

namespace
{

TEST(ConfigEndianessTitle)
{
    std::cout << "Testing \"config/endianess.h\"" << std::endl;
}

TEST(ConfigEndianessMacro)
{
	std::cout << "\tMacro: Endian is " << CRAP_ENDIAN_TYPE << std::endl;
}

}   // namespace

