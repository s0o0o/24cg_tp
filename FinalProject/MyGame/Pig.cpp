#include "Pig.h"
#include "PlayerObject.h"
#include <iostream>

Pig::Pig()
{
	//srand(clock());

	float x = -10.f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 5.f));
	float z = -5.f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 10.f));

	setPosition(x, 0.f, z);
	isBaby = true;
	rangeLimit = 1.f;

	pigXDir = (rand() % 2 == 0) ? 1.f : -1.f;
	pigZDir = (rand() % 2 == 0) ? 1.f : -1.f;
	moveSpeed = 0.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 1.f));

	movePigX = 2.0f;
	movePigZ = 0.f;
	rotatePigLeftLeg = 0.f;
	rotatePigRightLeg = 0.f;
	rotateFacePig = 0.f;


	initBuffer(&pigVAO, &pigVertexCount, "./OBJ/cube.obj");

}

Pig::~Pig()
{
//	delete this;
}

void Pig::initilize()
{
	//player = new PlayerObject;
}

// 펜스 실 범위
// x : -15.f ~ 0.f
// z : -8.f ~ 10.f

void Pig::update(float elapseTime)
{
	glm::vec3 dir(0.f);

	glm::vec3 newPosition = worldTransform[3]; // 현재 위치를 복사
	newPosition += getLook();

	//const glm::vec3 playerPosition = player->getPosition();

	//if (player->playerX >= worldTransform[3][0] - 1.f and
	//	player->playerX <= worldTransform[3][0] + 1.f and
	//	player->playerZ >= worldTransform[3][2] - 1.f and
	//	player->playerZ <= worldTransform[3][2] + 1.f) {
	//	std::cout << " 가까이에 있다!!!! " << std::endl;
	//}

	if (isBaby) {
		if (worldTransform[3][0] > -15.f and worldTransform[3][0] < -1.f
			and worldTransform[3][2] > -8.f and worldTransform[3][2] < 9.f) {


			if (pigXDir > 0) {
				dir += getRight();
			}
			if (pigXDir < 0) {
				dir -= getRight();
			}
			if (pigZDir > 0) {
				dir += getLook();
			}
			if (pigZDir < 0) {
				dir -= getLook();
			}

			if (worldTransform[3][0] <= -15.f + rangeLimit) {
				pigXDir = 1.f;
				std::cout << pigXDir << std::endl;
			}
			if (worldTransform[3][0] >= -1.f - rangeLimit) {
				pigXDir = -1.f;
				std::cout << pigXDir << std::endl;
			}
			if (worldTransform[3][2] <= -8.f + rangeLimit) {
				pigZDir = 1.f;
				std::cout << pigZDir << std::endl;
			}
			if (worldTransform[3][2] >= 9.f - rangeLimit) {
				pigZDir = -1.f;
				std::cout << pigZDir << std::endl;
			}
		}


	}


	if (glm::length(dir) >= glm::epsilon<float>())
		move(dir, moveSpeed * elapseTime);
}

void Pig::draw() const
{
	glUseProgram(shader);
	glBindVertexArray(pigVAO);

	GLint worldLoc = glGetUniformLocation(shader, "modelTransform");
	GLint colorLoc = glGetUniformLocation(shader, "colorTransform");

	//어른돼지
	const glm::mat4 unitMat(1.f);
	glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(movePigX, 0.0f, movePigX));
	glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFacePig), glm::vec3(0.f, 1.f, 0.f));
	//다리 그리기
	{
		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// 고정값..
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.18f, 0.25f, 0.18f));

		glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.18f, 0.f, -0.25f));
		glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.18f, 0.f, -0.25f));

		glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotatePigLeftLeg), glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotatePigRightLeg), glm::vec3(1.f, 0.f, 0.f));

		glm::mat4 finalMat;

		//왼쪽
		finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//오른쪽
		finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//몸통 그리기
	{
		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.55f, 0.55f, 0.8f));

		glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.25f, 0.f));

		glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	{
		//앞다리
		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// 고정값..
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.18f, 0.25f, 0.18f));

		glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.18f, 0.f, 0.3f));
		glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.18f, 0.f, 0.3f));

		glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotatePigLeftLeg), glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotatePigRightLeg), glm::vec3(1.f, 0.f, 0.f));

		glm::mat4 finalMat;

		//왼쪽
		finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//오른쪽
		finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//머리 그리기
	{
		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.5f, 0.5f, 0.5f));

		glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.4f, 0.5f));

		glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//코 그리기
	{
		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.2f, 0.1f, 0.1f));

		glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.55f, 0.75f));

		glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//콧구멍 그리기
	{
		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// 고정값..
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.05f, 0.05f));

		glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.05f, 0.58f, 0.8f));
		glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.05f, 0.58f, 0.8f));

		glm::mat4 finalMat;

		//왼쪽
		finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 0.f, 0.f, 0.f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//오른쪽
		finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 0.f, 0.f, 0.f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//눈 그리기
	{

		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// 고정값..
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.1f, 0.1f));

		glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.6f, 0.75f));
		glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.6f, 0.75f));

		glm::mat4 finalMat;

		//왼쪽
		finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 0.f, 0.f, 0.f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//오른쪽
		finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 0.f, 0.f, 0.f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//안광 그리기
	{

		glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// 고정값..
		glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.1f, 0.1f));

		glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.2f, 0.6f, 0.75f));
		glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.2f, 0.6f, 0.75f));

		glm::mat4 finalMat;

		//왼쪽
		finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 1.f, 1.f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//오른쪽
		finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
		glUniform3f(colorLoc, 1.f, 1.f, 1.f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//std::cout << "뭐니.그려지니.?" << std::endl;
}

void Pig::release()
{
}

