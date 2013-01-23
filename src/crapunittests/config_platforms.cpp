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
	*test_os = crap::platform;
}

TEST(ConfigPlatformsOutput)
{
	switch(*test_os)
	{
	case crap::platform_windows:
		std::cout << "\tEnum: Windows, Macro:" << CRAP_PLATFORM_NAME << std::endl;
		break;
	case crap::platform_linux:
		std::cout << "\tEnum: Linux, Macro:" << CRAP_PLATFORM_NAME << std::endl;
		break;
	case crap::platform_macintosh:
		std::cout << "\tEnum: Mac, Macro:" << CRAP_PLATFORM_NAME << std::endl;
		break;
	case crap::platform_ios:
		std::cout << "\tEnum: IOS, Macro:" << CRAP_PLATFORM_NAME << std::endl;
		break;
	case crap::platform_unix:
		std::cout << "\tEnum: Unix, Macro:" << CRAP_PLATFORM_NAME << std::endl;
		break;
	default:
		std::cout << "\tEnum: None Macro:" << CRAP_PLATFORM_NAME << std::endl;
	};
}

TEST(ConfigPlatformsDelete)
{
	delete test_os;
}

}   // namespace

