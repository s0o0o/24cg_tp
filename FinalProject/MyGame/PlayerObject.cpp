#include "PlayerObject.h"
#include <iostream>

// 플레이어는 그리지 않을거임.. 바라보는 시점이라


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

float playerLimit = 2.f;

void PlayerObject::update(float elapseTime)
{

	glm::vec3 dir(0.f);
	if (isWPressed) {
		
		glm::vec3 newPosition = worldTransform[3]; // 현재 위치를 복사
		newPosition += getLook(); // 이동 방향 추가

		// X축과 Z축 범위를 체크
		if (newPosition.z > -20.f + playerLimit && newPosition.z < 20.f - playerLimit &&
			newPosition.x > -40.f + playerLimit && newPosition.x < 40.f - playerLimit) {
			dir += getLook(); // 범위를 초과하지 않으면 이동
		}
		else {
			if (newPosition.z <= -20.f + playerLimit) dir.z = (-20.f + playerLimit) - worldTransform[3][2];
			if (newPosition.z >= 20.f - playerLimit) dir.z = (20.f - playerLimit) - worldTransform[3][2];
			if (newPosition.x <= -40.f + playerLimit) dir.x = (-40.f + playerLimit) - worldTransform[3][0];
			if (newPosition.x >= 40.f - playerLimit) dir.x = (40.f - playerLimit) - worldTransform[3][0];
		}
	}
	if (isAPressed) {
		glm::vec3 newPosition = worldTransform[3]; // 현재 위치를 복사
		newPosition += getRight(); // 이동 방향 추가

		// X축과 Z축 범위를 체크
		if (newPosition.z > -20.f + playerLimit && newPosition.z < 20.f - playerLimit &&
			newPosition.x > -40.f + playerLimit && newPosition.x < 40.f - playerLimit) {
			dir += getRight(); // 범위를 초과하지 않으면 이동
		}
		else {
			if (newPosition.z <= -20.f + playerLimit) dir.z = (-20.f + playerLimit) - worldTransform[3][2];
			if (newPosition.z >= 20.f - playerLimit) dir.z = (20.f - playerLimit) - worldTransform[3][2];
			if (newPosition.x <= -40.f + playerLimit) dir.x = (-40.f + playerLimit) - worldTransform[3][0];
			if (newPosition.x >= 40.f - playerLimit) dir.x = (40.f - playerLimit) - worldTransform[3][0];
		}
	}

	if (isSPressed) {
		glm::vec3 newPosition = worldTransform[3]; // 현재 위치를 복사
		newPosition -= getLook(); // 이동 방향 추가

		// X축과 Z축 범위를 체크
		if (newPosition.z > -20.f + playerLimit && newPosition.z < 20.f - playerLimit &&
			newPosition.x > -40.f + playerLimit && newPosition.x < 40.f - playerLimit) {
			dir -= getLook(); // 범위를 초과하지 않으면 이동
		}
		else {
			if (newPosition.z <= -20.f + playerLimit) dir.z = (-20.f + playerLimit) - worldTransform[3][2];
			if (newPosition.z >= 20.f - playerLimit) dir.z = (20.f - playerLimit) - worldTransform[3][2];
			if (newPosition.x <= -40.f + playerLimit) dir.x = (-40.f + playerLimit) - worldTransform[3][0];
			if (newPosition.x >= 40.f - playerLimit) dir.x = (40.f - playerLimit) - worldTransform[3][0];
		}

	}

	if (isDPressed) {
		glm::vec3 newPosition = worldTransform[3]; // 현재 위치를 복사
		newPosition -= getRight(); // 이동 방향 추가

		// X축과 Z축 범위를 체크
		if (newPosition.z > -20.f + playerLimit && newPosition.z < 20.f - playerLimit &&
			newPosition.x > -40.f + playerLimit && newPosition.x < 40.f - playerLimit) {
			dir -= getRight(); // 범위를 초과하지 않으면 이동
		}
		else {
			if (newPosition.z <= -20.f + playerLimit) dir.z = (-20.f + playerLimit) - worldTransform[3][2];
			if (newPosition.z >= 20.f - playerLimit) dir.z = (20.f - playerLimit) - worldTransform[3][2];
			if (newPosition.x <= -40.f + playerLimit) dir.x = (-40.f + playerLimit) - worldTransform[3][0];
			if (newPosition.x >= 40.f - playerLimit) dir.x = (40.f - playerLimit) - worldTransform[3][0];
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
	if (isPressed) {			// 눌러졌을 때
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
	else {						// 떼졌을 때
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
			std::cout << "클릭" << std::endl;
			isLeftMousePressed = true;
			befMousePosX = x;
			befMousePosY = y;
		}
		else if (state == GLUT_UP) {
			std::cout << "뗌" << std::endl;
			isLeftMousePressed = false;
		}
	}

}

void PlayerObject::mouseMove(int x, int y)
{
	int moveXValue = x - befMousePosX;
	int moveYValue = y - befMousePosY;

	if (moveXValue > 0)// 양수라면... 반시계로 돈당..
	{
		std::cout << moveXValue;
		rotateY(float(-moveXValue / 40.f));
	}
	else if (moveXValue < 0)// 음수라면... 시계로 돈당..
	{
		std::cout << moveXValue;
		rotateY(float(-moveXValue / 40.f));
	}


	moveXValue = x;
	moveYValue = y;
}
