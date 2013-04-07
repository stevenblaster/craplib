#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "precompiled.h"

class camera
{

public:

	camera();
	~camera();

	void set_rotation( const glm::quat &rotation );
	void set_position( const glm::vec3 &position );
	void lookat(const glm::vec3& pos, const glm::vec3& focalpoint, const glm::vec3& up);

	glm::mat4 get_view();

	void up( void );
	void down( void );
	void left( void );
	void right( void );
	void forward( void );
	void backward( void );

	void turn( const glm::vec3& movment );
	void roll( const float& angle );
	void yaw( const float& angle );
	void pitch( const float& angle );
	
private:

	// internal position
	glm::quat _orientation;
	glm::vec3 _position;

	// viewmat cached for performance
	glm::mat4 _viewmat;
	bool _updateRequired;

	// helper functions for implementation
	glm::vec3 get_up( void );
	glm::vec3 get_right( void );
	glm::vec3 get_lookat( void );

	// cache vars for movment
	glm::vec3 _movementChange;
	glm::vec3 _directionChange;

};
#endif // CAMERA_H