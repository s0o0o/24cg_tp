#include "startScene.h"
#include "startScene.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>


startScene::startScene(int winWidth, int winHeight)
	: width{ winWidth }, height{ winHeight }
{
}

startScene::~startScene()
{
	
}

void startScene::initialize()
{
	isShow = false;
	
}

void startScene::release()
{
	
}

void startScene::update(float elapsedTime)
{

}

void startScene::draw() const
{
	
}

void startScene::keyboard(unsigned char key, bool isPressed)
{
	

	if (isPressed) {			// �������� ��
		switch (key) {
		case 32:
			isShow = not isShow;
			std::cout << " �����̽��� ����!" << std::endl;
			break;
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

void startScene::specialKeyboard(int key, bool isPressed)
{
}

void startScene::mouse(int button, int state, int x, int y)
{


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

void startScene::mouseMove(int x, int y)
{
	
}

void startScene::setWindowSize(int winWidth, int winHeight)
{
	width = winWidth;
	height = winHeight;
}

void startScene::initBuffer(GLuint* VAO, GLsizei* vertexCount, std::string objFilename)
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

GLuint startScene::makeShader(std::string vertexFilename, std::string fragmentFilename)
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

std::string startScene::readFile(std::string filename)
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

std::vector<glm::vec3> startScene::readOBJ(std::string filename)
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
