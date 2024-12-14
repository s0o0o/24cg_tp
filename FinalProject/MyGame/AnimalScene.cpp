#include "AnimalScene.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

#include "RotateObject.h"
#include "PlayerObject.h"
#include "TownObject.h"

#define STB_IMAGE_IMPLEMENTATION		// �� �ϳ��� .cpp ���� define ����� �Ѵ�.. �ߺ� include ����!
#include <stb_image.h>

Scene::Scene(int winWidth, int winHeight)
	: width{ winWidth }, height{ winHeight }
{
	//�Ʊ���� ����>> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴°�
	moveBabyX = 0.f;
	moveBabyZ = 0.f;
	rotateBabyLeftLeg = 0.f;
	rotateBabyRightLeg = 0.f;
	rotateFaceBaby = 0.f;

	//���� ����>> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	movePigX = 2.0f;
	movePigZ = 0.f;
	rotatePigLeftLeg = 0.f;
	rotatePigRightLeg = 0.f;
	rotateFacePig = 0.f;

	//����ī ���� >> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	movePenguinX = 4.f;
	moveAlpaZ = 0.f;
	rotateAlpaLeftLeg = 0.f;
	rotateAlpaRightLeg = 0.f;
	rotateFaceAlpa = 0.f;

	//���Ƹ� ����>> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	moveChicX = -2.f;
	moveChicZ = 0.f;
	rotateChicLeftLeg = 0.f;
	rotateChicRightLeg = 0.f;
	rotateFaceChic = 0.f;

	//�� ���� >> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	moveAdultChicX = -4.f;
	moveAdultChickZ = -4.f;
	rotateAudultChicLeftLeg = 0.f;
	rotateAudultChicRightLeg = 0.f;
	rotateFaceAudultChic = 0.f;

	//��� ����>> ��ü��ġ yz, �޿� �ٸ�����, �޿� ��������, �ٶ󺸴� ��
	movePenguinX = 6.f;
	movePenguinZ = 0.f;
	rotatePenguinLeftArm = -25.f;
	rotatePenguinRightArm = 25.f;
	rotateFacePenguin = 0.f;

	//���� ���� >> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	moveFoxX = -6.f;
	moveFoxZ = 0.f;
	rotateFoxLeftLeg = 0.f;
	rotateFoxRightLeg = 0.f;
	rotateFaceFox = 0.f;

	//�ٸ� ���� bool���� �ʱ�ȭ
	isMaxRotateBaby = false; // ���� ����
	isMaxRotatePig = false;
	isMaxRotateAlpa = false;
	isMaxRotateChic = false;
	isMaxRotateAudultChic = false;
	isMaxRotatePenguin = false;
	isMaxRotateFox = false;

	// �� �ٸ� ���� ȸ�� �ӵ�
	rotateSpeed = 0.1f;
}

Scene::~Scene()
{
	release();
}

void Scene::initialize()
{
	shader = makeShader("./Shader/Animalvertex.glsl", "./Shader/Animalfragment.glsl");
	plainShader = makeShader("./Shader/plainVert.glsl", "./Shader/plainFrag.glsl");
	BackGroundShader = makeShader("./Shader/tex_vertex.glsl", "./Shader/tex_fragement.glsl");

	//initBuffer(&sphereVAO, &sphereVertexCount, "./OBJ/fence.obj");
	//����
	initBuffer(&cubeVAO, &cubeVertexCount, "./OBJ/cube.obj");

	// ��Ÿ����ġ
	initBuffer(&fenceVAO, &fenceVertexCount, "./OBJ/fence.obj");


	initBackGroundBuffer();
	std::string filenames3 = { "./Img/grass.jpg" };
	initTexture(&BGTexture, 1, &filenames3);



	player = new PlayerObject;

	player->rotateY(180.f);

	player->setPosition(0.f, 0.f, 20.f);

	srand(clock());

	objects[0] = new RotateObject;		// ��ĳ����!! rotateObject��.. �����ִ� ��ü��.. ������ ��ü�̴�!!
	objects[0]->setShader(shader);
	objects[0]->setVAO(sphereVAO, sphereVertexCount);
	objects[0]->setPosition(0.f, 0.5f, 0.f);

	objects[1] = new RotateObject;		// ��ĳ����
	objects[1]->setShader(shader);
	objects[1]->setVAO(sphereVAO, sphereVertexCount);
	objects[1]->setPosition(2.f, 0.5f, 0.f);

	objectCount = 2;

}

void Scene::release()
{
	for (int i = 0; i < objectCount; ++i)
		delete objects[i];

	delete player;
}

void Scene::update(float elapsedTime)
{
	//std::cout << "hello ���� ��2" << std::endl;
	// �÷��̾� ���� 
	player->update(elapsedTime);


	// ��ü�� �׸���
	for (int i = 0; i < objectCount; ++i)
		objects[i]->update(elapsedTime);	// ��ĳ���� �ÿ��� RotateObject�� update�� ȣ��ȴ�! -> virtual

	// �Ʊ���� �ٸ� ���� ȸ��
	if (isMaxRotateBaby)
	{
		rotateBabyLeftLeg -= rotateSpeed;
		rotateBabyRightLeg += rotateSpeed;
		if (rotateBabyLeftLeg <= -10.f) {
			isMaxRotateBaby = false;
		}
	}
	else if (not isMaxRotateBaby) {
		rotateBabyLeftLeg += rotateSpeed;
		rotateBabyRightLeg -= rotateSpeed;
		if (rotateBabyLeftLeg >= 10.f) {
			isMaxRotateBaby = true;
		}
	}

	// ���� �ٸ� ���� ȸ��
	if (isMaxRotatePig)
	{
		rotatePigLeftLeg -= rotateSpeed;
		rotatePigRightLeg += rotateSpeed;
		if (rotatePigLeftLeg <= -30.f) {
			isMaxRotatePig = false;
		}
	}
	else if (not isMaxRotatePig) {
		rotatePigLeftLeg += rotateSpeed;
		rotatePigRightLeg -= rotateSpeed;
		if (rotatePigLeftLeg >= 30.f) {
			isMaxRotatePig = true;
		}
	}

	// ����ī �ٸ� ���� ȸ��
	if (isMaxRotateAlpa)
	{
		rotateAlpaLeftLeg -= rotateSpeed;
		rotateAlpaRightLeg += rotateSpeed;
		if (rotateAlpaLeftLeg <= -30.f) {
			isMaxRotateAlpa = false;
		}
	}
	else if (not isMaxRotateAlpa) {
		rotateAlpaLeftLeg += rotateSpeed;
		rotateAlpaRightLeg -= rotateSpeed;
		if (rotateAlpaLeftLeg >= 30.f) {
			isMaxRotateAlpa = true;
		}
	}

	// ���Ƹ� �ٸ� ���� ȸ��
	if (isMaxRotateChic)
	{
		rotateChicLeftLeg -= rotateSpeed;
		rotateChicRightLeg += rotateSpeed;
		if (rotateChicLeftLeg <= -30.f) {
			isMaxRotateChic = false;
		}
	}
	else if (not isMaxRotateChic) {
		rotateChicLeftLeg += rotateSpeed;
		rotateChicRightLeg -= rotateSpeed;
		if (rotateChicLeftLeg >= 30.f) {
			isMaxRotateChic = true;
		}
	}

	// �� �ٸ� ���� ȸ��
	if (isMaxRotateAudultChic)
	{
		rotateAudultChicLeftLeg -= rotateSpeed;
		rotateAudultChicRightLeg += rotateSpeed;
		if (rotateAudultChicLeftLeg <= -30.f) {
			isMaxRotateAudultChic = false;
		}
	}
	else if (not isMaxRotateAudultChic) {
		rotateAudultChicLeftLeg += rotateSpeed;
		rotateAudultChicRightLeg -= rotateSpeed;
		if (rotateAudultChicLeftLeg >= 30.f) {
			isMaxRotateAudultChic = true;
		}
	}

	// ��� ���� ���� ȸ��
	if (isMaxRotatePenguin)
	{
		rotatePenguinLeftArm += rotateSpeed;
		rotatePenguinRightArm -= rotateSpeed;
		if (rotatePenguinLeftArm >= 0.f) {
			isMaxRotatePenguin = false;
		}
	}
	else if (not isMaxRotatePenguin) {
		rotatePenguinLeftArm -= rotateSpeed;
		rotatePenguinRightArm += rotateSpeed;
		if (rotatePenguinLeftArm <= -25.f) {
			isMaxRotatePenguin = true;
		}
	}

	//���� �ٸ� ���� ȸ��
	if (isMaxRotateFox)
	{
		rotateFoxLeftLeg -= rotateSpeed;
		rotateFoxRightLeg += rotateSpeed;
		if (rotateFoxLeftLeg <= -30.f) {
			isMaxRotateFox = false;
		}
	}
	else if (not isMaxRotateFox) {
		rotateFoxLeftLeg += rotateSpeed;
		rotateFoxRightLeg -= rotateSpeed;
		if (rotateFoxLeftLeg >= 30.f) {
			isMaxRotateFox = true;
		}
	}
}

void Scene::draw() const
{
	glm::vec3 cameraPos = player->getPosition();		// �÷��̾� ��ġ����
	cameraPos.y = 1.f;
	glm::vec3 targetPos = cameraPos + player->getLook(); // �÷��̾� ���� �ٶ󺻴�

	glm::mat4 viewMatrix = glm::lookAt(cameraPos, targetPos, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 projMatrix = glm::perspective(glm::radians(45.f), float(width) / float(height), 0.1f, 100.f);

	// �ٴ� ����....
	{
		glDisable(GL_CULL_FACE);

		glUseProgram(BackGroundShader);
		glBindVertexArray(BGVAO);

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.f, 0.f));
		glm::mat4 rotMatrixX = glm::rotate(glm::mat4(1.f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(20.f));
		glm::mat4 matrix = translateMatrix * rotMatrixX * sclaeMatrix;

		GLint worldLoc = glGetUniformLocation(BackGroundShader, "modelTransform");
		if (worldLoc < 0)
			std::cout << "worldLoc ã�� ����\n";
		else
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint viewLoc = glGetUniformLocation(BackGroundShader, "viewTransform");
		if (viewLoc < 0)
			std::cout << "viewLoc ã�� ����\n";
		GLint projLoc = glGetUniformLocation(BackGroundShader, "projTransform");
		if (projLoc < 0)
			std::cout << "projLoc ã�� ����\n";

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

		glBindTexture(GL_TEXTURE_2D, BGTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}

	glUseProgram(shader);
	glBindVertexArray(cubeVAO);

	glm::mat4 matrix(1.f);

	GLint worldLoc = glGetUniformLocation(shader, "modelTransform");
	GLint colorLoc = glGetUniformLocation(shader, "colorTransform");

	// ī�޶�, ������ �� ��ü�� ����..
	GLint viewLoc = glGetUniformLocation(shader, "viewTransform");
	if (viewLoc < 0)
		std::cout << "viewLoc ã�� ����\n";
	GLint projLoc = glGetUniformLocation(shader, "projTransform");
	if (projLoc < 0)
		std::cout << "projLoc ã�� ����\n";
	/*GLint cameraPosLoc = glGetUniformLocation(shader, "cameraPos");
	if (cameraPosLoc < 0)
		std::cout << "cameraPosLoc ã�� ����\n";*/

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	/*glUniform3f(cameraPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);*/

	{
		//�Ʊ����
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(moveBabyX, 0.0f, moveBabyZ));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFaceBaby), glm::vec3(0.f, 1.f, 0.f));
		// �ٸ� �׸��� �޴ٸ�
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.15f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.f, -0.15f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.f, -0.15f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateBabyLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateBabyRightLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// ���� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.4f, 0.4f, 0.45f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.15f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		{
			// �մٸ�
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.15f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.f, 0.3f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.f, 0.3f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateBabyLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateBabyRightLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.5f, 0.5f, 0.5f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.15f, 0.45f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.2f, 0.1f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.28f, 0.7f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�౸�� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.05f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.05f, 0.30f, 0.73f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.05f, 0.30f, 0.73f));

			glm::mat4 finalMat;
			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.08f, 0.08f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.35f, 0.68f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.35f, 0.68f));

			glm::mat4 finalMat;
			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�ȱ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.035f, 0.035f, 0.04f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.135f, 0.38f, 0.72f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.165f, 0.38f, 0.72f));

			glm::mat4 finalMat;
			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	{
		//�����
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(movePigX, 0.0f, movePigX));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFacePig), glm::vec3(0.f, 1.f, 0.f));
		//�ٸ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.18f, 0.25f, 0.18f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.18f, 0.f, -0.25f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.18f, 0.f, -0.25f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotatePigLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotatePigRightLeg), glm::vec3(1.f, 0.f, 0.f));


			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//���� �׸���
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
			//�մٸ�
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.18f, 0.25f, 0.18f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.18f, 0.f, 0.3f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.18f, 0.f, 0.3f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotatePigLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotatePigRightLeg), glm::vec3(1.f, 0.f, 0.f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.5f, 0.5f, 0.5f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.4f, 0.5f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.2f, 0.1f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.55f, 0.75f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.5f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�౸�� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.05f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.05f, 0.58f, 0.8f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.05f, 0.58f, 0.8f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{

			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.1f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.6f, 0.75f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.6f, 0.75f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�ȱ� �׸���
		{

			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.1f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.2f, 0.6f, 0.75f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.2f, 0.6f, 0.75f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	{
		// ����ī
		//(0.92, 0.9, 0.8)
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(movePenguinX, 0.0f, moveAlpaZ));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFaceAlpa), glm::vec3(0.f, 1.f, 0.f));
		// �ٸ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.18f, 0.3f, 0.18f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.18f, 0.f, -0.25f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.18f, 0.f, -0.25f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateAlpaLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateAlpaRightLeg), glm::vec3(1.f, 0.f, 0.f));

			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// ���� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.55f, 0.55f, 1.f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.3f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		{
			// �մٸ�
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.18f, 0.3f, 0.18f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.18f, 0.f, 0.3f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.18f, 0.f, 0.3f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateAlpaLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateAlpaRightLeg), glm::vec3(1.f, 0.f, 0.f));

			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.45f, 1.f, 0.45f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.4f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));

			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �ֵ��� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.2f, 0.15f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 1.05f, 0.65f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.8f, 0.75f, 0.6f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.05f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 1.15f, 0.7f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.8f, 0.7f, 0.6f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.2f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.1f, 1.5f, 0.5f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.1f, 1.5f, 0.5f));


			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.92f, 0.9f, 0.8f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		{
			// ��
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.07f, 0.07f, 0.07f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 1.2f, 0.6f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 1.2f, 0.6f));

			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	{
		//���Ƹ�
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(moveChicX, 0.0f, moveChicZ));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFaceChic), glm::vec3(0.f, 1.f, 0.f));
		//�ٸ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.15f, 0.08f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.07f, 0.f, 0.f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.07f, 0.f, 0.f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateChicLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateChicRightLeg), glm::vec3(1.f, 0.f, 0.f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.64f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.64f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//���� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.4f, 0.4f, 0.4f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.15f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.0f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.3f, 0.3f, 0.3f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.4f, 0.25f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniform3f(colorLoc, 1.f, 1.0f, 0.f);
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�θ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.05f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.48f, 0.4f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.64f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.6f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.05f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.07f, 0.5f, 0.38f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.07f, 0.5f, 0.38f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	{
		//��
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(moveAdultChicX, 0.0f, moveAdultChickZ));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFaceAudultChic), glm::vec3(0.f, 1.f, 0.f));
		//�ٸ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.2f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.07f, 0.f, 0.f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.07f, 0.f, 0.f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateAudultChicLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateAudultChicRightLeg), glm::vec3(1.f, 0.f, 0.f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.64f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.64f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//���� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.4f, 0.4f, 0.5f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.18f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.0f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.25f, 0.3f, 0.3f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.25f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniform3f(colorLoc, 1.f, 1.0f, 1.f);
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�θ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.25f, 0.06f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.57f, 0.4f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.64f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�ߺ��� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.06f, 0.12f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.51f, 0.44f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.6f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.05f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.08f, 0.65f, 0.38f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.08f, 0.65f, 0.38f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	{
		// ���
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(movePenguinX, 0.0f, movePenguinZ));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFacePenguin), glm::vec3(0.f, 1.f, 0.f));
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.05f, 0.3f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.12f, 0.f, 0.1f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.12f, 0.f, 0.1f));;

			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 0.3f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 0.3f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.0625f, 0.5f, 0.2f)); // �� ũ��

			// ��� ��ġ ���� (������ ���κ� �翷)
			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.2f, 0.2f, 0.f)); // ���� ���
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.2f, 0.2f, 0.f)); // ������ ���

			glm::mat4 rotateleftarm = glm::rotate(unitMat, glm::radians(rotatePenguinLeftArm), glm::vec3(0.f, 0.f, 1.f));
			glm::mat4 rotaterightarm = glm::rotate(unitMat, glm::radians(rotatePenguinRightArm), glm::vec3(0.f, 0.f, 1.f));

			glm::mat4 finalMat;

			// ���� ��
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.15f, 0.4f, 0.f)) * rotateleftarm * glm::translate(unitMat, glm::vec3(0.15f, -0.4f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.36f);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// ������ ��
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.15f, 0.4f, 0.f)) * rotaterightarm * glm::translate(unitMat, glm::vec3(-0.15f, -0.4f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.36f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// ���� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.4f, 0.65f, 0.4f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.05f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.36f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.3f, 0.5f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.09f, 0.18f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.3f, 0.3f, 0.3f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.7f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));

			glUniform3f(colorLoc, 0.f, 0.f, 0.36f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �θ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.05f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.8f, 0.2f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 0.4f, 0.2f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// �� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.6f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.05f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.07f, 0.85f, 0.15f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.07f, 0.85f, 0.15f));

			glm::mat4 finalMat;

			// ����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.5f, 0.5f, 0.5f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// ������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.5f, 0.5f, 0.5f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	{
		//����
		const glm::mat4 unitMat(1.f);
		glm::mat4 moveFinal = glm::translate(unitMat, glm::vec3(moveFoxX, 0.0f, moveFoxZ));
		glm::mat4 rotateDir = glm::rotate(unitMat, glm::radians(rotateFaceFox), glm::vec3(0.f, 1.f, 0.f));
		//�ٸ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.13f, 0.25f, 0.13f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.f, -0.25f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.f, -0.25f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateFoxLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateFoxRightLeg), glm::vec3(1.f, 0.f, 0.f));


			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//���� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.55f, 0.55f, 0.8f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.25f, 0.f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;

			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.9f, 0.7f, 0.2f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		{
			//�մٸ�
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.13f, 0.25f, 0.13f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.f, 0.3f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.f, 0.3f));

			glm::mat4 rotateleftleg = glm::rotate(unitMat, glm::radians(rotateFoxLeftLeg), glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotaterightleg = glm::rotate(unitMat, glm::radians(rotateFoxRightLeg), glm::vec3(1.f, 0.f, 0.f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * glm::translate(unitMat, glm::vec3(-0.0625f, 0.15f, 0.f)) * rotateleftleg * glm::translate(unitMat, glm::vec3(0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * glm::translate(unitMat, glm::vec3(0.0625f, 0.15f, 0.f)) * rotaterightleg * glm::translate(unitMat, glm::vec3(-0.0625f, -0.15f, 0.f)) * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�Ӹ� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.45f, 0.45f, 0.45f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.4f, 0.5f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.9f, 0.7f, 0.2f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�ֵ��� �׸���
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.2f, 0.1f, 0.1f));

			glm::mat4 moveBottomUp = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.75f));

			glm::mat4 finalMat = moveFinal * moveBottomUp * rotateDir * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.97f, 0.8f, 0.5f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//��
		{
			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.1f, 0.05f, 0.05f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(0.f, 0.55f, 0.8f));

			glm::mat4 finalMat;

			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{

			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.06f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.6f, 0.75f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.6f, 0.75f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�ȱ� �׸���
		{

			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.05f, 0.06f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.2f, 0.6f, 0.75f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.2f, 0.6f, 0.75f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 1.f, 1.f, 1.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//�� �׸���
		{

			glm::mat4 moveYMat = glm::translate(unitMat, glm::vec3(0.f, 0.5f, 0.f));	// ������..
			glm::mat4 scaleMat = glm::scale(unitMat, glm::vec3(0.08f, 0.09f, 0.1f));

			glm::mat4 moveleftPos = glm::translate(unitMat, glm::vec3(-0.15f, 0.85f, 0.6f));
			glm::mat4 moveRightPos = glm::translate(unitMat, glm::vec3(0.15f, 0.85f, 0.6f));

			glm::mat4 finalMat;

			//����
			finalMat = moveFinal * rotateDir * moveleftPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//������
			finalMat = moveFinal * rotateDir * moveRightPos * scaleMat * moveYMat;
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(finalMat));
			glUniform3f(colorLoc, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}


	// ������Ʈ �׸���
	player->draw();		// ���� �÷��̾� �ȱ׸��� �ص�... ���߿� �׸� �� ������ ȣ�����ش�

	for (int i = 0; i < objectCount; ++i)
		objects[i]->draw();		// �θ� Ŭ�������� draw�� virtual.. 
	// ���������Լ��� �������⿡ ���� �ڽ�Ŭ������ draw�� �����ͱ׸��°��̴�..
	// virtual keyword ������.. ��ĳ���� �ϸ� �ȵȴ٤�!!!
}

void Scene::keyboard(unsigned char key, bool isPressed)
{
	player->keyboard(key, isPressed);

	if (isPressed) {			// �������� ��
		switch (key) {
		default:
			break;
		}
	}
	else {						// ������ ��
		switch (key) {
		default:
			break;
		}
	}
}

void Scene::specialKeyboard(int key, bool isPressed)
{
}

void Scene::mouse(int button, int state, int x, int y)
{
	player->mouse(button, state, x, y);

	// ȭ�� ������Ʈ�� �ȴ�....

	constexpr int WHEEL_UP = 3;
	constexpr int WHEEL_DOWN = 4;

	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case GLUT_LEFT_BUTTON: {
			float xPos = (static_cast<float>(x) / width * 2.f - 1.f);
			float yPos = -(static_cast<float>(y) / height * 2.f - 1.f);

			//std::cout << "��Ŭ�� : " << x << ", " << y << std::endl;
			//std::cout << "OpenGL x ��ǥ�� " << xPos << std::endl;
			//std::cout << "OpenGL y ��ǥ�� " << yPos << std::endl;

			break;
		}
		case GLUT_MIDDLE_BUTTON:
			std::cout << "��Ŭ�� : " << x << ", " << y << std::endl;
			break;
		case GLUT_RIGHT_BUTTON:
			std::cout << "��Ŭ�� : " << x << ", " << y << std::endl;
			break;
		case WHEEL_UP:
			std::cout << "��  �� : " << x << ", " << y << std::endl;
			break;
		case WHEEL_DOWN:
			std::cout << "�ٴٿ� : " << x << ", " << y << std::endl;
			break;
		}
		break;
	case GLUT_UP:
		switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
		break;
	}
}

void Scene::mouseMove(int x, int y)
{
	player->mouseMove(x, y);
}

void Scene::setWindowSize(int winWidth, int winHeight)
{
	width = winWidth;
	height = winHeight;
}

void Scene::initBuffer(GLuint* VAO, GLsizei* vertexCount, std::string objFilename)
{
	glGenVertexArrays(1, VAO);		// ���� �Ҵ�....
	glBindVertexArray(*VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<glm::vec3> verticies = readOBJ(objFilename);

	*vertexCount = verticies.size() / 3;

	// GPU�� �ϳ��� ��ǻ�Ϳ� ����... ���ο� gpu���� cpu, ��, ��� ����...

	// CPU �޸𸮿� �ִ� �����͸�, GPU �޸𸮿� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies[0]) * verticies.size(), verticies.data(), GL_STATIC_DRAW);

	// �� �����Ͱ� � ����������, �츮�� ���Ǹ� �߱� ������, openGL�� �˷���� �Ѵ�!
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	// location, ����, Ÿ��, nomalized?, ����(����Ʈ), ���ۿ�����
	glEnableVertexAttribArray(0);

	//// �� �����Ͱ� � ����������, �츮�� ���Ǹ� �߱� ������, openGL�� �˷���� �Ѵ�!
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, reinterpret_cast<void*>(sizeof(float) * 3));
	// location, ����, Ÿ��, nomalized?, ����(����Ʈ), ���ۿ�����
	glEnableVertexAttribArray(1);

	//// �� �����Ͱ� � ����������, �츮�� ���Ǹ� �߱� ������, openGL�� �˷���� �Ѵ�!
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, reinterpret_cast<void*>(sizeof(float) * 6));
	// location, ����, Ÿ��, nomalized?, ����(����Ʈ), ���ۿ�����
	glEnableVertexAttribArray(2);

}

void Scene::initBackGroundBuffer() {
	glGenVertexArrays(1, &BGVAO);		// ���� �Ҵ�....
	glBindVertexArray(BGVAO);

	GLuint VBO3;
	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);


	float size = 1.0f;
	float vertexData[54]{ // 6��, ��� 2�ﰢ��, �ﰢ���� ��3��, ���� 9���� --> 324
		// px, py, pz,		tx, ty, tz=0,	 nx, ny, nz

		//Front					// ���Ⱑ �ؽ�ó ��ǥ�� (���� ���⼱ �ؽ�ó��ǥ�� ���ʾƷ��� 0,0 �������� ����!!)
		-size * 2, -size,0,			0, 0, 0,	1, 0, 0,
		size * 2, -size, 0,			1, 0, 0,	1, 0, 0,
		size * 2, size, 0,			1, 1, 0,	1, 0, 0,
		size * 2, size, 0,			1, 1, 0,	1, 0, 0,
		-size * 2, size, 0,			0, 1, 0,	1, 0, 0,
		-size * 2, -size,0,			0, 0, 0,	1, 0, 0

	};

	// CPU �޸𸮿� �ִ� �����͸�, GPU �޸𸮿� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 54, vertexData, GL_STATIC_DRAW);

	// �� �����Ͱ� � ����������, �츮�� ���Ǹ� �߱� ������, openGL�� �˷���� �Ѵ�!
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	// location, ����, Ÿ��, nomalized?, ����(����Ʈ), ���ۿ�����
	glEnableVertexAttribArray(0);

	// �� �����Ͱ� � ����������, �츮�� ���Ǹ� �߱� ������, openGL�� �˷���� �Ѵ�!
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, reinterpret_cast<void*>(sizeof(float) * 3));
	// location, ����, Ÿ��, nomalized?, ����(����Ʈ), ���ۿ�����
	glEnableVertexAttribArray(1);

	// �� �����Ͱ� � ����������, �츮�� ���Ǹ� �߱� ������, openGL�� �˷���� �Ѵ�!
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, reinterpret_cast<void*>(sizeof(float) * 6));
	// location, ����, Ÿ��, nomalized?, ����(����Ʈ), ���ۿ�����
	glEnableVertexAttribArray(2);
}


void Scene::initTexture(GLuint* texture, int size, std::string* texFilename)
{
	glGenTextures(size, texture);

	// ���� �̹��� ������(binary) --> �츮�� �ƴ� ���� �̹����� ����Ʈ ������ �о �����ؾ� �Ѵ�..
	stbi_set_flip_vertically_on_load(true);

	for (int i = 0; i < size; ++i) {
		glBindTexture(GL_TEXTURE_2D, texture[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, level;
		unsigned char* data = stbi_load(texFilename[i].c_str(), &width, &height, &level, 0);		// ���� �Ҵ�...

		if (3 == level)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	// GPU�� ������ ����
		else if (4 == level)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else {
			std::cerr << texFilename[i] << " load Error! �̹��� ���� ����..\n";
			exit(1);
		}

		stbi_image_free(data);
	}
}




GLuint Scene::makeShader(std::string vertexFilename, std::string fragmentFilename)
{
	// ���̴� ������...

	GLint result;
	GLchar errorLog[512];

	GLuint vertexShader, fragmentShader;

	std::string vertexStr = readFile(vertexFilename);	// �� ������ ����������
	const char* vertexSource{ vertexStr.c_str() };		// �� ������ ����Ƿ��� �� ������ �Ҹ�Ǹ� �ȵȴ�..!

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << vertexFilename << " ERROR: vertex shader error\n" << errorLog << std::endl;
	}
	else {
		std::cout << vertexFilename << " ������ ����!" << std::endl;
	}

	std::string fragmentStr = readFile(fragmentFilename);
	const char* fragmentSource{ fragmentStr.c_str() };

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << fragmentFilename << " ERROR: fragment shader error\n" << errorLog << std::endl;
	}
	else {
		std::cout << fragmentFilename << " ������ ����!" << std::endl;
	}

	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);		// ���� vertex Shader�� ���̴� ���α׷��� �߰��� �ش�
	glAttachShader(shaderID, fragmentShader);	// ���� fragment Shader�� ���̴� ���α׷��� �߰��� �ش�
	glLinkProgram(shaderID);					// �߰��� ���̴����� �ϳ��� ���α׷����� �����Ѵ�!

	glDeleteShader(vertexShader);				// ���� ���̻� vertex Shaer�� �ʿ����...
	glDeleteShader(fragmentShader);				// ���� ���̻� fragment Shaer�� �ʿ����...

	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << vertexFilename << ", " << fragmentFilename << " ERROR: shader program ���� ����\n" << errorLog << std::endl;
		//return;
	}
	else {
		std::cout << vertexFilename << ", " << fragmentFilename << " shader program ���� ����!" << std::endl;
	}

	return shaderID;
}

std::string Scene::readFile(std::string filename)
{
	std::ifstream in{ filename };
	if (!in) {
		std::cout << filename << "���� �������� ����!" << std::endl;
		exit(1);
	}

	std::string str;
	std::string temp;
	while (std::getline(in, temp)) {
		str += temp;
		str.append(1, '\n');
	}

	return str;
}


std::vector<glm::vec3> Scene::readOBJ(std::string filename)
{
	std::ifstream in{ filename };
	if (!in) {
		std::cout << filename << " file read failed\n";
		exit(1);
	}

	// c++ stream --> input output�� ���ִ� �帧?

	srand(static_cast<unsigned int>(time(nullptr)));

	std::vector<glm::vec3> vertex;
	std::vector<glm::vec3> color;
	std::vector<glm::vec3> normal;
	std::vector<glm::ivec3> vindex;
	std::vector<glm::ivec3> nindex;
	while (in) {
		std::string line;
		std::getline(in, line);
		std::stringstream ss{ line };
		std::string str;
		ss >> str;
		if (str == "v") {
			glm::vec3 v;
			for (int i = 0; i < 3; ++i) {
				std::string subStr;
				ss >> subStr;
				v[i] = std::stof(subStr);
			}
			vertex.push_back(v);
			color.push_back(glm::vec3(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)));
		}
		else if (str == "vn") {
			glm::vec3 n;
			for (int i = 0; i < 3; ++i) {
				std::string subStr;
				ss >> subStr;
				n[i] = std::stof(subStr);
			}
			normal.push_back(n);
		}
		else if (str == "f") {
			glm::ivec3 fv;
			glm::ivec3 fn;
			for (int i = 0; i < 3; ++i) {
				std::string substr;
				ss >> substr;
				std::stringstream subss{ substr };
				std::string vIdx;
				std::getline(subss, vIdx, '/');
				fv[i] = std::stoi(vIdx) - 1;
				std::getline(subss, vIdx, '/');
				// �ؽ�ó �ǳʶٱ�
				std::getline(subss, vIdx, '/');
				fn[i] = std::stoi(vIdx) - 1;
			}
			vindex.push_back(fv);
			nindex.push_back(fn);
		}
	}

	std::vector<glm::vec3> data;
	for (int i = 0; i < vindex.size(); ++i) {
		data.push_back(vertex[vindex[i][0]]);
		data.push_back(color[vindex[i][0]]);
		data.push_back(normal[nindex[i][0]]);
		data.push_back(vertex[vindex[i][1]]);
		data.push_back(color[vindex[i][1]]);
		data.push_back(normal[nindex[i][1]]);
		data.push_back(vertex[vindex[i][2]]);
		data.push_back(color[vindex[i][2]]);
		data.push_back(normal[nindex[i][2]]);
	}

	std::cout << filename << " File Read, " << data.size() / 3 << " Vertices Exists." << std::endl;
	return data;
}



std::vector<glm::vec3> Scene::readOBJWithUV(std::string filename)
{
	std::ifstream in{ filename };
	if (!in) {
		std::cout << filename << " file read failed\n";
		exit(1);
	}

	std::vector<glm::vec3> vertex;
	std::vector<glm::vec3> tex;
	std::vector<glm::vec3> normal;
	std::vector<glm::ivec3> vindex;
	std::vector<glm::ivec3> tindex;
	std::vector<glm::ivec3> nindex;
	while (in) {
		std::string line;
		std::getline(in, line);
		std::stringstream ss{ line };
		std::string str;
		ss >> str;
		if (str == "v") {
			glm::vec3 v;
			for (int i = 0; i < 3; ++i) {
				std::string subStr;
				ss >> subStr;
				v[i] = std::stof(subStr);
			}
			vertex.push_back(v);
		}
		else if (str == "vt") {
			glm::vec3 t;
			for (int i = 0; i < 3; ++i) {
				std::string subStr;
				ss >> subStr;
				t[i] = std::stof(subStr);
			}
			tex.push_back(t);
		}
		else if (str == "vn") {
			glm::vec3 n;
			for (int i = 0; i < 3; ++i) {
				std::string subStr;
				ss >> subStr;
				n[i] = std::stof(subStr);
			}
			normal.push_back(n);
		}
		else if (str == "f") {
			glm::ivec3 fv;
			glm::ivec3 ft;
			glm::ivec3 fn;
			for (int i = 0; i < 3; ++i) {
				std::string substr;
				ss >> substr;
				std::stringstream subss{ substr };
				std::string vIdx;
				std::getline(subss, vIdx, '/');
				fv[i] = std::stoi(vIdx) - 1;
				std::getline(subss, vIdx, '/');
				ft[i] = std::stoi(vIdx) - 1;
				std::getline(subss, vIdx, '/');
				fn[i] = std::stoi(vIdx) - 1;
			}
			vindex.push_back(fv);
			tindex.push_back(ft);
			nindex.push_back(fn);
		}
	}

	std::vector<glm::vec3> data;
	for (int i = 0; i < vindex.size(); ++i) {
		data.push_back(vertex[vindex[i][0]]);
		data.push_back(tex[tindex[i][0]]);
		data.push_back(normal[nindex[i][0]]);
		data.push_back(vertex[vindex[i][1]]);
		data.push_back(tex[tindex[i][1]]);
		data.push_back(normal[nindex[i][1]]);
		data.push_back(vertex[vindex[i][2]]);
		data.push_back(tex[tindex[i][2]]);
		data.push_back(normal[nindex[i][2]]);
	}

	std::cout << filename << " File Read, " << data.size() / 3 << " Vertices Exists." << std::endl;
	return data;
}
