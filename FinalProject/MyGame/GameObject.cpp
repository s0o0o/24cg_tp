#include "GameObject.h"

#include <iostream>

GameObject::GameObject()
	: worldTransform(1.f)
{
}

GameObject::~GameObject()
{
}

void GameObject::initilize()
{
	
}

void GameObject::update(float elapsedTime)
{
}

void GameObject::draw() const
{
	// �𵨺�ȯ���
	GLint modelLoc = glGetUniformLocation(shader, "modelTransform");
	if (modelLoc < 0)
		std::cout << "modelLoc ã�� ����\n";
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void GameObject::release()
{
}

void GameObject::setShader(GLuint my_shader)
{
	this->shader = my_shader;
}

void GameObject::setVAO(GLuint vao, GLsizei count)
{
	VAO = vao;
	vertexCount = count;
}

glm::vec3 GameObject::getPosition() const
{
	return glm::vec3(worldTransform[3]); 
	// ���� ��ȯ.. 4*4��Ŀ���.. 3������ �׻� �̵������� ����Ǿ��ִ�!!
	// translate�� ���� ����Ǿ�����..
	// opengl�������δ� 3��, �Ƹ� �ٷ��������δ� 3�࿡ ����Ǿ������Ƿ� ��ü�� ��� 
	// ��ġ���ִ��� �˰������.. translate�� ����! ����Ǿ��ִ�. �̵������� ����Ǿ��ִ�
	// ���庯ȯ��� 3���� ���������..									
}

void GameObject::setPosition(glm::vec3 position)
{
	worldTransform[3] = glm::vec4(position, 1.f);
}

void GameObject::setPosition(float x, float y, float z)
{
	setPosition(glm::vec3(x, y, z));
}

glm::vec3 GameObject::getLook() const
{
	return glm::vec3(worldTransform[2]);
}

glm::vec3 GameObject::getRight() const
{
	return glm::vec3(worldTransform[0]);
}


void GameObject::rotateY(float degrees)
{
	glm::vec3 originPos = getPosition();
	setPosition(0.f, 0.f, 0.f);

	worldTransform = glm::rotate(glm::mat4(1.f), glm::radians(degrees), glm::vec3(0.f, 1.f, 0.f)) * worldTransform;

	setPosition(originPos);
}

void GameObject::rotateX(float degrees)
{
	glm::vec3 originPos = getPosition();
	setPosition(0.f, 0.f, 0.f);

	worldTransform = glm::rotate(glm::mat4(1.f), glm::radians(degrees), glm::vec3(1.f, 0.f, 0.f)) * worldTransform;

	setPosition(originPos);
}


void GameObject::move(glm::vec3 dir, float value)
{
	glm::vec3 normalDir = glm::normalize(dir);
	worldTransform = glm::translate(glm::mat4(1.f), normalDir * value) * worldTransform;
}

void GameObject::moveForward(float value)
{
	move(getLook(), value);
}


