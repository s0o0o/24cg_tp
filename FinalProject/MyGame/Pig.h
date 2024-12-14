#pragma once
#include "GameObject.h"
#include "PlayerObject.h"

class Pig : public GameObject
{
private:
	GLuint pigVAO;
	int pigVertexCount;

	float x, y, z;
	float rangeLimit;
	float moveSpeed;

	bool isBaby;
	float pigXDir;
	float pigZDir;

	float movePigX;
	float movePigZ;
	float rotatePigLeftLeg;
	float rotatePigRightLeg;
	float rotateFacePig;

public:
	Pig();
	virtual ~Pig();

	virtual void initilize() override;
	virtual void update(float elapseTime)override;
	virtual void draw() const override;
	virtual void release() override;


};




