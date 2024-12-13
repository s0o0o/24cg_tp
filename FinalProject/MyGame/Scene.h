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

	PlayerObject* player;

	GameObject* objects[10];

	int objectCount;

	int width;
	int height;

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
	static void initCubeBuffer(GLuint* VAO, GLsizei* vertexCount, std::string objFilename);

	static void initBufferWithUV(GLuint* VAO, GLsizei* vertexCount, std::string objFilename);

	static void initTexture(GLuint* texture, int size, std::string* texFilename);
	void initBackGroundBuffer();

public:
	static GLuint makeShader(std::string vertexFilename, std::string fragmentFilename);
	static std::string readFile(std::string filename);
	static std::vector<glm::vec3> readOBJ(std::string filename);

	static std::vector<glm::vec3> readOBJWithUV(std::string filename);
};

