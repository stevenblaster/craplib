
#include "camera.h"

camera::camera()
{
	update = false;
	viewmat = glm::mat4(1.0f);
	rotation = glm::toQuat(glm::mat4(1.0f));
	position = glm::vec3(0.0f);
}

camera::~camera()
{
	;
}

void camera::set_rotation(const glm::quat rotation)
{
	this->rotation = rotation;
	update = true;
}

void camera::set_position(const glm::vec3 position)
{
	this->position = position;
	update = true;
}

void camera::up()
{
	update = true;
	glm::vec3 dir = get_up();
	dir *= 0.01f;
	move(dir);
}

void camera::down()
{
	update = true;
	glm::vec3 dir = get_up();
	dir *= -0.01f;
	move(dir);
}

void camera::right()
{
	update = true;
	glm::vec3 dir = get_right();
	dir *= 0.01f;
	move(dir);
}

void camera::left()
{
	update = true;
	glm::vec3 dir = get_right();
	dir *= -0.01f;
	move(dir);
}

void camera::forward()
{
	update = true;
	glm::vec3 dir = get_lookat();
	dir *= 0.01f;
	move(dir);
}

void camera::backward()
{
	update = true;
	glm::vec3 dir = get_lookat();
	dir *= -0.01f;
	move(dir);
}

void camera::turnup()
{
	update = true;
	glm::vec3 up(1.0, 0.0f, 0.0);
	glm::quat rot(0.001f, up);
	rotation = rotation * rot;
}

void camera::turndown()
{
	update = true;
	glm::vec3 down(-1.0, 0.0f, 0.0);
	glm::quat rot(0.001f, down);
	rotation = rotation * rot;
}

void camera::turnleft()
{
	update = true;
	glm::vec3 left(0.0, -1.0f, 0.0);
	glm::quat rot(0.001f, left);
	rotation = rotation * rot;
}

void camera::turnright()
{
	update = true;
	glm::vec3 right(0.0, 1.0f, 0.0);
	glm::quat rot(0.001f, right);
	rotation = rotation * rot;
}

glm::mat4 camera::get_view()
{
	if(update)
	{
		glm::mat4 orientation = glm::toMat4(rotation);
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		viewmat = translation * orientation;
		update = false;
	}
	return viewmat;
}

glm::vec3 camera::get_up()
{
	glm::mat3 rotationMatrix = glm::toMat3(rotation);
	return glm::vec3( rotationMatrix[0][1], -rotationMatrix[1][1], rotationMatrix[2][1] );
}

glm::vec3 camera::get_lookat()
{
	glm::mat3 rotationMatrix = glm::toMat3(rotation);
	return glm::vec3( rotationMatrix[0][0], rotationMatrix[1][0], -rotationMatrix[2][0] );
}

glm::vec3 camera::get_right()
{
	glm::mat3 rotationMatrix = glm::toMat3(rotation);
	return glm::vec3( -rotationMatrix[0][2], rotationMatrix[1][2], rotationMatrix[2][2] );
}

void camera::move( glm::vec3 dir )
{
	position += dir;
	return;
}

void camera::lookat( const glm::vec3 pos, const glm::vec3 focalpoint, const glm::vec3 up )
{
	update = true;
	glm::mat4 temp = glm::lookAt(pos, focalpoint, up);
	position[0] = temp[3][0];
	position[1] = temp[3][1];
	position[2] = temp[3][2];
	rotation = glm::toQuat(temp);
}
