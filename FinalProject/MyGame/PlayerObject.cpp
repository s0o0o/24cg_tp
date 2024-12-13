#include "PlayerObject.h"
#include <iostream>

// �÷��̾�� �׸��� ��������.. �ٶ󺸴� �����̶�


PlayerObject::PlayerObject()
{
	isWPressed = false;
	isAPressed = false;
	isSPressed = false;
	isDPressed = false;

	moveSpeed = 5.f;

	initilize();


}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::initilize()
{
	setVAO(0, 0);
	setShader(0);

}


void PlayerObject::update(float elapseTime)
{

	glm::vec3 dir(0.f);
	if (isWPressed) {
		if (worldTransform[3][2] >= -20.f and worldTransform[3][2] <= 20.f
			and worldTransform[3][0] >= -40.f and worldTransform[3][0] <= 40.f) {
			dir += getLook();
		}
		else {
		
		}

	}
	if (isAPressed) {
		if (worldTransform[3][2] >= -20.f and worldTransform[3][2] <= 20.f
			and worldTransform[3][0] >= -40.f and worldTransform[3][0] <= 40.f) {
			dir += getRight();
		}
		else {
		
		}
	}

	if (isSPressed) {
		if (worldTransform[3][2] >= -20.f and worldTransform[3][2] <= 20.f
			and worldTransform[3][0] >= -40.f and worldTransform[3][0] <= 40.f) {
			dir -= getLook();
		}
		else {
			
		}

	}

	if (isDPressed) {
		if (worldTransform[3][2] >= -20.f and worldTransform[3][2] <= 20.f
			and worldTransform[3][0] >= -40.f and worldTransform[3][0] <= 40.f) {
			dir -= getRight();
		}
		else {
		

		}
	}


	if (glm::length(dir) >= glm::epsilon<float>())
		move(dir, moveSpeed * elapseTime);
}

void PlayerObject::draw() const
{
}

void PlayerObject::release()
{
}

void PlayerObject::keyboard(unsigned char key, bool isPressed)
{
	if (isPressed) {			// �������� ��
		switch (key) {
		case'W':
		case'w':
			isWPressed = true;
			break;
		case'S':
		case's':
			isSPressed = true;

			break;
		case'A':
		case'a':
			isAPressed = true;

			break;
		case'D':
		case'd':
			isDPressed = true;

			break;
		case'g':
			//std::cout <<  << std::endl;
			break;
		default:
			break;
		}
	}
	else {						// ������ ��
		switch (key) {
		case'W':
		case'w':
			isWPressed = false;
			break;
		case'S':
		case's':
			isSPressed = false;
			break;
		case'A':
		case'a':
			isAPressed = false;
			break;
		case'D':
		case'd':
			isDPressed = false;
			break;
		default:
			break;
		}
	}
}

void PlayerObject::mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			std::cout << "Ŭ��" << std::endl;
			isLeftMousePressed = true;
			befMousePosX = x;
			befMousePosY = y;
		}
		else if (state == GLUT_UP) {
			std::cout << "��" << std::endl;
			isLeftMousePressed = false;
		}
	}

}

void PlayerObject::mouseMove(int x, int y)
{
	int moveXValue = x - befMousePosX;
	int moveYValue = y - befMousePosY;

	if (moveXValue > 0)// ������... �ݽð�� ����..
	{
		std::cout << moveXValue;
		rotateY(float(-moveXValue / 40.f));
	}
	else if (moveXValue < 0)// �������... �ð�� ����..
	{
		std::cout << moveXValue;
		rotateY(float(-moveXValue / 40.f));
	}


	moveXValue = x;
	moveYValue = y;
}
