#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class camera
{

public:

	camera();
	~camera();

	void set_rotation(const glm::quat rotation);
	void set_position(const glm::vec3 position);
	void lookat(const glm::vec3 pos, const glm::vec3 focalpoint, const glm::vec3 up);

	glm::mat4 get_view();

	void up();
	void down();
	void left();
	void right();
	void forward();
	void backward();

	void turnleft();
	void turnright();
	void turnup();
	void turndown();
	
private:

	// internal position
	glm::quat rotation;
	glm::vec3 position;

	// viewmat cached for performance
	glm::mat4 viewmat;
	bool update;

	// temp helper functions for implementation
	void move(glm::vec3 dir);
	glm::vec3 get_up( void );
	glm::vec3 get_right( void );
	glm::vec3 get_lookat( void );

};
#endif // CAMERA_H