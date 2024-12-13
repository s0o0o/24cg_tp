#pragma once

#include <iostream>
#include "GameObject.h"

class TownObject : public GameObject {

	GLuint BGVAO;
	GLuint BGTexture;

	float rotateSpeed;

public:
	TownObject();
	virtual ~TownObject();

	virtual void initilize() override;
	virtual void update(float elapseTime)override;
	virtual void draw() const override;
	virtual void release() override;


};

