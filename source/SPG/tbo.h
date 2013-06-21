#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

class content_manager;
struct texture_content;

class tbo
{
public:
	enum image_type
	{
		bmp,
		tga,
		dds,
		depth
	};

	tbo( const crap::string64& id, content_manager* cm, image_type type );
	~tbo( void );

	void bind_buffer( void );
	void activate( void );

private:
	texture_content* _tex;
	crap::string64 _id;
	content_manager* _cm;
};


#endif // TEXTURE_H