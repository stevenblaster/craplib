
#include "camera.h"

camera::camera()
{
	_updateRequired = false;

	_viewmat = glm::mat4( 1.0f );
	_orientation = glm::quat( 0.0f, 0.0f, 0.0f, 0.0f );

	_eye = glm::vec3( 0.0f );
	_axisX = glm::vec3( 1.0f, 0.0f, 0.0f );
	_axisY = glm::vec3( 0.0f, 1.0f, 0.0f );
	_axisZ = glm::vec3( 0.0f, 0.0f, 1.0f );
	_viewDir = glm::vec3( 0.0f, 0.0f, -1.0f  );
}

camera::~camera()
{
	;
}

void camera::lookAt( const glm::vec3 &target )
{
	lookAt( _eye, target, _axisY );
}

void camera::lookAt( const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up )
{
	_eye = eye;
	_axisZ = eye - target;
	glm::normalize( _axisZ );

	_viewDir = - _axisZ;

	_axisX = glm::cross( up, _axisZ );
	glm::normalize( _axisX );

	_axisY = glm::cross( _axisZ, _axisX );
	glm::normalize( _axisY );

	_viewmat[0][0] = _axisX.x;
	_viewmat[1][0] = _axisX.y;
	_viewmat[2][0] = _axisX.z;
	_viewmat[3][0] = -glm::dot( _axisX, _eye );

	_viewmat[0][1] = _axisY.x;
	_viewmat[1][1] = _axisY.y;
	_viewmat[2][1] = _axisY.z;
	_viewmat[3][1] = -glm::dot( _axisY, _eye );

	_viewmat[0][2] = _axisZ.x;
	_viewmat[1][2] = _axisZ.y;
	_viewmat[2][2] = _axisZ.z;
	_viewmat[3][2] = -glm::dot( _axisZ, _eye );

	_orientation = glm::toQuat( _viewmat );
}

void camera::move( float x, float y, float z )
{
	glm::vec3 eye = _eye;
	
	eye += _axisX * x;
	eye += glm::vec3( 0.0f, 1.0f, 0.0f ) * y;
	eye += _viewDir * z;

	setPosition( eye );
}

void camera::move( glm::vec3 direction, glm::vec3 length )
{
	_eye += direction.x * length.x;
	_eye += direction.y * length.y;
	_eye += direction.z * length.z;

	updateViewMatrix();
}

void camera::rotate( glm::vec3 &vec  )
{
	rotate( vec.x, vec.y, vec.z );
}

void camera::rotate( float yawDegrees, float pitchDegrees, float rollDegrees )
{

	pitchDegrees = -pitchDegrees;
	yawDegrees = -yawDegrees;
	rollDegrees = -rollDegrees;

	glm::quat rotation;


	rotation = glm::angleAxis(yawDegrees, 0.0f, 1.0f, 0.0f);
	_orientation = _orientation * rotation;
	rotation = glm::angleAxis(pitchDegrees, 1.0f, 0.0f, 0.0f);
	_orientation = rotation * _orientation;

	//glm::quat rot = glm::quat( glm::yawPitchRoll( headingDegrees, pitchDegrees, rollDegrees ) );


	//_orientation = _orientation * rot;

	updateViewMatrix();
}

void camera::setOrientation( const glm::quat &orientation )
{
	_orientation = orientation;

	updateViewMatrix();
}

void camera::setPosition( float x, float y, float z )
{
	_eye.x = x;
	_eye.y = y;
	_eye.z = z;

	updateViewMatrix();
}

void camera::setPosition( const glm::vec3 &position )
{
	_eye = position;
	updateViewMatrix();
}

void camera::updateViewMatrix( void )
{
	_viewmat = glm::toMat4( _orientation );

	_axisX = glm::vec3( _viewmat[0][0], _viewmat[1][0], _viewmat[2][0] );
	_axisY = glm::vec3( _viewmat[0][1], _viewmat[1][1], _viewmat[2][1] );
	_axisZ = glm::vec3( _viewmat[0][2], _viewmat[1][2], _viewmat[2][2] );
	_viewDir = -_axisZ;

	_viewmat[3][0] = - glm::dot( _axisX, _eye);
	_viewmat[3][1] = - glm::dot( _axisY, _eye);
	_viewmat[3][2] = - glm::dot( _axisZ, _eye);

}

glm::mat4 camera::getView( void )
{
	return _viewmat;
}