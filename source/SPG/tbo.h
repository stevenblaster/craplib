#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

namespace crap
{
	class texture;
}

class content_manager;

class tbo
{
public:
	enum image_type
	{
		bmp,
		tga,
		dds
	};

	tbo( const crap::string64& id, content_manager* cm, image_type type );
	~tbo( void );

	void bind_buffer( void );
	void activate( void );

private:
	crap::texture* _tex;
};


#endif // TEXTURE_H