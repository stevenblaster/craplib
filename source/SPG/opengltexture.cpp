////////////////////////////////////////////////////////
// CRAP Library
//!		@file opengltexture.cpp
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Loads and uses an image for opengl
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "GL/glew.h"
#include "GL/glfw.h"

#include "container/string.h"
#include "files/file.h"
#include "files/fileheaders.h"
#include "opengl/opengltexture.h"

//lib namespace
namespace crap
{

//ogl namespace
namespace opengl
{

texture::~texture( void )
{
	glDeleteTextures(1, &_id);
}

texture::texture( u32 id , u32 index ) : _id(id), _index(index)
{

}

texture::texture( const texture& other )  : _id(other._id), _index(other._index)
{

}

texture& texture::operator=( const texture& other )
{
	_id = other._id;
	_index = other._index;
	return *this;
}

void texture::bind( void )
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

void texture::activate( void )
{
	glActiveTexture(_index);
}

u32 create_texture_bmp( const char* name )
{
	bmp_header head;
	file bmp_file(name);
	CRAP_ASSERT_DEBUG( bmp_file.readable(), "BMP File does not exist or is not readable" );
	bmp_file.read_bytes( &head, sizeof(head) );
	CRAP_ASSERT_DEBUG( head.validate(), "Not a valid BMP-file" );

	if( head.size_of_image == 0 )
		head.size_of_image = head.width * head.height * 3; // 3 = RGB

	if( head.offset == 0 )
		head.offset = 54; //default

	u8* data = new u8[ head.size_of_image ];
	bmp_file.read_bytes( data, head.size_of_image );
	bmp_file.close();

	// Create one OpenGL texture
	u32 id;
	glGenTextures(1, &id);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, id);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, head.width, head.height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return id;
}

u32 create_texture_tga( const char* name )
{
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Read the file, call glTexImage2D with the right parameters
	glfwLoadTexture2D(name, 0);

	// Nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}

u32 create_texture_dds( const char* name )
{
	dds_header head;
	file dds_file( name );
	CRAP_ASSERT_DEBUG( dds_file.readable(), "DDS File does not exist or is not readable" );
	dds_file.read_bytes( &head, sizeof(head) );
	CRAP_ASSERT_DEBUG( head.validate(), "Not a valid DDS-file" );

	//int fun = sizeof(head);
	u32 buffer_size = (size_t32) dds_file.size() - sizeof(head);
	//u32 buffer_size = head.mip_map_count > 1 ? head.pitch_or_linear_s * 2 : head.pitch_or_linear_s; 
	u8* buffer = new u8[buffer_size];
	dds_file.read_bytes( buffer, buffer_size );
	dds_file.close();

	u32 components = (head.pixelformat.pf_four_cc == FOURCC_DXT1) ? 3 : 4; 
	u32 format;
	switch( head.pixelformat.pf_four_cc ) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		delete[] buffer;
		CRAP_ASSERT_ERROR("DDS format invalid");
	}

	// Create one OpenGL texture
	u32 textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	u32 blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	u32 offset = 0;

	/* load the mipmaps */ 
	for (i32 level = 0; level < head.mip_map_count && (head.width || head.height); ++level) 
	{ 
		u32 size = ((head.width+3)/4)*((head.height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, head.width, head.height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		head.width  /= 2; 
		head.height /= 2; 
	} 

	delete[] buffer; 
	return textureID;
}

texture create_texture( const char* name, image_type type )
{
	i32 ogl_id[]= {GL_TEXTURE0,GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5,
		GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13,
		GL_TEXTURE14, GL_TEXTURE15, GL_TEXTURE16, GL_TEXTURE17, GL_TEXTURE18, GL_TEXTURE19, GL_TEXTURE20,
		GL_TEXTURE21, GL_TEXTURE22, GL_TEXTURE23, GL_TEXTURE24, GL_TEXTURE25, GL_TEXTURE26, GL_TEXTURE27,
		GL_TEXTURE28, GL_TEXTURE29, GL_TEXTURE30, GL_TEXTURE31 };
		/* .. continue .. */

	static i32 index_counter = 0;
	if( type == bmp )
	{
		u32 id = create_texture_bmp( name );
		u32 index = ogl_id[index_counter++];
		return texture(id, index);
	}

	if( type == tga )
	{
		u32 id = create_texture_tga( name );
		u32 index = ogl_id[index_counter++];
		return texture(id, index);
	}

	if( type == dds )
	{
		u32 id = create_texture_dds( name );
		u32 index = ogl_id[index_counter++];
		return texture(id, index);
	}

	CRAP_ASSERT_ERROR("Unknown image type");
	return texture(0,0);
}

} // amespace opengl

} //namespace crap