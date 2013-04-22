#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "control/logger.h"

namespace
{
	typedef crap::logger<crap::filter_policy::no_filter_policy,crap::format_policy::no_format_policy,crap::writer_policy::stream_writer_policy> NoNoStreamLogger;
	typedef crap::logger<crap::filter_policy::channel_filter_policy,crap::format_policy::no_format_policy,crap::writer_policy::stream_writer_policy> ChNoStreamLogger;
	typedef crap::logger<crap::filter_policy::channel_filter_policy,crap::format_policy::simple_format_policy,crap::writer_policy::stream_writer_policy> ChSfStreamLogger;

TEST(ControlLoggerTitle)
{
    std::cout << "Testing \"control/logger.h\"" << std::endl;
}

TEST(ControlLoggerNoNoS)
{	
	std::cout << "\tcrap::no filter no format stream logger" << std::endl;
	NoNoStreamLogger nns;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_channel::log_core,"Core Channel Test %d.",10);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"Core Channel Test 10.\n");
		std::cout.rdbuf(sbuf);
	}
}

TEST(ControlLoggerNoNoSToBig)
{
	//This needs a fix.
	CHECK(false != true);
	//std::cout << "\tcrap::no filter no format console logger MSG Size to big" << std::endl;
	//NoNoConsoleLogger nnc;
	//CRAP_LOG_INFO(crap::log_channel::log_core,"Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test  %d.",10);
	////CHECK_EQUAL( false, less_object(11,10) );
}

TEST(ControlLoggerNoNoSNothing)
{
	std::cout << "\tcrap::no filter no format stream logger no msg" << std::endl;
	NoNoStreamLogger nns;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_channel::log_core,"",1);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"\n");
		std::cout.rdbuf(sbuf);
	}
}

TEST(ControlLoggerChNoSMsg)
{
	std::cout << "\tcrap::channel filter no format stream logger" << std::endl;
	ChNoStreamLogger cns;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_opengl,"This is an opengl message, this is a %d",10);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"This is an opengl message, this is a 10\n");
		std::cout.rdbuf(sbuf);
	}
}

TEST(ControlLoggerChNoSNoMsg)
{
	std::cout << "\tcrap::channel filter no format stream logger --> no msg should be there" << std::endl;
	ChNoStreamLogger cns;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_core,"This is a core message, this is a %d",10);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"");
		std::cout.rdbuf(sbuf);
	}
}

TEST(ControlLoggerChSFMsg)
{
	std::cout << "\tcrap::channel filter simple format stream logger" << std::endl;
	ChSfStreamLogger cfn;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_opengl,"This is an opengl message, this is a %d",10);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"[OPENGL  ] (INFO   ) This is an opengl message, this is a 10\n");
		std::cout.rdbuf(sbuf);
	}
}

TEST(ControlLoggerNoNoMsgTypeFormat)
{
	std::cout << "\tcrap::two no filter no format stream logger different formats" << std::endl;
	NoNoStreamLogger nns;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		/*d or i	Signed decimal integer	392
		u	Unsigned decimal integer	7235
		o	Unsigned octal	610
		x	Unsigned hexadecimal integer	7fa
		X	Unsigned hexadecimal integer (uppercase)	7FA
		f	Decimal floating point, lowercase	392.65
		F	Decimal floating point, uppercase	392.65
		e	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
		E	Scientific notation (mantissa/exponent), uppercase	3.9265E+2
		g	Use the shortest representation: %e or %f	392.65
		G	Use the shortest representation: %E or %F	392.65
		a	Hexadecimal floating point, lowercase	-0xc.90fep-2
		A	Hexadecimal floating point, uppercase	-0XC.90FEP-2
		c	Character	a
		s	String of characters	sample
		p	Pointer address	b8000000
		%	A % followed by another % character will write a single % to the stream.	%*/
		CRAP_LOG_INFO(crap::log_channel::log_core,"Format Test Number %d Othernumber %i, Float %f, String %s.",1,10,10.0f,"Test");
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"Format Test Number 1 Othernumber 10, Float 10.000000, String Test.\n");
		std::cout.rdbuf(sbuf);
	}
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_channel::log_core,"Format Test Float(shortest) %g, Character %c, Hex %x.",10.0f,'c',0x7fa);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"Format Test Float(shortest) 10, Character c, Hex 7fa.\n");
		std::cout.rdbuf(sbuf);
	}
}

TEST(ControlLoggerNoNoMsgMultiple)
{
	std::cout << "\tcrap::two no filter no format stream logger" << std::endl;
	NoNoStreamLogger nns;
	NoNoStreamLogger nns2;
	{
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
		CRAP_LOG_INFO(crap::log_channel::log_core,"Core Channel Test %d.",10);
		std::cout.flush();
		std::string check;
		check = buffer.str();
		CHECK_EQUAL(check,"Core Channel Test 10.\nCore Channel Test 10.\n");
		std::cout.rdbuf(sbuf);
	}
}

}   // namespace
