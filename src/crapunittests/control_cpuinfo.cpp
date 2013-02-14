#include "UnitTest++.h"

//lib includes
#include "control/cpuinfo.h"

namespace
{

crap::cpu_info& cpu_inf = crap::cpu_info::instance();

TEST(ControlCpuinfoTitle)
{
    std::cout << "Testing \"control/cpuinfo.h\"" << std::endl;
}

TEST(ControlCpuinfoPrintinfo)
{
	std::cout << "\tVendor: " << cpu_inf.vendor() << std::endl;
	std::cout << "\tType: " << cpu_inf.type_string() << std::endl;
	std::cout << "\tFamily: " << cpu_inf.family_string() << std::endl;
	std::cout << "\tSIMD type: " << cpu_inf.detectedSIMD() << " (" << cpu_inf.simd_string() << ")" << std::endl;
}

}   // namespace
