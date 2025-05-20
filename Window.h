#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>
class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getrotacionPersonajeY() { return rotacionPersonajeY; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getmueveLink() { return mueveLink; }
	GLfloat getmueveLinkz() { return mueveLinkz; }
	bool getavanzaBomba() const { return avanzaBomba; }
	float articulacionBrazo = 0.0f;
	int direccionBrazo = 1;
	bool brazoOscilando = false;
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax, rotay, rotaz, articulacion1, articulacion2, articulacion3, articulacion4;
	int direccionPiernaIzq = 1;
	int direccionPiernaDer = -1;
	bool keys[1024];
	bool avanzaBomba;
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat mueveLink, mueveLinkz, rotacionPersonajeY;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

