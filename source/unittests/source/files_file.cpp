#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "files/file.h"

class test_class
{
public:
    int integer;
    float flt;
};

class other_test_class : public test_class
{
public:
    int integer2;
    float flt2;
};

namespace
{

crap::file* _testfile;

TEST(FilesFileTitle)
{
    std::cout << "Testing \"files/file.h\"" << std::endl;
}

TEST(FilesFileConstructor)
{
	std::cout << "\tConstruction" << std::endl;
	_testfile = new crap::file( "testfile.txt" );
}

TEST(FilesFileReadableFailBecauseNotOpen)
{
	CHECK_EQUAL( false, _testfile->readable() );
}

TEST(FilesFileOpenRead)
{
	std::cout << "\tOpen file" << std::endl;
	_testfile->open( crap::file::read );
}

TEST(FilesFileReadableFailBecauseNotExist)
{
	CHECK_EQUAL( false, _testfile->readable() );
}

TEST(FilesFileCloseNonExist)
{
	_testfile->close();
}

TEST(FilesFileChangeFilename)
{
	_testfile->set_filename( "testwrite.txt" );
}

TEST(FilesFileOpenWrite)
{
	std::cout << "\tWrite text" << std::endl;
	_testfile->open( crap::file::write );
}

TEST(FilesFileWriteText)
{
	crap::string64 test_str("You man, you suck much.");
	_testfile->write_text(test_str);
}

TEST(FilesFileReadText)
{
	std::cout << "\tRead text" << std::endl;
	_testfile->open( crap::file::read ); //avoid flushing the file
	crap::string64 test_str;
	_testfile->read_text( test_str, 64 );
	CHECK( test_str == "You man, you suck much." );
}

TEST(FilesFileAppendText)
{
	std::cout << "\tAppend text" << std::endl;
	crap::string64 test_str(" Thanks, you too!");
	_testfile->append_text( test_str );
}

TEST(FilesFileWriteBinary)
{
	std::cout << "\tWrite binary" << std::endl;
	_testfile->set_filename( "binaryfile.bin" );
	_testfile->open( crap::file::write_binary );



	test_class tmp;
	tmp.flt = 0.1234f;
	tmp.integer = -234;

	_testfile->write_bytes( &tmp, sizeof(tmp) );
}

TEST(FilesFileReadBinary)
{
	std::cout << "\tRead binary" << std::endl;
	_testfile->open( crap::file::read_binary );



	test_class tmp;
	tmp.flt = 0.f;
	tmp.integer = 0;

	_testfile->read_bytes( &tmp, sizeof(tmp) );

	CHECK_EQUAL( 0.1234f, tmp.flt );
	CHECK_EQUAL( -234, tmp.integer );
}

TEST(FilesFileAppendBinary)
{
	std::cout << "\tAppend binary" << std::endl;
	_testfile->open( crap::file::append_binary );


	test_class tmp;
	tmp.flt = 5.345f;
	tmp.integer = 96;

	_testfile->append_bytes( &tmp, sizeof(tmp) );

	_testfile->open( crap::file::read_binary );



	other_test_class tmp2;
	tmp2.flt = 0.f;
	tmp2.integer = 0;
	tmp2.flt2 = 0.f;
	tmp2.integer2 = 0;

	_testfile->read_bytes( &tmp2, sizeof(tmp2) );

	CHECK_EQUAL( 0.1234f, tmp2.flt );
	CHECK_EQUAL( -234, tmp2.integer );
	CHECK_EQUAL( 5.345f, tmp2.flt2 );
	CHECK_EQUAL( 96, tmp2.integer2 );
}

TEST(FilesFileDestructor)
{
	delete _testfile;
}

}   // namespace

