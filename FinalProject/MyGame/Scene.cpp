#include "Scene.h"

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

}

Scene::~Scene()
{
	release();
}

void Scene::initialize()
{
	shader = makeShader("./Shader/vertex.glsl", "./Shader/fragment.glsl");

	objShader = makeShader("./Shader/obj_vertex.glsl", "./Shader/obj_fragment.glsl");

	plainShader = makeShader("./Shader/plainVert.glsl", "./Shader/plainFrag.glsl");
	texShader = makeShader("./Shader/tex_vertex.glsl", "./Shader/tex_fragement.glsl");

	initBuffer(&sphereVAO, &sphereVertexCount, "./OBJ/fence.obj");

	initCubeBuffer(&cubeVAO, &cubeVertexCount);

	// ��Ÿ�� ��ġ
	initBuffer(&fenceVAO, &fenceVertexCount, "./OBJ/fence.obj");

	initBuffer(&dogVAO, &dogVertexCount, "./OBJ/Courage/courage.obj");

	// ���� ��ġ
	initBuffer(&treeVAO, &treeVertexCount, "./OBJ/tree_up.obj");
	initBuffer(&treeVAO2, &treeVertexCount2, "./OBJ/tree_bottom.obj");

	// �� ��ġ
	initBuffer(&house_top_VAO, &houseTopVertexCount, "./OBJ/house_top.obj");
	initBufferWithUV(&house_bottom_VAO, &houseBottomVertexCount, "./OBJ/house_bottom.obj");

	// farm sign��ġ
	initBufferWithUV(&sign_top_VAO, &signTopVertexCount, "./OBJ/sign_up.obj");
	initBufferWithUV(&sign_bottom_VAO, &signBottomVertexCount, "./OBJ/sign_bottom.obj");


	std::string filenames5 = { "./Img/farmsign_rest.png" };
	initTexture(&signTexture[0], 1, &filenames5);
	std::string filenames6 = { "./Img/farmsign.png" };
	initTexture(&signTexture[1], 1, &filenames6);

	initBackGroundBuffer();
	std::string filenames3 = { "./Img/grass.jpg" };
	initTexture(&GroundTexture, 1, &filenames3);

	std::string filenames = { "./Img/sky1.png" };
	initTexture(&BGTexture, 1, &filenames);

	std::string filenames2 = { "./Img/sky2.png" };
	initTexture(&BGTexture2, 1, &filenames2);

	std::string filenames4 = { "./Img/houseWood.png" };
	initTexture(&houseTexture[0], 1, &filenames4);

	std::string filenames7 = { "./Img/store.png" };
	initTexture(&houseTexture[1], 1, &filenames7);

	player = new PlayerObject;

	player->rotateY(180.f);

	player->setPosition(0.f, 0.f, 15.f);

	srand(clock());

	objects[0] = new TownObject;		// ��ĳ����!! rotateObject��.. �����ִ� ��ü��.. ������ ��ü�̴�!!
	objects[0]->setShader(shader);
	objects[0]->setVAO(sphereVAO, sphereVertexCount);
	objects[0]->setPosition(0.f, 0.5f, 0.f);

	objects[1] = new TownObject;		// ��ĳ����
	objects[1]->setShader(shader);
	objects[1]->setVAO(dogVAO, dogVertexCount);
	objects[1]->setPosition(2.f, 0.5f, 0.f);

	objectCount = 2;
	townObjectCount = 15;

	for (int i = 0; i < 10; ++i) {
		rotateTreeY[i] = static_cast<float>(std::rand()) / RAND_MAX * 360.0f;
	}

	
}

void Scene::release()
{
	for (int i = 0; i < objectCount; ++i)
		delete objects[i];

	//for (int i = 0; i < townObjectCount; ++i)
	//	delete townObjects[i];

	delete player;
}

void Scene::update(float elapsedTime)
{
	//std::cout << "hello ���� ��2" << std::endl;
	// �÷��̾� ���� 
	player->update(elapsedTime);


	// ��ü�� ������Ʈ..
	/*for (int i = 0; i < objectCount; ++i)
		objects[i]->update(elapsedTime);*/	// ��ĳ���� �ÿ��� RotateObject�� update�� ȣ��ȴ�! -> virtual

		/*for (int i = 0; i < townObjectCount; ++i)
			townObjects[i]->update(elapsedTime);*/
}

void Scene::draw() const
{
	glm::vec3 cameraPos = player->getPosition();		// �÷��̾� ��ġ����
	cameraPos.y = 1.5f;
	glm::vec3 targetPos = cameraPos + player->getLook(); // �÷��̾� ���� �ٶ󺻴�

	glm::mat4 viewMatrix = glm::lookAt(cameraPos, targetPos, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 projMatrix = glm::perspective(glm::radians(45.f), float(width) / float(height), 0.1f, 100.f);


	// ��� ����...
	glUseProgram(texShader);
	{
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(BGVAO);


		{
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-40.0f, 15.f, -3.f));
			glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));

			glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(23.f));
			glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;


			GLint worldLoc = glGetUniformLocation(texShader, "modelTransform");
			if (worldLoc < 0)
				std::cout << "worldLoc ã�� ����\n";
			else
				glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(matrix));

			glBindTexture(GL_TEXTURE_2D, BGTexture2);


			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		{
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(40.0f, 15.f, -3.f));
			glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));

			glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(23.f));
			glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;


			GLint worldLoc = glGetUniformLocation(texShader, "modelTransform");
			if (worldLoc < 0)
				std::cout << "worldLoc ã�� ����\n";
			else
				glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(matrix));

			glBindTexture(GL_TEXTURE_2D, BGTexture2);


			glDrawArrays(GL_TRIANGLES, 0, 6);

		}

		{ // z��
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 18.f, -45.f));
			glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(20.f));
			glm::mat4 matrix = translateMatrix * sclaeMatrix;


			GLint worldLoc = glGetUniformLocation(texShader, "modelTransform");
			if (worldLoc < 0)
				std::cout << "worldLoc ã�� ����\n";
			else
				glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(matrix));

			glBindTexture(GL_TEXTURE_2D, BGTexture2);


			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		{ // z��
			glDisable(GL_CULL_FACE);
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 18.f, 50.f));
			glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
			glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(30.f));
			glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;


			GLint worldLoc = glGetUniformLocation(texShader, "modelTransform");
			if (worldLoc < 0)
				std::cout << "worldLoc ã�� ����\n";
			else
				glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(matrix));

			glBindTexture(GL_TEXTURE_2D, BGTexture2);


			glDrawArrays(GL_TRIANGLES, 0, 6);
			glEnable(GL_CULL_FACE);

		}

		glEnable(GL_DEPTH_TEST);
	}

	// �ٴ� ����....
	{
		//glDisable(GL_CULL_FACE);

		glUseProgram(texShader);
		glBindVertexArray(BGVAO);

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.f, 0.f));
		glm::mat4 rotMatrixX = glm::rotate(glm::mat4(1.f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(25.f));
		glm::mat4 matrix = translateMatrix * rotMatrixX * sclaeMatrix;

		GLint worldLoc = glGetUniformLocation(texShader, "modelTransform");
		if (worldLoc < 0)
			std::cout << "worldLoc ã�� ����\n";
		else
			glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint viewLoc = glGetUniformLocation(texShader, "viewTransform");
		if (viewLoc < 0)
			std::cout << "viewLoc ã�� ����\n";
		GLint projLoc = glGetUniformLocation(texShader, "projTransform");
		if (projLoc < 0)
			std::cout << "projLoc ã�� ����\n";

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

		glBindTexture(GL_TEXTURE_2D, GroundTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}




	glUseProgram(shader);

	// ī�޶�, ������ �� ��ü�� ����..
	GLint viewLoc = glGetUniformLocation(shader, "viewTransform");
	if (viewLoc < 0)
		std::cout << "viewLoc ã�� ����\n";
	GLint projLoc = glGetUniformLocation(shader, "projTransform");
	if (projLoc < 0)
		std::cout << "projLoc ã�� ����\n";
	GLint cameraPosLoc = glGetUniformLocation(shader, "cameraPos");
	if (cameraPosLoc < 0)
		std::cout << "cameraPosLoc ã�� ����\n";

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniform3f(cameraPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);


	// ������Ʈ �׸���
	player->draw();		// ���� �÷��̾� �ȱ׸��� �ص�... ���߿� �׸� �� ������ ȣ�����ش�

	/*for (int i = 0; i < objectCount; ++i)
		objects[i]->draw();	*/	// �θ� Ŭ�������� draw�� virtual.. 
		// ���������Լ��� �������⿡ ���� �ڽ�Ŭ������ draw�� �����ͱ׸��°��̴�..
		// virtual keyword ������.. ��ĳ���� �ϸ� �ȵȴ٤�!!!



// --------------------------------- �潺 
	glUseProgram(objShader);

	viewLoc = glGetUniformLocation(objShader, "viewTransform");
	if (viewLoc < 0)
		std::cout << "viewLoc ã�� ����\n";
	projLoc = glGetUniformLocation(objShader, "projTransform");
	if (projLoc < 0)
		std::cout << "projLoc ã�� ����\n";

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

	GLint useGlobalColor = glGetUniformLocation(objShader, "useGlobalColor");

	glUseProgram(texShader);
	GLint useLightColor = glGetUniformLocation(texShader, "lightColor");
	if (useLightColor < 0) {
		std::cout << " lightColor ã�� �� ����.." << std::endl;
	}
	glUniform3f(useLightColor, 1.f, 1.f, 1.f);

	glUseProgram(objShader);
	// �潺 �׸���
	for (int i = 0; i < 6; ++i) {

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-15.f + i * 3.f, 0.f, -8.f));
		glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
		glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		GLuint modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 138 / 255.f, 73 / 255.f, 36 / 255.f);


		glBindVertexArray(fenceVAO);
		glDrawArrays(GL_TRIANGLES, 0, fenceVertexCount);

		////////////////////////////

		translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-17.f, 0.f, -6.f + i * 3.f));
		rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));

		matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		glBindVertexArray(fenceVAO);
		glDrawArrays(GL_TRIANGLES, 0, fenceVertexCount);

		////////////////////////////

		translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(1.f, 0.f, -6.f + i * 3.f));
		rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));

		matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		glBindVertexArray(fenceVAO);
		glDrawArrays(GL_TRIANGLES, 0, fenceVertexCount);

	}

	for (int i = 0; i < 6; ++i) {

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-15.f + i * 3.f, 0.f, 10.f));
		glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
		glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		GLuint modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 138 / 255.f, 73 / 255.f, 36 / 255.f);


		glBindVertexArray(fenceVAO);
		glDrawArrays(GL_TRIANGLES, 0, fenceVertexCount);

	}




	// --------------------------------- 

	// ���� sign


	glUseProgram(texShader);

	// ���� �Ͻ������� ������


	glUniform1i(usingLight, GL_TRUE);

	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 11.5f));
	glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(20.f), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.2f));

	glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;

	GLuint modelLoc = glGetUniformLocation(texShader, "modelTransform");
	if (modelLoc < 0)
		std::cout << " modelLoc ã���� ����!";
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

	glBindVertexArray(sign_bottom_VAO);
	glBindTexture(GL_TEXTURE_2D, signTexture[0]);
	glDrawArrays(GL_TRIANGLES, 0, signBottomVertexCount);

	glBindVertexArray(sign_top_VAO);
	glBindTexture(GL_TEXTURE_2D, signTexture[0]);
	glDrawArrays(GL_TRIANGLES, 0, signTopVertexCount);

	GLuint usingLight = glGetUniformLocation(texShader, "useLight");
	glUniform1i(usingLight, GL_FALSE);

	translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.65f, 11.6f));
	rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(20.f), glm::vec3(0.f, 1.f, 0.f));
	sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.5f/1.5f, 1.f/1.5f, 0.001f));

	matrix = translateMatrix * rotMatrixY * sclaeMatrix;

	modelLoc = glGetUniformLocation(texShader, "modelTransform");
	if (modelLoc < 0)
		std::cout << " modelLoc ã���� ����!";
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

	glBindVertexArray(cubeVAO);
	glBindTexture(GL_TEXTURE_2D, signTexture[1]);
	glDrawArrays(GL_TRIANGLES, 0, cubeVertexCount);

	usingLight = glGetUniformLocation(texShader, "useLight");
	glUniform1i(usingLight, GL_TRUE);


	// -------- ���� ���κ�
	// �׸���....
	glUseProgram(objShader);
	usingLight = glGetUniformLocation(objShader, "useLight");
	glUniform1i(usingLight, GL_TRUE);
	for (int i = 0; i < 10; ++i)
	{
		// Z�޺κ�
		viewLoc = glGetUniformLocation(objShader, "viewTransform");
		if (viewLoc < 0)
			std::cout << "viewLoc ã�� ����\n";
		projLoc = glGetUniformLocation(objShader, "projTransform");
		if (projLoc < 0)
			std::cout << "projLoc ã�� ����\n";

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-20.f + i * 4.f, 0.f, -10.f));
		glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(rotateTreeY[i]), glm::vec3(0.f, 1.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
		glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		GLuint modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 98 / 255.f, 193 / 255.f, 91 / 255.f);

		glBindVertexArray(treeVAO);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount);

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 138 / 255.f, 73 / 255.f, 36 / 255.f);

		glBindVertexArray(treeVAO2);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount2);

		translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-18.f + i * 4.f, 0.f, -15.f));
		rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(rotateTreeY[i]), glm::vec3(0.f, 1.f, 0.f));

		sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
		matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 98 / 255.f, 193 / 255.f, 91 / 255.f);

		glBindVertexArray(treeVAO);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount);

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 138 / 255.f, 73 / 255.f, 36 / 255.f);

		glBindVertexArray(treeVAO2);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount2);

		/////// �翷

		translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(20.f, 0.f, -18.f + i * 4.f));
		rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(rotateTreeY[i]), glm::vec3(0.f, 1.f, 0.f));

		sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
		matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 98 / 255.f, 193 / 255.f, 91 / 255.f);

		glBindVertexArray(treeVAO);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount);

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 138 / 255.f, 73 / 255.f, 36 / 255.f);

		glBindVertexArray(treeVAO2);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount2);

		///////

		translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-20.f, 0.f, -18.f + i * 4.f));
		rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(rotateTreeY[i]), glm::vec3(0.f, 1.f, 0.f));

		sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.f));
		matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 98 / 255.f, 193 / 255.f, 91 / 255.f);

		glBindVertexArray(treeVAO);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount);

		color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 138 / 255.f, 73 / 255.f, 36 / 255.f);

		glBindVertexArray(treeVAO2);
		glDrawArrays(GL_TRIANGLES, 0, treeVertexCount2);
	}

	// --------------------------------- 
	// �� �׸���

	{
		glUseProgram(texShader);
		glBindVertexArray(house_bottom_VAO);
		viewLoc = glGetUniformLocation(texShader, "viewTransform");
		if (viewLoc < 0)
			std::cout << "viewLoc ã�� ����\n";
		projLoc = glGetUniformLocation(texShader, "projTransform");
		if (projLoc < 0)
			std::cout << "projLoc ã�� ����\n";

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(10.f, 0.f, 0.f));
		glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.3f));
		glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		GLuint modelLoc = glGetUniformLocation(texShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));


		glBindTexture(GL_TEXTURE_2D, houseTexture[0]);
		glDrawArrays(GL_TRIANGLES, 0, houseBottomVertexCount);
	}

	{
		glUseProgram(objShader);
		glBindVertexArray(house_top_VAO);
		viewLoc = glGetUniformLocation(objShader, "viewTransform");
		if (viewLoc < 0)
			std::cout << "viewLoc ã�� ����\n";
		projLoc = glGetUniformLocation(objShader, "projTransform");
		if (projLoc < 0)
			std::cout << "projLoc ã�� ����\n";

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(10.f, 0.f, 0.f));
		glm::mat4 rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));

		glm::mat4 sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.3f));
		glm::mat4 matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		GLuint modelLoc = glGetUniformLocation(objShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		GLint color = glGetUniformLocation(objShader, "globalColor");
		glUniform1i(useGlobalColor, GL_TRUE);
		if (color < 0)
			std::cout << "globalColor ã�� ����\n";
		else
			glUniform3f(color, 255 / 255.f, 178 / 255.f, 217 / 255.f);


		glDrawArrays(GL_TRIANGLES, 0, houseTopVertexCount);
	}

	{
		glUseProgram(texShader);

		GLuint usingLight = glGetUniformLocation(texShader, "useLight");
		glUniform1i(usingLight, GL_FALSE);

		translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(10.f, 3.f, 1.8f));
		rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
		sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(2.f,1.f, 0.001f));

		matrix = translateMatrix * rotMatrixY * sclaeMatrix;

		modelLoc = glGetUniformLocation(texShader, "modelTransform");
		if (modelLoc < 0)
			std::cout << " modelLoc ã���� ����!";
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

		glBindVertexArray(cubeVAO);
		glBindTexture(GL_TEXTURE_2D, houseTexture[1]);
		glDrawArrays(GL_TRIANGLES, 0, cubeVertexCount);

		usingLight = glGetUniformLocation(texShader, "useLight");
		glUniform1i(usingLight, GL_TRUE);
	}



	if (player->isStoreShow) {
		{
			
			glUseProgram(texShader);

			GLuint usingLight = glGetUniformLocation(texShader, "useLight");
			glUniform1i(usingLight, GL_FALSE);

			translateMatrix = glm::translate(glm::mat4(1.f), glm::vec3(10.f,1.f,1.6f));
			rotMatrixY = glm::rotate(glm::mat4(1.f), glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
			sclaeMatrix = glm::scale(glm::mat4(1.f), glm::vec3(2.f, 2.f, 0.001f));

			matrix = translateMatrix * rotMatrixY * sclaeMatrix;

			modelLoc = glGetUniformLocation(texShader, "modelTransform");
			if (modelLoc < 0)
				std::cout << " modelLoc ã���� ����!";
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));

			glBindVertexArray(cubeVAO);
			glBindTexture(GL_TEXTURE_2D, houseTexture[1]);
			glDrawArrays(GL_TRIANGLES, 0, cubeVertexCount);

			usingLight = glGetUniformLocation(texShader, "useLight");
			glUniform1i(usingLight, GL_TRUE);
		}
	}
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

void Scene::initCubeBuffer(GLuint* VAO, GLsizei* vertexCount)
{
	glGenVertexArrays(1, VAO);		// ���� �Ҵ�....
	glBindVertexArray(*VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	*vertexCount = 36;

	float size = 0.5f;
	float vertexData[6 * 2 * 3 * 9]{ // 6��, ��� 2�ﰢ��, �ﰢ���� ��3��, ���� 9���� --> 324
		// px, py, pz,		tx, ty, tz=0,	 nx, ny, nz

		//Front					// ���Ⱑ �ؽ�ó ��ǥ�� (���� ���⼱ �ؽ�ó��ǥ�� ���ʾƷ��� 0,0 �������� ����!!)
		-size, -size, size,		0, 0, 0,	1, 0, 0,
		size, -size, size,		1, 0, 0,	1, 0, 0,
		size, size, size,		1, 1, 0,	1, 0, 0,
		size, size, size,		1, 1, 0,	1, 0, 0,
		-size, size, size,		0, 1, 0,	1, 0, 0,
		-size, -size, size,		0, 0, 0,	1, 0, 0,
		//Back
		-size, -size, -size,	1, 0, 0,	0, 1, 0,
		-size, size, -size,		1, 1, 0,	0, 1, 0,
		size, size, -size,		0, 1, 0,	0, 1, 0,
		size, size, -size,		0, 1, 0,	0, 1, 0,
		size, -size, -size,		0, 0, 0,	0, 1, 0,
		-size, -size, -size,	1, 0, 0,	0, 1, 0,
		//Left
		-size, -size, size,		1, 0, 0,	0, 0, 1,
		-size, size, size,		1, 1, 0,	0, 0, 1,
		-size, size, -size,		0, 1, 0,	0, 0, 1,
		-size, size, -size,		0, 1, 0,	0, 0, 1,
		-size, -size, -size,	0, 0, 0,	0, 0, 1,
		-size, -size, size,		1, 0, 0,	0, 0, 1,
		//Right
		size, -size, size,		0, 0, 0,	1, 1, 0,
		size, -size, -size,		1, 0, 0,	1, 1, 0,
		size, size, -size,		1, 1, 0,	1, 1, 0,
		size, size, -size,		1, 1, 0,	1, 1, 0,
		size, size, size,		0, 1, 0,	1, 1, 0,
		size, -size, size,		0, 0, 0,	1, 1, 0,
		//Top
		-size, size, size,		0, 0, 0,	1, 0, 1,
		size, size, size,		1, 0, 0,	1, 0, 1,
		size, size, -size,		1, 1, 0,	1, 0, 1,
		size, size, -size,		1, 1, 0,	1, 0, 1,
		-size, size, -size,		0, 1, 0,	1, 0, 1,
		-size, size, size,		0, 0, 0,	1, 0, 1,
		//Bottom
		-size, -size, size,		0, 0, 0,	0, 1, 1,
		-size, -size, -size,	1, 0, 0,	0, 1, 1,
		size, -size, -size,		1, 1, 0,	0, 1, 1,
		size, -size, -size,		1, 1, 0,	0, 1, 1,
		size, -size, size,		0, 1, 0,	0, 1, 1,
		-size, -size, size,		0, 0, 0,	0, 1, 1
	};

	// CPU �޸𸮿� �ִ� �����͸�, GPU �޸𸮿� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 324, vertexData, GL_STATIC_DRAW);

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


void Scene::initBufferWithUV(GLuint* VAO, GLsizei* vertexCount, std::string objFilename)
{
	glGenVertexArrays(1, VAO);		// ���� �Ҵ�....
	glBindVertexArray(*VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<glm::vec3> verticies = readOBJWithUV(objFilename);

	*vertexCount = verticies.size() / 3;

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

