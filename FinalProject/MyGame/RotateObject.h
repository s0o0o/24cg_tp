#pragma once

#include <iostream>
#include "GameObject.h"

class RotateObject : public GameObject{

	
	float rotateSpeed;

public:
	RotateObject();
	virtual ~RotateObject();

	virtual void initilize() override;
	virtual void update(float elapseTime)override;
	virtual void draw() const override;
	virtual void release() override;
};

