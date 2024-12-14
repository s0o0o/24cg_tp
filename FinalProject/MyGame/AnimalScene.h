#pragma once

#include "library.h"

#include <string>
#include <vector>

class GameObject;
class PlayerObject;


class Scene
{
private:
	GLuint shader;
	GLuint plainShader;
	GLuint BackGroundShader;

	GLuint sphereVAO;
	int sphereVertexCount;
	GLuint teapotVAO;
	int teapotVertexCount;

	GLuint fenceVAO, BGTexture, BGVAO;
	int fenceVertexCount;
	GameObject* townObjects[20];

	GLuint cubeVAO;
	int cubeVertexCount;

	PlayerObject* player;

	GameObject* objects[10];

	int objectCount;

	int width;
	int height;

	//팔 혹은 다리 회전 관련 변수
	bool isMaxRotateBaby; // 각도 제한
	bool isMaxRotatePig;
	bool isMaxRotateAlpa;
	bool isMaxRotateChic;
	bool isMaxRotateAudultChic;
	bool isMaxRotatePenguin;
	bool isMaxRotateFox;

	float rotateSpeed; // 각도 변화

	//아기돼지 변수>> 전체위치 yz, 왼오 다리각도, 바라보는것
	float moveBabyX;
	float moveBabyZ;
	float rotateBabyLeftLeg;
	float rotateBabyRightLeg;
	float rotateFaceBaby;

	//돼지 변수>> 전체위치 yz, 왼오 다리각도, 바라보는 것
	float movePigX;
	float movePigZ;
	float rotatePigLeftLeg;
	float rotatePigRightLeg;
	float rotateFacePig;

	//알파카 변수 >> 전체위치 yz, 왼오 다리각도, 바라보는 것
	float moveAlpaX;
	float moveAlpaZ;
	float rotateAlpaLeftLeg;
	float rotateAlpaRightLeg;
	float rotateFaceAlpa;

	//병아리 변수>> 전체위치 yz, 왼오 다리각도, 바라보는 것
	float moveChicX;
	float moveChicZ;
	float rotateChicLeftLeg;
	float rotateChicRightLeg;
	float rotateFaceChic;

	//닭 변수 >> 전체위치 yz, 왼오 다리각도, 바라보는 것
	float moveAdultChicX;
	float moveAdultChickZ;
	float rotateAudultChicLeftLeg;
	float rotateAudultChicRightLeg;
	float rotateFaceAudultChic;

	//펭귄 변수>> 전체위치 yz, 왼오 다리각도, 왼오 날개각도, 바라보는 것
	float movePenguinX;
	float movePenguinZ;
	float rotatePenguinLeftArm;
	float rotatePenguinRightArm;
	float rotateFacePenguin;

	//여우 변수 >> 전체위치 yz, 왼오 다리각도, 바라보는 것
	float moveFoxX;
	float moveFoxZ;
	float rotateFoxLeftLeg;
	float rotateFoxRightLeg;
	float rotateFaceFox;

public:
	// 게임 로직에서, update, draw..., 키 입력
	Scene(int winWidth, int winHeight);
	~Scene();

	void initialize();
	void release();

	void update(float elapsedTime);

	void draw() const;

	void keyboard(unsigned char key, bool isPressed);
	void specialKeyboard(int key, bool isPressed);
	void mouse(int button, int state, int x, int y);
	void mouseMove(int x, int y);

	void setWindowSize(int winWidth, int winHeight);


private:
	static void initBuffer(GLuint* VAO, GLsizei* vertexCount, std::string objFilename);
	static void initTexture(GLuint* texture, int size, std::string* texFilename);
	void initBackGroundBuffer();

public:
	static GLuint makeShader(std::string vertexFilename, std::string fragmentFilename);
	static std::string readFile(std::string filename);
	static std::vector<glm::vec3> readOBJ(std::string filename);

	static std::vector<glm::vec3> readOBJWithUV(std::string filename);
};

