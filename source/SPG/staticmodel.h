#pragma once

#ifndef MODEL_H
#define MODEL_H

class static_model
{
public:
	model( const crap::string64& vbo, 
		const crap::string64& diff, const crap::string64& bump, const crap::string64& spec, 
		const crap::string64& vs, const crap::string64& ps );
	~model( void );

	void draw( void );
};

#endif //MODEL_H