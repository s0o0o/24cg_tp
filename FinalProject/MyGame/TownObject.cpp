#include "TownObject.h"
#include "PlayerObject.h"
#include "Scene.h"
#include "library.h"
#include <iostream>



TownObject::TownObject()
	:fenceShader(0)
{
	size = 0.1 + static_cast<double>(std::rand()) / RAND_MAX * 0.1;
	std::cout << "town생성! 사이즈는 " << size << std::endl;
	randX = -10.f + static_cast<float>(std::rand()) / RAND_MAX * 20.f;

	rotateSpeed = (rand() % 2 + 1) * 90.f; // 90~180도
	this->shader = fenceShader;
}

TownObject::~TownObject()
{
	std::cout << "town제거!" << std::endl;

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
	
	
}

void TownObject::release()
{
}



