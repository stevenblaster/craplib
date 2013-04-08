/*


Copyright 2012 Thomas Dalling - http://tomdalling.com/

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

camera::camera() :
	_position(0.0f, 0.0f, 1.0f),
	_horizontalAngle(0.0f),
	_verticalAngle(0.0f),
	_fieldOfView(50.0f),
	_nearPlane(0.01f),
	_farPlane(100.0f),
	_viewportAspectRatio(4.0f/3.0f)
{
}

const glm::vec3& camera::position() const {
	return _position;
}

void camera::setPosition(const glm::vec3& position) {
	_position = position;
}

void camera::offsetPosition(const glm::vec3& offset) {
	_position += offset;
}

float camera::fieldOfView() const {
	return _fieldOfView;
}

void camera::setFieldOfView(float fieldOfView) {
	assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
	_fieldOfView = fieldOfView;
}

float camera::nearPlane() const {
	return _nearPlane;
}

float camera::farPlane() const {
	return _farPlane;
}

void camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

glm::mat4 camera::orientation() const {
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, _verticalAngle, glm::vec3(1,0,0));
	orientation = glm::rotate(orientation, _horizontalAngle, glm::vec3(0,1,0));
	return orientation;
}

void camera::offsetOrientation(float upAngle, float rightAngle) {
	_horizontalAngle += rightAngle;
	while(_horizontalAngle > 360.0f) _horizontalAngle -= 360.0;
	while(_horizontalAngle < 0.0f) _horizontalAngle += 360.0;

	_verticalAngle += upAngle;
	if(_verticalAngle > MaxVerticalAngle) _verticalAngle = MaxVerticalAngle;
	if(_verticalAngle < -MaxVerticalAngle) _verticalAngle = -MaxVerticalAngle;
}

float camera::viewportAspectRatio() const {
	return _viewportAspectRatio;
}

void camera::setViewportAspectRatio(float viewportAspectRatio) {
	assert(viewportAspectRatio > 0.0);
	_viewportAspectRatio = viewportAspectRatio;
}

glm::vec3 camera::forward() const {
	glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-1,1);
	return glm::vec3(forward);
}

glm::vec3 camera::right() const {
	glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
	return glm::vec3(right);
}

glm::vec3 camera::up() const {
	glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
	return glm::vec3(up);
}

glm::mat4 camera::matrix() const {
	return projection() * view();
}

glm::mat4 camera::projection() const {
	return glm::perspective(_fieldOfView, _viewportAspectRatio, _nearPlane, _farPlane);
}

glm::mat4 camera::view() const {
	return orientation() * glm::translate(glm::mat4(), -_position);
}