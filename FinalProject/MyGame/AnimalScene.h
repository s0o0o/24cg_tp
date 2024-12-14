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

	//�� Ȥ�� �ٸ� ȸ�� ���� ����
	bool isMaxRotateBaby; // ���� ����
	bool isMaxRotatePig;
	bool isMaxRotateAlpa;
	bool isMaxRotateChic;
	bool isMaxRotateAudultChic;
	bool isMaxRotatePenguin;
	bool isMaxRotateFox;

	float rotateSpeed; // ���� ��ȭ

	//�Ʊ���� ����>> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴°�
	float moveBabyX;
	float moveBabyZ;
	float rotateBabyLeftLeg;
	float rotateBabyRightLeg;
	float rotateFaceBaby;

	//���� ����>> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	float movePigX;
	float movePigZ;
	float rotatePigLeftLeg;
	float rotatePigRightLeg;
	float rotateFacePig;

	//����ī ���� >> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	float moveAlpaX;
	float moveAlpaZ;
	float rotateAlpaLeftLeg;
	float rotateAlpaRightLeg;
	float rotateFaceAlpa;

	//���Ƹ� ����>> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	float moveChicX;
	float moveChicZ;
	float rotateChicLeftLeg;
	float rotateChicRightLeg;
	float rotateFaceChic;

	//�� ���� >> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	float moveAdultChicX;
	float moveAdultChickZ;
	float rotateAudultChicLeftLeg;
	float rotateAudultChicRightLeg;
	float rotateFaceAudultChic;

	//��� ����>> ��ü��ġ yz, �޿� �ٸ�����, �޿� ��������, �ٶ󺸴� ��
	float movePenguinX;
	float movePenguinZ;
	float rotatePenguinLeftArm;
	float rotatePenguinRightArm;
	float rotateFacePenguin;

	//���� ���� >> ��ü��ġ yz, �޿� �ٸ�����, �ٶ󺸴� ��
	float moveFoxX;
	float moveFoxZ;
	float rotateFoxLeftLeg;
	float rotateFoxRightLeg;
	float rotateFaceFox;

public:
	// ���� ��������, update, draw..., Ű �Է�
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

