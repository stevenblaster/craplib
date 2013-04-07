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

	void lookAt( const glm::vec3 &target);
	void lookAt( const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up);

	void move( float x, float y, float z );
	void move( glm::vec3 direction, glm::vec3 length );

	void perspective( float fovx, float aspect, float znear, float zfar );
	void rotate( float headingDegrees, float pitchDegrees, float rollDegrees );
	void rotate( glm::vec3 &vec );
	void setOrientation( const glm::quat &orientation );
	void setPosition( float x, float y, float z );
	void setPosition( const glm::vec3 &position );
	void updateViewMatrix( void );

	glm::mat4 getView( void );

	
private:

	// internal position
	glm::quat _orientation;
	glm::vec3 _eye;

	glm::vec3 _axisX;
	glm::vec3 _axisY;
	glm::vec3 _axisZ;

	glm::vec3 _viewDir;

	glm::mat4 _viewmat;

	bool _updateRequired;

};
#endif // CAMERA_H