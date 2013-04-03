#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/fixedstring.h"

namespace
{

crap::fixed_string<64>* _fixedstring;

TEST(ContainerStaticstringTitle)
{
    std::cout << "Testing \"container/fixedstring.h\"" << std::endl;
}

TEST(ContainerStaticstringConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_fixedstring = new crap::fixed_string<64>;
}

TEST(StringCopyConstructorTest)
{
	std::cout << "\tdoing tests..." << std::endl;
	crap::string64 testString2( *_fixedstring );
	CHECK_EQUAL( (size_t32)0, testString2.size() );
}

TEST(StringCstringConstructorTest)
{
	crap::string64 testString2("IAmATest");
	CHECK_EQUAL((size_t32)8,testString2.size());
}

TEST(StringAssignmentOperator)
{
	crap::string64 testString2("IAmATest");
	*_fixedstring = testString2;
	CHECK_EQUAL((size_t32)8,_fixedstring->size());
}

TEST(StringCstringAssignmentOperator)
{
	crap::string64 testString2;
	testString2 = "IAmATest2";
	CHECK_EQUAL((size_t32)9,testString2.size());
}

TEST(StringConcatinateTest)
{
	crap::string64 testString2("Hello I am ");
	crap::string64 testString3("a Wiener.");
	crap::string64 testString4;

	testString4 += testString2;
	testString4 += testString3;

	//std::cout << testString2 << testString3 << " vs " << testString4 << std::endl;

	CHECK_EQUAL(testString2.size()+testString3.size(), testString4.size());
}

TEST(StringCharConcatinateTest)
{
	crap::string64 testString2("Hello I am ");
	testString2 += "a Wiener.";
	crap::string64 testString3("Hello I am a Wiener.");

	CHECK_EQUAL(testString2.size(), testString3.size());
}

TEST(StringComparisionTest)
{
	crap::string64 testString2 = "Hello I am a Wiener.";
	crap::string64 testString3 = "IAmATest";

	testString2 == testString3;

	CHECK_EQUAL( true, testString2 != *_fixedstring );
	CHECK_EQUAL( true, testString3 == *_fixedstring );
	CHECK_EQUAL( false, testString2 == testString3 );
}

TEST(StringIndexoperator)
{
	crap::string64 testString2 = "Hello I am a Wiener.";

	CHECK_EQUAL('e', testString2[1]);
	CHECK_EQUAL('l', testString2[3]);
	CHECK_EQUAL(' ', testString2[5]);
}

TEST(StringTestContains)
{
	crap::string64 testString2 = "Hello I am a Wiener.";
	crap::string64 testString3 = " am a W";
	crap::string64 testString4 = "Mama spielt Karten";

	CHECK_EQUAL(true, testString2.contains("lo I"));
	CHECK_EQUAL(true, testString2.contains("iener."));
	CHECK_EQUAL(false, testString2.contains("Mama spielt Karten"));

	CHECK_EQUAL(true, testString2.contains(testString3));
	CHECK_EQUAL(false, testString2.contains(testString4));
}

TEST(StringTestSearch)
{
	crap::string64 testString2 = "Hello I am a Wiener.";
	crap::string64 testString3 = " am a W";
	crap::string64 testString4 = "i";

	CHECK_EQUAL(3, testString2.search("lo I"));
	CHECK_EQUAL(14, testString2.search("iener."));
	CHECK_EQUAL(-1, testString2.search("Mama"));

	CHECK_EQUAL(7, testString2.search(testString3));
	CHECK_EQUAL(14, testString2.search(testString4));
}

TEST(StringSubStringTest)
{
	crap::string64 testString2 = "Hello I am a Wiener.";
	crap::string64 testString3 = " am a W";

	crap::string64 testString5 = "llo I";
	crap::string64 testString4 = testString2.substr(7,7);

	CHECK_EQUAL(true, testString3 == testString4);
	CHECK_EQUAL(true, testString5 == testString2.substr(testString2.search(testString5), testString5.size()));
}

TEST(StringCutTest)
{
	crap::string64 testString2 = "Hello I am a Wiener.";
	crap::string64 testString3 = "Hello I am";

	testString2.cut(testString3.size());

	CHECK_EQUAL(true, testString2 == testString3);
}

TEST(StringTrimTest)
{
	crap::string64 testString2 = "  Hello I am a Wiener.";
	crap::string64 testString3 = "Hello I am a Wiener.   ";
	crap::string64 testString4 = " Hello I am a Wiener. ";

	testString2.trim();
	testString3.trim();
	testString4.trim();

	CHECK_EQUAL(true, testString2 == testString3);
	CHECK_EQUAL(true, testString2 == testString4);
	CHECK_EQUAL(true, testString3 == testString4);
}

TEST(StringSplitAndMergeTest)
{
	crap::string64 testString2 = "Hello, I am a Wiener.";
//        std::cout << "before split" << std::endl;
	crap::vector<crap::string64> testList = testString2.split(' ');
//              std::cout << "after split" << std::endl;
	//for(u64 i=0; i<testList.size(); ++i)
	//{
	//	std::cout << testList[i] << std::endl;
	//}

	crap::string64 testString3;
	testString3.merge(testList, '&');
   //std::cout << testString3 << std::endl;
}

TEST(ContainerStaticstringDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete 	_fixedstring;
}

}   // namespace
