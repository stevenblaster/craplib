#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "threading/functorthread.h"
#include "threading/sleep.h"

struct dostuff
{
    void operator()( void )
    {
        std::cout << "Counting...";
        i32 tmp=0;
        while( tmp < 11 )
        {
            std::cout << tmp++ << ", ";
            //crap::sleep_msec(100);
        }
        std::cout << " done" << std::endl;
    }
};

namespace
{

crap::functor_thread<dostuff>* _functor_thread;

TEST(ThreadingFunctorThreadTitle)
{
    std::cout << "Testing \"threading/functorthread.h\"" << std::endl;
}

TEST(ThreadingFunctorThreadCreate)
{
    std::cout << "\tTesting Construction" << std::endl;
    _functor_thread = new crap::functor_thread<dostuff>();
}

TEST(ThreadingFunctorThreadStart)
{
    _functor_thread->start();
}

TEST(ThreadingFunctorThreadIsRunning)
{
    if( _functor_thread->is_running())
        std::cout << "\tThread is running" << std::endl;
    else
        std::cout << "\tThread is NOT running" << std::endl;
}

TEST(ThreadingFunctorThreadWait)
{
    std::cout << "\tWaiting for Thread" << std::endl;
    _functor_thread->join();
}

TEST(ThreadingFunctorThreadDestroy)
{
    std::cout << "\tTesting Destruction" << std::endl;
    delete _functor_thread;
}

}   // namespace

