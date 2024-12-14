#include "RotateObject.h"

RotateObject::RotateObject()
{
	
	rotateSpeed = (rand() % 2 + 1) * 90.f; // 90~180도
}

RotateObject::~RotateObject()
{
}

void RotateObject::initilize()
{

}

void RotateObject::update(float elapseTime)
{
	rotateY(rotateSpeed * elapseTime);
}

void RotateObject::draw() const
{
	glUseProgram(shader);
	GLuint modelLoc = glGetUniformLocation(shader, "modelTransform");
	if (modelLoc < 0)
		std::cout << " modelLoc 찾을수 없음!";
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(worldTransform));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

}

void RotateObject::release()
{
}
