#include "crap.h"

#include "control/craptime.h"
#include "container/binarytree.h"
#include "math/random.h"


int main()
{
	i32 time = 0;

	//BINARY TREE
	std::cout << "=== Testing binary tree ===" << std::endl;
	crap::binary_tree<i32>* bin_tree = new crap::binary_tree<i32>();

    std::cout << "\t inserting 1000 integers" << std::endl;
	time = crap::time::current_tick();
    for(int i=0; i<1000; ++i)
	{
		bin_tree->insert(i);
	}
	std::cout << "\t\t"<< (f32)( (i32)crap::time::current_tick() - time ) / crap::time::TICKS_PER_SECOND << " seconds" << std::endl;

	std::cout << "\t realigning tree" << std::endl;
	time = crap::time::current_tick();
	bin_tree->realign();
	std::cout << "\t\t"<< (f32)( (i32)crap::time::current_tick() - time ) / crap::time::TICKS_PER_SECOND << " seconds" << std::endl;

    std::cout << "\t searching 1000 random integers" << std::endl;
	time = crap::time::current_tick();
    for(int i=0; i<1000; ++i)
	{
        bin_tree->find( crap::random<int>::range(0, 999) );
	}
	std::cout << "\t\t"<< (f32)( (i32)crap::time::current_tick() - time ) / crap::time::TICKS_PER_SECOND << " seconds" << std::endl;

    std::cout << "\t deleting 1000 integers" << std::endl;
	time = crap::time::current_tick();
    for(int i=0; i<1000; ++i)
	{
		bin_tree->remove(i);
	}
	std::cout << "\t\t"<< (f32)( (i32)crap::time::current_tick() - time ) / crap::time::TICKS_PER_SECOND << " seconds" << std::endl;
}
