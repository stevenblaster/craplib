
#include "camera.h"

camera::camera()
{
	_updateRequired = false;
	_viewmat = glm::mat4( 1.0f );
	_orientation = glm::quat( 0.0f, 0.0f, 0.0f, 0.0f );
	_position = glm::vec3( 0.0f );
}

camera::~camera()
{
	;
}

void camera::set_rotation( const glm::quat& rotation )
{
	this->_orientation = rotation;
	_updateRequired = true;
}

void camera::set_position( const glm::vec3& position )
{
	this->_position = position;
	_updateRequired = true;
}

void camera::lookat( const glm::vec3& pos, const glm::vec3& focalpoint, const glm::vec3& up )
{
	_updateRequired = true;
	glm::mat4 temp = glm::lookAt( pos, focalpoint, up );
	_position[0] = temp[3][0];
	_position[1] = temp[3][1];
	_position[2] = temp[3][2];
	_orientation = glm::toQuat( temp );
}

// Movement
void camera::left()
{
	_updateRequired = true;
	_movementChange.x = 1;
}

void camera::right()
{
	_updateRequired = true;
	_movementChange.x = -1;
}

void camera::up()
{
	_updateRequired = true;
	_movementChange.y = 1;
}

void camera::down()
{
	_updateRequired = true;
	_movementChange.y = -1;
}

void camera::forward()
{
	_updateRequired = true;
	_movementChange.z = 1;
}

void camera::backward()
{
	_updateRequired = true;
	_movementChange.z = -1;
}

// Rotation

void camera::turn( const glm::vec3& movement )
{	
	glm::vec3 move = movement / 1000.0f;
	pitch(move.x);
	yaw(move.y);
	roll(move.z);
}

void camera::roll( const float& angle )
{
	_updateRequired = true;
	_directionChange.x = angle;
}

void camera::yaw( const float& angle )
{
	_updateRequired = true;
	_directionChange.y = angle;
}

void camera::pitch( const float& angle )
{
	_updateRequired = true;
	_directionChange.z = angle;
}

glm::mat4 camera::get_view( void )
{
	if(_updateRequired)
	{
		// update orientation
		glm::quat rotation;
		rotation = glm::angleAxis( _directionChange.y, 0.0f, 1.0f, 0.0f );
		rotation = glm::angleAxis( _directionChange.x, 1.0f, 0.0f, 0.0f ) * rotation;
		rotation = glm::angleAxis( _directionChange.z, 0.0f, 0.0f, 1.0f ) * rotation;
		_orientation = rotation * _orientation;
		_orientation = glm::normalize( _orientation );
		
		_viewmat = glm::toMat4( _orientation );

		_viewmat[3][0] = _position.x;
		_viewmat[3][1] = _position.y;
		_viewmat[3][2] = _position.z;
		_viewmat[3][3] = 1.0f;

		// reset caches
		_directionChange = glm::vec3( 0.0f );
		_movementChange = _directionChange;
		_updateRequired = false;
	}
	return _viewmat;
}

glm::vec3 camera::get_up( void )
{
	glm::mat3 rotationMatrix = glm::toMat3( _orientation );
	return glm::vec3( rotationMatrix[0][1], -rotationMatrix[1][1], rotationMatrix[2][1] );
}

glm::vec3 camera::get_lookat( void )
{
	glm::mat3 rotationMatrix = glm::toMat3( _orientation );
	return glm::vec3( rotationMatrix[0][0], rotationMatrix[1][0], -rotationMatrix[2][0] );
}

glm::vec3 camera::get_right( void )
{
	glm::mat3 rotationMatrix = glm::toMat3( _orientation );
	return glm::vec3( -rotationMatrix[0][2], rotationMatrix[1][2], rotationMatrix[2][2] );
}

