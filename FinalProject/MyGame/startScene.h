#pragma once

#include "library.h"

#include <string>
#include <vector>

class startScene
{
private:
	GLuint shader;
	GLuint plainShader;

	

	int width;
	int height;

public:
	// 게임 로직에서, update, draw..., 키 입력
	startScene(int winWidth, int winHeight);
	~startScene();

	void initialize();
	void release();

	void update(float elapsedTime);

	void draw() const;

	void keyboard(unsigned char key, bool isPressed);
	void specialKeyboard(int key, bool isPressed);
	void mouse(int button, int state, int x, int y);
	void mouseMove(int x, int y);

	void setWindowSize(int winWidth, int winHeight);

	bool isShow;

private:
	static void initBuffer(GLuint* VAO, GLsizei* vertexCount, std::string objFilename);

public:
	static GLuint makeShader(std::string vertexFilename, std::string fragmentFilename);
	static std::string readFile(std::string filename);
	static std::vector<glm::vec3> readOBJ(std::string filename);

};

