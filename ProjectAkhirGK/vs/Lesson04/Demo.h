#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);

	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();

	// Mulai dari sini
	float angle; 
	GLuint VBOTanah, VAOTanah, EBOTanah, txtTanah;
	GLuint VBOTembok, VAOTembok, EBOTembok, txtTembok;
	GLuint VBOPintu, VAOPintu, EBOPintu, txtPintu;
	GLuint VBOLampu, VAOLampu, EBOLampu, txtLampu;
	GLuint VBOKasur, VAOKasur, EBOKasur, txtKasur;
	GLuint VBOSprei, VAOSprei, EBOSprei, txtSprei;
	GLuint VBOMeja, VAOMeja, EBOMeja, txtMeja;
	GLuint VBOAtap, VAOAtap, EBOAtap, txtAtap;
	GLuint VBOSaklar, VAOSaklar, EBOSaklar, txtSaklar;
	GLuint VBOLemari, VAOLemari, EBOLemari, txtLemari;
	GLuint VBOLemariDepan, VAOLemariDepan, EBOLemariDepan, txtLemariDepan;

	void BuildColoredTanah();
	void DrawColoredTanah();
	
	void BuildColoredTembok();
	void DrawColoredTembok();

	void BuildColoredPintu();
	void DrawColoredPintu();

	void BuildColoredLampu();
	void DrawColoredLampu();

	void BuildColoredKasur();
	void DrawColoredKasur();

	void BuildColoredSprei();
	void DrawColoredSprei();

	void BuildColoredMeja();
	void DrawColoredMeja();

	void BuildColoredAtap();
	void DrawColoredAtap();

	void BuildColoredSaklar();
	void DrawColoredSaklar();

	void BuildColoredLemari();
	void DrawColoredLemari();

	void BuildColoredLemariDepan();
	void DrawColoredLemariDepan();
};

