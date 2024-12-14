#include "TownObject.h"
#include "Scene.h"
#include <iostream>



TownObject::TownObject()
	:fenceShader(0)
{
	size = 0.1 + static_cast<double>(std::rand()) / RAND_MAX * 0.1;
	std::cout << "town����! ������� " << size << std::endl;
	randX = -10.f + static_cast<float>(std::rand()) / RAND_MAX * 20.f;

	rotateSpeed = (rand() % 2 + 1) * 90.f; // 90~180��
	this->shader = fenceShader;
}

TownObject::~TownObject()
{
	std::cout << "town����!" << std::endl;

}

void TownObject::initilize()
{

}

void TownObject::update(float elapseTime)
{
	//rotateY(rotateSpeed * elapseTime);
}

void TownObject::draw() const
{
	
	GLuint modelLoc = glGetUniformLocation(shader, "modelTransform");
	if (modelLoc < 0)
		std::cout << " modelLoc ã���� ����!";
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(worldTransform));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

}

void TownObject::release()
{
}



