#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <map>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movOffset;
float rotllanta;
float rotllantaOffset;
float mueveBombaz;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulo = glm::radians(180.0f);  
float angulovaria = 0.0f;
bool cambio;
bool avanzaSumo;
bool avanza;
bool avanzaTopo = false;
float movTopo;
float movTopoo;
float rotaSumo;
float movSumo;
int aux;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;



Texture pastoTexture;
Texture Topos;
Texture JuegoTopos;

Texture LetrasTexture;


Model Arbol_M;
Model Tronco_M;
Model Luz_M;
Model Banco_M;
Model Mesa_Banco_M;
Model BañoM_M;
Model BañoH_M;
Model Miche_M;
//DARDOS
Model Carpa_M;
Model Dardo_M;
Model Escalera_M;
Model GloboA_M;
Model GloboV_M;
Model GloboR_M;
Model GloboM_M;
Model GloboN_M;
Model GloboC_M;
Model Peluche_M;
Model Tablero_M;
//PINOS
Model Bomba_M;
Model BombaS_M;
Model Linea_M;
Model Pantalla_M;
Model Pino_M;
// JAULA BATEO
Model Bola_M;
Model Caja_M;
Model Campo_M;
Model Cofre_M;
Model Espada_M;
Model Reflector_M;
Model Reja_M;
// HOCEEEEES
Model Banda_M;
Model BlancoD_M;
Model BlancoI_M;
Model CarpaH_M;
Model Hoz_M;
//
// DADOOOOOOOS
Model CarpaD_M;
Model Dado_M;
Model Letrero1_M;
Model Letrero2_M;
Model MesaD_M;
Model PelucheD_M;
Model RepisaR_M;
//TOPOOO
Model JuegoTopos_M;
Model Topos_M;
Model Topo1_M;
Model Topo2_M;
Model Topo3_M;
Model Topo4_M;
Model Topo5_M;
Model Topo6_M;
Model Mazo_M;
//Link
Model CabezaLink_M;
Model CuerpoLink_M;
Model SombreroLink_M;
Model BotaDerLink_M;
Model BotaIzqLink_M;
Model BrazoDerLink_M;
Model BrazoIzqLink_M;
Model PiernaDerLink_M;
Model PiernaIzqLink_M;
Model VainaLink_M;
// Clarence
Model ClarenceC_M;
Model ClarencePD_M;
Model ClarencePI_M;
Model ClarenceBD_M;
Model ClarenceBI_M;
//JEFF
Model JeffC_M;
Model JeffPD_M;
Model JeffPI_M;
Model JeffBD_M;
Model JeffBI_M;
//SUMO
Model SumoC_M;
Model SumoPD_M;
Model SumoPI_M;
Model SumoBD_M;
Model SumoBI_M;
//GUMBAAAL
Model Gumball_Carro_M;
Model Carrie_Krueger_M;
Model Gumball_M;
Model Darwin_M;
Model Penny_M;
Model Pork_Cassidy_M;
Model Teri_M;
Model Puerta_M;
Model Letrero_M;


Model _M;
Skybox skybox;



//materiales
Material Material_brillante;
Material Material_opaco;

Material Material_link;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
static float acumuladorr = 0.0f;
//Variables texto
std::string textoActual = "PROYECTO CGEIHC"; // Texto inicial
float tiempoRotacion = 0.5f; // Tiempo entre rotaciones (en segundos)
float tiempoUltimaRotacion = 0.0f;
// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};
	//Piso que mide 20 unidades
	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	1.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		1.0f, 1.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj1);

	//aggarra solo una region letra
	unsigned int letraIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letraVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.00f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.11f, 0.00f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.11f, 0.33f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 0.33f,		    0.0f, -1.0f, 0.0f,

	};

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(letraVertices, letraIndices, 32, 6);
	meshList.push_back(obj2);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}





std::map<char, glm::vec4> letraUVs;
void InicializarMapaLetras() {
	int columnas = 9;
	int filas = 3;
	float anchoCelda = 1.0f / columnas;
	float altoCelda = 1.0f / filas;

	std::string letras = "ABCDEFGHI"
		"JKLMNOPQR"
		"STUVWXYZ";

	for (int fila = 0; fila < filas; ++fila) {
		for (int columna = 0; columna < columnas; ++columna) {
			char letra = letras[fila * columnas + columna];
			float u_min = columna * anchoCelda;
			float v_min = 1.0f - (fila + 1) * altoCelda; // Desde la parte superior
			float u_max = (columna + 1) * anchoCelda;
			float v_max = 1.0f - fila * altoCelda;

			letraUVs[letra] = glm::vec4(u_min, v_min, u_max, v_max);

		}
	}
}



void RenderTextoEstatico(const std::string& texto, glm::vec3 posicionInicial,
	float separacion, GLuint uniformModel, GLuint uniformTextureOffset) {
	for (size_t i = 0; i < texto.size(); ++i) {
		char letra = texto[i];

		// Verifica si la letra está en el mapa de UVs
		if (letraUVs.find(letra) == letraUVs.end()) continue;

		glm::vec4 uv = letraUVs[letra]; // Coordenadas UV de la letra
		glm::vec2 toffset = glm::vec2(uv.x, uv.y);

		// Calcula la posición de la letra
		glm::vec3 posicionLetra = posicionInicial + glm::vec3(0.0f, 0.0f, i * separacion);

		// Renderiza la letra
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, posicionLetra);
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotación al plano XY
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación al plano XY
		model = glm::scale(model, glm::vec3(1.4f, 4.5f, 4.5f)); // Aplica la escala
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		LetrasTexture.UseTexture();
		meshList[1]->RenderMesh(); // Usa un plano para renderizar la letra
	}
}

std::string RotarTexto(const std::string& texto) {
	if (texto.empty()) return texto; // Si el texto está vacío, no hacer nada
	return texto.substr(1) + texto[0]; // Mueve la primera letra al final
}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();


	CreateObjects();
	CreateShaders();
	InicializarMapaLetras();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);


	pastoTexture = Texture("Textures/pastoCamino.tga");
	pastoTexture.LoadTextureA();

	JuegoTopos = Texture("Textures/juegoTopo.png");
	JuegoTopos.LoadTextureA();
	Topos = Texture("Textures/moleAtlas.png");
	Topos.LoadTextureA();
	Arbol_M = Model();
	Arbol_M.LoadModel("Models/Arboles/Arbol/Arbol.obj");
	Mesa_Banco_M = Model();
	Mesa_Banco_M.LoadModel("Models/Espacio/Mesa_Banco.obj");
	Banco_M = Model();
	Banco_M.LoadModel("Models/Espacio/Banco.obj");
	Tronco_M = Model();
	Tronco_M.LoadModel("Models/Arboles/Tronco/Tronco.obj");
	Luz_M = Model();
	Luz_M.LoadModel("Models/Espacio/luz.obj");
	BañoH_M = Model();
	BañoH_M.LoadModel("Models/Baños/Hombre/bañoH.obj");
	BañoM_M = Model();
	BañoM_M.LoadModel("Models/Baños/Mujer/bañoM.obj");
	Miche_M = Model();
	Miche_M.LoadModel("Models/Miche/micheladas.obj");
	//dardos
	Carpa_M = Model();
	Carpa_M.LoadModel("Models/Dardos/Carpa/carpa.obj");
	Dardo_M = Model();
	Dardo_M.LoadModel("Models/Dardos/Dardo/dardo.obj");
	Escalera_M = Model();
	Escalera_M.LoadModel("Models/Dardos/Escalera/escalera.obj");
	GloboA_M = Model();
	GloboA_M.LoadModel("Models/Dardos/Globos/globo_amarillo.obj");
	GloboM_M = Model();
	GloboM_M.LoadModel("Models/Dardos/Globos/globo_magenta.obj");
	GloboN_M = Model();
	GloboN_M.LoadModel("Models/Dardos/Globos/globo_naranja.obj");
	GloboR_M = Model();
	GloboR_M.LoadModel("Models/Dardos/Globos/globo_rojo.obj");
	GloboV_M = Model();
	GloboV_M.LoadModel("Models/Dardos/Globos/globo_verde.obj");
	GloboC_M = Model();
	GloboC_M.LoadModel("Models/Dardos/Globos/globo_cian.obj");
	Peluche_M = Model();
	Peluche_M.LoadModel("Models/Dardos/Peluche/peluches.obj");
	//bolos
	Tablero_M = Model();
	Tablero_M.LoadModel("Models/Dardos/Tablero/tablero.obj");
	Bomba_M = Model();
	Bomba_M.LoadModel("Models/Boliche/Bomba/bomba.obj");
	BombaS_M = Model();
	BombaS_M.LoadModel("Models/Boliche/Bomba/bombaSola.obj");
	Linea_M = Model();
	Linea_M.LoadModel("Models/Boliche/Linea/linea.obj");
	Pantalla_M = Model();
	Pantalla_M.LoadModel("Models/Boliche/Pantalla/pantalla.obj");
	Pino_M = Model();
	Pino_M.LoadModel("Models/Boliche/Pino/pino.obj");
	//Jaula de bateo
	Bola_M = Model();
	Bola_M.LoadModel("Models/JaulaBateo/Bola/pinecone.obj");
	Caja_M = Model();
	Caja_M.LoadModel("Models/JaulaBateo/Caja/caja.obj");
	Campo_M = Model();
	Campo_M.LoadModel("Models/JaulaBateo/Campo/campo.obj");
	Cofre_M = Model();
	Cofre_M.LoadModel("Models/JaulaBateo/Cofre/cofre.obj");
	Espada_M = Model();
	Espada_M.LoadModel("Models/JaulaBateo/Espada/espada.obj");
	Reflector_M = Model();
	Reflector_M.LoadModel("Models/JaulaBateo/Reflector/reflector.obj");
	Reja_M = Model();
	Reja_M.LoadModel("Models/JaulaBateo/Reja/reja.obj");
	//HOCEEES
	Banda_M = Model();
	Banda_M.LoadModel("Models/Hoces/Banda/bandaHoces.obj");
	BlancoD_M = Model();
	BlancoD_M.LoadModel("Models/Hoces/Blancos/BlancoDerechoHoces.obj");
	BlancoI_M = Model();
	BlancoI_M.LoadModel("Models/Hoces/Blancos/BlancoIzquierdoHoces.obj");
	CarpaH_M = Model();
	CarpaH_M.LoadModel("Models/Hoces/Carpa/CarpaHoces.obj");
	Hoz_M = Model();
	Hoz_M.LoadModel("Models/Hoces/Hoz/Hoz.obj");
	// DADOOOOOOOOOD
	CarpaD_M = Model();
	CarpaD_M.LoadModel("Models/Dados/Carpa_Dados.obj");
	Dado_M = Model();
	Dado_M.LoadModel("Models/Dados/Dado.obj");
	Letrero1_M = Model();
	Letrero1_M.LoadModel("Models/Dados/Letrero1.obj");
	Letrero2_M = Model();
	Letrero2_M.LoadModel("Models/Dados/Letrero2.obj");
	MesaD_M = Model();
	MesaD_M.LoadModel("Models/Dados/Mesa_Dados.obj");
	PelucheD_M = Model();
	PelucheD_M.LoadModel("Models/Dados/Peluches.obj");
	RepisaR_M = Model();
	RepisaR_M.LoadModel("Models/Dados/Repisa_Roja.obj");
	//TOPOOO
	JuegoTopos_M = Model();
	JuegoTopos_M.LoadModel("Models/JuegoTopos/Base/juegoTopo.obj");
	Topos_M = Model();
	Topos_M.LoadModel("Models/JuegoTopos/Base/TopoComp.obj");
	Topo1_M = Model();
	Topo1_M.LoadModel("Models/JuegoTopos/TopoBajoDerecho/topoBajoDerecho.obj");
	Topo2_M = Model();
	Topo2_M.LoadModel("Models/JuegoTopos/TopoBajoMedio/topoBajoMedio.obj");
	Topo3_M = Model();
	Topo3_M.LoadModel("Models/JuegoTopos/TopoBajoIzquierdo/topoBajoIzquierdo.obj");
	Topo4_M = Model();
	Topo4_M.LoadModel("Models/JuegoTopos/TopoSuperiorDerecho/topoSuperiorDerecho.obj");
	Topo5_M = Model();
	Topo5_M.LoadModel("Models/JuegoTopos/TopoSuperiorMedio/topoSuperiorMedio.obj");
	Topo6_M = Model();
	Topo6_M.LoadModel("Models/JuegoTopos/TopoSuperiorIzquierdo/topoSuperiorIzquierdo.obj");
	Mazo_M = Model();
	Mazo_M.LoadModel("Models/JuegoTopos/Mazo/mazo.obj");


	//link
	CabezaLink_M = Model();
	CabezaLink_M.LoadModel("Models/Link/cabeza.obj");
	CuerpoLink_M = Model();
	CuerpoLink_M.LoadModel("Models/Link/cuerpo.obj");
	BrazoDerLink_M = Model();
	BrazoDerLink_M.LoadModel("Models/Link/brazo_der.obj");
	BrazoIzqLink_M = Model();
	BrazoIzqLink_M.LoadModel("Models/Link/brazo_izq.obj");
	PiernaDerLink_M = Model();
	PiernaDerLink_M.LoadModel("Models/Link/pierna_der.obj");
	PiernaIzqLink_M = Model();
	PiernaIzqLink_M.LoadModel("Models/Link/pierna_izq.obj");
	VainaLink_M = Model();
	VainaLink_M.LoadModel("Models/Link/vaina.obj");
	SombreroLink_M = Model();
	SombreroLink_M.LoadModel("Models/Link/sombrero.obj");
	//Clarence
	ClarenceC_M = Model();
	ClarenceC_M.LoadModel("Models/Clarence/cuerpoClarence.obj");
	ClarencePD_M = Model();
	ClarencePD_M.LoadModel("Models/Clarence/piernaDerClarence.obj");
	ClarencePI_M = Model();
	ClarencePI_M.LoadModel("Models/Clarence/piernaIzqClarence.obj");
	ClarenceBD_M = Model();
	ClarenceBD_M.LoadModel("Models/Clarence/brazoDerClarence.obj");
	ClarenceBI_M = Model();
	ClarenceBI_M.LoadModel("Models/Clarence/brazoizqClarence.obj");
	//Jeff
	JeffC_M = Model();
	JeffC_M.LoadModel("Models/jeff/source/jeffcuerpo.obj");
	JeffPD_M = Model();
	JeffPD_M.LoadModel("Models/jeff/source/jeffpiernaDer.obj");
	JeffPI_M = Model();
	JeffPI_M.LoadModel("Models/jeff/source/jeffpiernaIzq.obj");
	JeffBD_M = Model();
	JeffBD_M.LoadModel("Models/jeff/source/jeffbrazoDer.obj");
	JeffBI_M = Model();
	JeffBI_M.LoadModel("Models/jeff/source/jeffbrazoIzq.obj");
	//Sumo
	SumoC_M = Model();
	SumoC_M.LoadModel("Models/Sumo/source/sumocuerpo.obj");
	SumoPD_M = Model();
	SumoPD_M.LoadModel("Models/Sumo/source/sumopiernader.obj");
	SumoPI_M = Model();
	SumoPI_M.LoadModel("Models/Sumo/source/sumopiernaizq.obj");
	SumoBD_M = Model();
	SumoBD_M.LoadModel("Models/Sumo/source/sumobrazodercho.obj");
	SumoBI_M = Model();
	SumoBI_M.LoadModel("Models/Sumo/source/sumoBrazoizq.obj");


	//GUMABALLL
	Gumball_Carro_M = Model();
	Gumball_Carro_M.LoadModel("Models/Gumball-Car/Gumball-Car.obj");
	Carrie_Krueger_M = Model();
	Carrie_Krueger_M.LoadModel("Models/Carrie-Krueger/Carrie-Krueger.obj");
	Gumball_M = Model();
	Gumball_M.LoadModel("Models/Gumball/gumball.obj");
	Darwin_M = Model();
	Darwin_M.LoadModel("Models/Darwin/Darwin.obj");
	Penny_M = Model();
	Penny_M.LoadModel("Models/Penny/pennyM.obj");
	Pork_Cassidy_M = Model();
	Pork_Cassidy_M.LoadModel("Models/Pork-Cassidy/Pork-Cassidy.obj");
	Teri_M = Model();
	Teri_M.LoadModel("Models/Teri/Teri.obj");

	Puerta_M = Model();
	Puerta_M.LoadModel("Models/puerta.obj");
	Letrero_M = Model();
	Letrero_M.LoadModel("Models/letrero.obj");


	LetrasTexture = Texture("Textures/letras.png");
	LetrasTexture.LoadTextureA();





	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cube_right.png");
	skyboxFaces.push_back("Textures/Skybox/cube_left.png");
	skyboxFaces.push_back("Textures/Skybox/cube_down.png");
	skyboxFaces.push_back("Textures/Skybox/cube_up.png");
	skyboxFaces.push_back("Textures/Skybox/cube_back.png");
	skyboxFaces.push_back("Textures/Skybox/cube_front.png");

	skybox = Skybox(skyboxFaces);

	Material_link = Material(0.0f, 1);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales




	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movSumo = 0.0f;
	movOffset = 0.01f;
	rotllanta = 0.0f;
	rotaSumo = 0.0f;
	rotllantaOffset = 10.0f;
	cambio = true;
	avanzaSumo = true;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		acumuladorr += deltaTime;


		angulovaria += 0.5f * deltaTime;

		if (avanzaSumo) {
			if (movSumo< 100.0f)
			{
				movSumo += movOffset * deltaTime;
			}
			else {
				avanzaSumo = false;
				rotaSumo = 180.0f;
			}
		}
		else {
			if (movSumo > -1.0f)
			{
				movSumo -= movOffset * deltaTime;
			}
			else {
				avanzaSumo = true;
				rotaSumo = 0.0f;
			}

		}
		if (avanzaTopo) {
			if (movTopo < 0.0f)
			{
				movTopo += movOffset * deltaTime;
			}
			else {
				avanzaTopo = false;
			}
			if (movTopoo > -0.30f)
			{
				movTopoo -= movOffset * deltaTime;
			}
		}
		else {
			if (movTopo > -0.30f)
			{
				movTopo -= movOffset * deltaTime;
			}
			else {
				avanzaTopo = true;
			}
			if (movTopoo < 0.0f)
			{
				movTopoo += movOffset * deltaTime;
			}

		}

		if (mainWindow.getavanzaBomba()) {
			if (mueveBombaz > 0.0f)
			{
				mueveBombaz += movOffset * deltaTime;
			}
		}
	

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 posInicial(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//Este se hace dentro del while
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 20.0f));     //escalamos el piso por 30 (ahora mide 600 unidades)
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pastoTexture.UseTexture();

		meshList[0]->RenderMesh();
	
	
		// Juego de daRdos
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(273.50f, -2.0f, -27.0f));
			model = glm::scale(model, glm::vec3(2.25f, 2.25f, 2.25f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Carpa_M.RenderModel();

			//Tablero con globos
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, 5.50f, -7.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Tablero_M.RenderModel();
			model = glm::translate(model, glm::vec3(-5.0f, 2.0f, 0.10f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			//Segunda fila de globos
			model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			//Tercera lifa
			model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();

			//Cuarta 
			model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();;
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			//quinta 
			model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboC_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboV_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboM_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboN_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboA_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			GloboR_M.RenderModel();
			model = modelaux;
			//escalera con peluches
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, 1.540f, 5.30f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Escalera_M.RenderModel();
			model = glm::translate(model, glm::vec3(0.0f, 1.280f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Peluche_M.RenderModel();
			model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Dardo_M.RenderModel();
			model = modelaux;
		}
		//BOLOS 
	{
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, 21.40f, 180.0f));
		model = glm::scale(model, glm::vec3(4.05f, 4.05f, 4.05f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pantalla_M.RenderModel();
		//Pista de bolos
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.0f, -5.50f, 10.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Linea_M.RenderModel();
		model = modelaux;
		modelaux = model;
		model = glm::translate(model, glm::vec3(4.20f, -5.50f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bomba_M.RenderModel();
		model = modelaux;
		modelaux = model;
		model = glm::translate(model, glm::vec3(-4.20f, -5.50f, 18.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (mueveBombaz) * 5.0));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BombaS_M.RenderModel();
		model = modelaux;
		//bolos 
		modelaux = model;
		model = glm::translate(model, glm::vec3(-5.60f, -4.9f, 1.60f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();

		model = glm::translate(model, glm::vec3(-2.50f, -0.0f, 0.50f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(-1.50f, -0.0f, 0.50f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(-0.50f, -0.0f, 0.50f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = modelaux;
		modelaux = model;
		model = glm::translate(model, glm::vec3(2.50f, -4.9f, 1.60f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();

		model = glm::translate(model, glm::vec3(-2.50f, -0.0f, 0.50f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(-1.50f, -0.0f, 0.50f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
		model = glm::translate(model, glm::vec3(-0.50f, -0.0f, 0.50f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pino_M.RenderModel();
	}

		//JAULA DE BATEO
			{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(80.0f, 10.650f, -145.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				Reja_M.RenderModel();
				modelaux = model;
				model = glm::translate(model, glm::vec3(0.0f, -12.70f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Campo_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(37.0f, 2.0f, 0.0f));
				model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Reflector_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-37.0f, 2.30f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Reflector_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-9.50f, -11.90f, 24.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Cofre_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(9.50f, -11.90f, 24.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Caja_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-3.0f, -11.70f, 24.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Espada_M.RenderModel();	model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(0.0f, -11.70f, 24.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Bola_M.RenderModel();

			}

		//HOCEEEEES
			{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-102.0f, -2.40f, 156.0f));
				model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				CarpaH_M.RenderModel();

				modelaux = model;
				model = glm::translate(model, glm::vec3(12.91f, 16.078f, -17.016f + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BlancoD_M.RenderModel();
				model = glm::translate(model, glm::vec3(-25.50f, 0.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BlancoI_M.RenderModel();
				model = modelaux;

				modelaux = model;
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Banda_M.RenderModel();
				model = modelaux;
				//oces del lado izquierdo 
				modelaux = model;
				model = glm::translate(model, glm::vec3(-23.691f, 11.312f, 15.504 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-23.691f, 11.312f, 8.452 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-23.691f, 11.312f, 1.1633 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-23.691f, 11.312f, -5.494 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				// oc s lado derecho
				modelaux = model;
				model = glm::translate(model, glm::vec3(23.656f, 11.312f, 15.504 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(23.656f, 11.312f, 8.452 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(23.656f, 11.312f, 1.1633 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(23.656f, 11.312f, -5.494 + 1.95f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Hoz_M.RenderModel();
				model = modelaux;
			}

	
	//DADOOOOOS
	{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(30.0f, -1.80f, 156.0f));
				model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				CarpaD_M.RenderModel();
			
				modelaux = model;
				model = glm::translate(model, glm::vec3(-6.75f, 4.304f, 2.008f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MesaD_M.RenderModel();
				model = modelaux;

				modelaux = model;
				model = glm::translate(model, glm::vec3(-6.979f, 7.912f, -7.926f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Letrero1_M.RenderModel();
				model = modelaux;

				modelaux = model;
				model = glm::translate(model, glm::vec3(8.825f, 6.124f, -4.528f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Letrero2_M.RenderModel();
				model = modelaux;

				modelaux = model;
				model = glm::translate(model, glm::vec3(8.904f, 2.179f, 2.815f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				RepisaR_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(8.526f, 3.183f, 3.698f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Peluche_M.RenderModel();
				model = modelaux;

				modelaux = model;
				model = glm::translate(model, glm::vec3(-6.75f, 7.304f, 2.008f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Dado_M.RenderModel();
				model = modelaux;		
			
			}

	
	// Juego de Golpea al Topo
	{
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, -1.5f, -150.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JuegoTopos_M.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(2.823f, 10.003f, 1.054f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo1_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.001f, 9.703f, 1.089f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo2_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-2.875f, 9.965f, 1.161f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo3_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(2.907f, 9.985f, -2.427f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo4_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.021f, 10.023f, -2.478f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo5_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-2.87f, 9.76f, -2.519f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo6_M.RenderModel();
		model = modelaux;

		model = glm::translate(model, glm::vec3(0.107f, 10.395f, -0.722f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mazo_M.RenderModel();
	}
	
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-85.0f, -1.5f, -165.0f));
		model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topos_M.RenderModel();  	modelaux = model;
		model = glm::translate(model, glm::vec3(0.107f, 10.395f, -0.722f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mazo_M.RenderModel();  model = modelaux;
		model = glm::translate(model, glm::vec3(-15.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topos_M.RenderModel();modelaux = model;
		model = glm::translate(model, glm::vec3(0.107f, 10.395f, -0.722f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mazo_M.RenderModel();  model = modelaux;
		
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topos_M.RenderModel();modelaux = model;
		model = glm::translate(model, glm::vec3(0.107f, 10.395f, -0.722f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mazo_M.RenderModel();  model = modelaux;
		
	{
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-105.0f, -1.5f, -150.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JuegoTopos_M.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(2.823f, 10.003f, 1.054f));
		model = glm::translate(model, glm::vec3(0.0f, (movTopo) * 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo1_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.001f, 9.703f, 1.089f));
		model = glm::translate(model, glm::vec3(0.0f, (movTopoo) * 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo2_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-2.875f, 9.965f, 1.161f));
		model = glm::translate(model, glm::vec3(0.0f, (movTopo) * 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo3_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(2.907f, 9.985f, -2.427f));
		model = glm::translate(model, glm::vec3(0.0f, (movTopoo) * 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo4_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.021f, 10.023f, -2.478f));
		model = glm::translate(model, glm::vec3(0.0f, (movTopo) * 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo5_M.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-2.87f, 9.76f, -2.519f));
		model = glm::translate(model, glm::vec3(0.0f, (movTopoo) * 5.0f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Topo6_M.RenderModel();
		model = modelaux;

	}
	
	//CLARENCE
	{
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-98.0f, -1.90f, -150.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ClarenceC_M.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.096f, 0.5810f, -0.022f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ClarencePD_M.RenderModel();
		model = modelaux;
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.2830f, 0.530f, -0.114f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ClarencePI_M.RenderModel();
		model = modelaux;
		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.2870f, 1.5290f, -0.066f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ClarenceBD_M.RenderModel();
		model = modelaux;
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.4640f, 1.529f, -0.066f));
		model = glm::rotate(model, -36 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ClarenceBI_M.RenderModel();
		model = modelaux;
	}
	
		// LINK
		{
			// ---------- LINK ----------

		//Cuerpo
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(13.0f, 3.25f, -22.0f));
			model = glm::translate(model, glm::vec3(-0.0f + mainWindow.getmueveLink(), 2.0f, -3.0f));
			model = glm::translate(model, glm::vec3(-0.0f, 0.0f, 0.0f + mainWindow.getmueveLinkz()));
			//model = glm::translate(model, glm::vec3(0.0f, 3.85f, 0.0f));
			model = glm::scale(model, glm::vec3(2.2f, 2.2f, 2.2f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(mainWindow.getrotacionPersonajeY()), glm::vec3(0.0f, 1.0f, 0.0f));
			posInicial = model;
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			CuerpoLink_M.RenderModel();
			//Pierna derecha
			model = modelaux;
			model = glm::translate(model, glm::vec3(-0.437f, -0.93f, -0.045f));
			model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(1.0f, 0.0f, 0.0f));			
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			PiernaDerLink_M.RenderModel();
			//Pierna izquierda
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.437f, -0.93f, -0.045f));
			model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			PiernaIzqLink_M.RenderModel();
			//Vaina
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.7f));
			model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			VainaLink_M.RenderModel();
			//Brazo derecho
			model = modelaux;
			model = glm::translate(model, glm::vec3(-0.78f, 0.85f, -0.13f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			BrazoDerLink_M.RenderModel();
			//Brazo izquierdo
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.8f, 0.865f, -0.13f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			BrazoIzqLink_M.RenderModel();
			//Cabeza
			model = posInicial;
			model = glm::translate(model, glm::vec3(0.0f, 1.02f, -0.12f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			modelaux = model;
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			CabezaLink_M.RenderModel();
			glDisable(GL_BLEND);
			//Sombrero
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.0f, 1.4f, -0.02f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_link.UseMaterial(uniformSpecularIntensity, uniformShininess);
			SombreroLink_M.RenderModel();
		}
		// Micheladas
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-220.0f, -2.5f, 122.0f));
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Miche_M.RenderModel();
		}
		
		//Baño 1
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-9.0f, -1.850f, 110.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();

			//baño 2
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-145.0f, -1.850f, 100.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();

			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();

			//baño 3
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(200.0f, -1.850f, 100.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();

			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();

			//baño 4
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(161.0f, -1.850f, -110.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();

			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
			//baño 5
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-8.0f, -1.850f, -150.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();

			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
			//baño6
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(130.0f, -1.850f, -10.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();

			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			//model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
			//baño 7
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-130.0f, -1.850f, -40.0f));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();

			model = glm::translate(model, glm::vec3(-11.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}
		//Faros
		{
			model = glm::mat4(1.0);//1
			model = glm::translate(model, glm::vec3(-165.0f, -1.0f, -126.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//2
			model = glm::translate(model, glm::vec3(-120.0f, -1.0f, -125.50f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//3
			model = glm::translate(model, glm::vec3(-50.0f, -1.0f, -145.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();//	4			
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(30.0f, -1.0f, -125.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//5
			model = glm::translate(model, glm::vec3(128.0f, -1.0f, -118.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//6
			model = glm::translate(model, glm::vec3(185.0f, -1.0f, -140.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//7
			model = glm::translate(model, glm::vec3(225.0f, -1.0f, -80.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//8
			model = glm::translate(model, glm::vec3(-240.0f, -1.0f, -38.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();	//9			
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-200.0f, -2.80f, -38.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0); //10
			model = glm::translate(model, glm::vec3(-110.0f, -1.0f, -15.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0); //11
			model = glm::translate(model, glm::vec3(-75.0f, -1.0f, -50.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//12
			model = glm::translate(model, glm::vec3(-25.0f, -1.0f, -15.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0); //13			
			model = glm::translate(model, glm::vec3(25.0f, -1.0f, -35.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//14
			model = glm::translate(model, glm::vec3(75.0f, -1.0f, -15.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//15
			model = glm::translate(model, glm::vec3(125.0f, -1.0f, -35.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0); //16
			model = glm::translate(model, glm::vec3(187.0f, -1.0f, -15.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();

			model = glm::mat4(1.0);//17
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(-225.0f, -1.0f, 150.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//18
			model = glm::translate(model, glm::vec3(245.0f, -1.0f, 50.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//19
			model = glm::translate(model, glm::vec3(-185.0f, -1.0f, 85.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//20
			model = glm::translate(model, glm::vec3(-92.0f, -1.0f, 80.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//21
			model = glm::translate(model, glm::vec3(70.0f, -1.0f, 80.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//22

			model = glm::translate(model, glm::vec3(175.0f, -1.0f, 80.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//23
			model = glm::translate(model, glm::vec3(225.0f, -1.0f, 88.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//24
			model = glm::translate(model, glm::vec3(-45.0f, -1.0f, 145.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//25
			model = glm::translate(model, glm::vec3(-15.0f, -1.0f, 145.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//26
			model = glm::translate(model, glm::vec3(245.0f, -1.0f, 145.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
			model = glm::mat4(1.0);//27
			model = glm::translate(model, glm::vec3(20.0f, -1.0f, 40.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Luz_M.RenderModel();
		}
		
	//ARBOLES
	{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(20.0f, -2.7f, -160.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(150.0f, -2.7f, -160.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(275.0f, -2.7f, -140.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-20.0f, -2.7f, -90.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(160.0f, -2.7f, -80.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				//////////////////////////////////////////////////////////////////
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-250.0f, -3.0f, -100.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-250.0f, -2.7f, 50.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-150.0f, -2.7f, 25.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-25.0f, -2.7f, 50.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				modelaux = model;
				model = glm::translate(model, glm::vec3(-0.0f, 1.10f, -18.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Mesa_Banco_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(0.0f, 1.10f, 18.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Mesa_Banco_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(18.0f, 1.10f, 0.0f));
				model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Mesa_Banco_M.RenderModel();
				model = modelaux;
				modelaux = model;
				model = glm::translate(model, glm::vec3(-18.0f, 1.10f, 0.0f));
				model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Mesa_Banco_M.RenderModel();
				model = modelaux;
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(140.0f, -2.7f, 45.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-170.0f, -2.7f, 160.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-170.0f, -2.7f, 160.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(-24.0f, -2.7f, 150.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(284.0f, -2.7f, 130.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Arbol_M.RenderModel();

			}

	//Bancos

	model = glm::mat4(1.0);//1
	model = glm::translate(model, glm::vec3(-125.0f, -3.35f, -145.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//2
	model = glm::translate(model, glm::vec3(200.0f, -3.35f, -145.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//3
	model = glm::translate(model, glm::vec3(223.0f, -3.35f, -110.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	model = glm::rotate(model, -270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//4
	model = glm::translate(model, glm::vec3(242.0f, -3.350f, -85.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//5
	model = glm::translate(model, glm::vec3(8.0f, -3.35f, -37.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//6
	model = glm::translate(model, glm::vec3(108.0f, -3.35f, -37.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//7
	model = glm::translate(model, glm::vec3(-225.0f, -3.35f, 75.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	model = glm::rotate(model, -270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	Banco_M.RenderModel();
	model = glm::mat4(1.0);//8
	model = glm::translate(model, glm::vec3(-65.0f, -3.35f, 120.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	model = glm::mat4(1.0);//9
	model = glm::translate(model, glm::vec3(240.0f, -3.35f, 75.0f));
	model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
	model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();



	
		


		//Jeff
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(190.0f, -1.90f, -92.0f));
			model = glm::scale(model, glm::vec3(20.05f, 20.05f, 20.05f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			JeffC_M.RenderModel();

			modelaux = model;
			model = glm::translate(model, glm::vec3(0.001f, 0.168f, -0.028f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			JeffPD_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-0.023f, 0.168f,- 0.029f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			JeffPI_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-0.031f, 0.3150f, -0.03f));
			model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			JeffBD_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.003f, 0.319f,- 0.026f));
			model = glm::rotate(model, -36 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			JeffBI_M.RenderModel();
			model = modelaux;
		}
		//Sumo
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(30.0f, 0.90f, 0.0f + (movSumo)));
			model = glm::rotate(model, glm::radians(rotaSumo), glm::vec3(0.0f, 1.0f, 0.0f));
			//model = glm::translate(model, glm::vec3(10.0f, 0.90f, -92.0f));
			model = glm::scale(model, glm::vec3(20.05f, 20.05f, 20.05f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SumoC_M.RenderModel();

			modelaux = model;
			model = glm::translate(model, glm::vec3(-0.014f, 0.022f, -0.0f));
			model = glm::rotate(model, 15.0f * sin(angulovaria * 0.1f) * toRadians, glm::vec3(-1.0f, 0.0f, -0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SumoPD_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.02f, 0.022f, -0.0f));
			model = glm::rotate(model, 15.0f * sin(angulovaria * 0.1f + glm::pi<float>()) * toRadians, glm::vec3(-1.0f, 0.0f, -0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SumoPI_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.015f, 0.106f, 0.001f));
			model = glm::rotate(model, 15.0f * sin(angulovaria * 0.1f) * toRadians, glm::vec3(-1.0f, 0.0f, -0.0f));
			model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SumoBI_M.RenderModel();

			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-0.016f, 0.107f, 0.001f));
			model = glm::rotate(model, 15.0f * sin(angulovaria * 0.1f + glm::pi<float>()) * toRadians, glm::vec3(-1.0f, 0.0f, -0.0f));
			model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SumoBD_M.RenderModel();

			model = modelaux;
		}
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-220.0f, -2.15f, -50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gumball_Carro_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 1.08f, 50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gumball_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 4.1f, -50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Teri_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 6.35f, -135.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Penny_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -2.0f, 70.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.8f, 2.8f, 2.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pork_Cassidy_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(180.0f, 2.60f, 50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Darwin_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, 8.35f, -145.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carrie_Krueger_M.RenderModel();

		//Puerta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, -2.0f, -25.0f));
		model = glm::rotate(model, 270.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_M.RenderModel();

		//Letrero
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 13.45f, 1.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letrero_M.RenderModel();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Rotar el texto cada cierto tiempo
		if (now - tiempoUltimaRotacion >= tiempoRotacion) {
			textoActual = RotarTexto(textoActual); // Rota el texto
			tiempoUltimaRotacion = now; // Actualiza el tiempo de la última rotación
		}
		
		// Renderizar el texto rotado
		RenderTextoEstatico(textoActual, glm::vec3(-273.5f, 25.4f, -32.0f), 1.0f,
			uniformModel, uniformTextureOffset);
		

		glDisable(GL_BLEND);
	
	







		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}