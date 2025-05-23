#include "Window.h"
Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	mueveLink = 2.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto Final CGeIHC: Feria", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> mueveLink += 1.0;
		theWindow->rotacionPersonajeY = 0.0f;
		// Pierna 1 (izquierda)
		theWindow->articulacion1 += 5.0f * theWindow->direccionPiernaIzq;
		if (theWindow->articulacion1 >= 45.0f)
			theWindow->direccionPiernaIzq = -1;
		else if (theWindow->articulacion1 <= -45.0f)
			theWindow->direccionPiernaIzq = 1;

		// Pierna 2 (derecha)
		theWindow->articulacion2 += 5.0f * theWindow->direccionPiernaDer;
		if (theWindow->articulacion2 >= 45.0f)
			theWindow->direccionPiernaDer = -1;
		else if (theWindow->articulacion2 <= -45.0f)
			theWindow->direccionPiernaDer = 1;
	}
	
	if (key == GLFW_KEY_U)
	{
		theWindow-> mueveLink -= 1.0;
		theWindow->rotacionPersonajeY = 180.0f;
		theWindow->articulacion1 += 5.0f * theWindow->direccionPiernaIzq;
		if (theWindow->articulacion1 >= 45.0f)
			theWindow->direccionPiernaIzq = -1;
		else if (theWindow->articulacion1 <= -45.0f)
			theWindow->direccionPiernaIzq = 1;

		// Pierna 2 (derecha)
		theWindow->articulacion2 += 5.0f * theWindow->direccionPiernaDer;
		if (theWindow->articulacion2 >= 45.0f)
			theWindow->direccionPiernaDer = -1;
		else if (theWindow->articulacion2 <= -45.0f)
			theWindow->direccionPiernaDer = 1;

	}
	if (key == GLFW_KEY_J)
	{
		theWindow->mueveLinkz += 1.0;
		theWindow->rotacionPersonajeY = -90.0f;
		// Pierna 1 (izquierda)
		theWindow->articulacion1 += 5.0f * theWindow->direccionPiernaIzq;
		if (theWindow->articulacion1 >= 45.0f)
			theWindow->direccionPiernaIzq = -1;
		else if (theWindow->articulacion1 <= -45.0f)
			theWindow->direccionPiernaIzq = 1;

		// Pierna 2 (derecha)
		theWindow->articulacion2 += 5.0f * theWindow->direccionPiernaDer;
		if (theWindow->articulacion2 >= 45.0f)
			theWindow->direccionPiernaDer = -1;
		else if (theWindow->articulacion2 <= -45.0f)
			theWindow->direccionPiernaDer = 1;
	}

	if (key == GLFW_KEY_H)
	{
		theWindow->mueveLinkz -= 1.0;
		theWindow->rotacionPersonajeY = 90.0f;
		theWindow->articulacion1 += 5.0f * theWindow->direccionPiernaIzq;
		if (theWindow->articulacion1 >= 45.0f)
			theWindow->direccionPiernaIzq = -1;
		else if (theWindow->articulacion1 <= -45.0f)
			theWindow->direccionPiernaIzq = 1;

		// Pierna 2 (derecha)
		theWindow->articulacion2 += 5.0f * theWindow->direccionPiernaDer;
		if (theWindow->articulacion2 >= 45.0f)
			theWindow->direccionPiernaDer = -1;
		else if (theWindow->articulacion2 <= -45.0f)
			theWindow->direccionPiernaDer = 1;

	}
	if (key == GLFW_KEY_O)
	{
		theWindow->articulacion3 += 5.0f * theWindow->direccionBrazo;
		if (theWindow->articulacion3 >= 0.0f)
			theWindow->direccionBrazo = -1;
		else if (theWindow->articulacion3 <= -90.0f)
			theWindow->direccionBrazo = 1;

	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
