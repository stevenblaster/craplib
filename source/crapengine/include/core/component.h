#include <typeinfo>

class Component
{
	bool is_type( std::type_info obj ) const
	{
		return typeid(*this) == obj;
	}
};

class Node
{
	Component* _start;
	Component* _last;

	template<typename T>
	Component* getComponent( void ) const
	{
		//search
		for( /* ..go through intrusive list .. */ )
		{
			Component* current = 0; 
			if( current->is_type( typeid(T) ) )
			{
				return current;
			}
		}
		return 0;
	}
};