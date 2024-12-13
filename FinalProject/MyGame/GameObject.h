#pragma once

#include "library.h"

class GameObject
{
protected:		// �θ� Ŭ������ �� ���̴�..
	glm::mat4 worldTransform;

	GLuint shader;
	GLuint VAO;
	GLsizei vertexCount;

public:
	GameObject();
	virtual ~GameObject();

	virtual void initilize();
	virtual void update(float elapsedTime);
	virtual void draw() const;
	virtual void release();

	void setShader(GLuint shader);
	void setVAO(GLuint vao, GLsizei count);

	glm::vec3 getPosition() const;
	void setPosition(glm::vec3 position);
	void setPosition(float x, float y, float z);	// �����ε�

	glm::vec3 getLook() const;
	glm::vec3 getRight() const;

	void rotateY(float degrees);

	void move(glm::vec3 dir, float value);
	void moveForward(float value);

};

