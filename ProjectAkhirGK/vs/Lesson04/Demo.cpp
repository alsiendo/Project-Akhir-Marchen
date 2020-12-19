#include "Demo.h"
Demo::Demo() {
}
Demo::~Demo() {
}

void Demo::Init() {
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredTanah();
	BuildColoredTembok();
	BuildColoredPintu();
	BuildColoredLampu();
	BuildColoredKasur();
	BuildColoredSprei();
	BuildColoredMeja();
	BuildColoredAtap();
	BuildColoredSaklar();
	BuildColoredLemari();
	BuildColoredLemariDepan();

	InitCamera();
}
void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAOTanah);
	glDeleteBuffers(1, &VBOTanah);
	glDeleteBuffers(1, &EBOTanah);
	glDeleteVertexArrays(1, &VAOTembok);
	glDeleteBuffers(1, &VBOTembok);
	glDeleteBuffers(1, &EBOTembok);
	glDeleteVertexArrays(1, &VAOPintu);
	glDeleteBuffers(1, &VBOPintu);
	glDeleteBuffers(1, &EBOPintu);
	glDeleteVertexArrays(1, &VAOLampu);
	glDeleteBuffers(1, &VBOLampu);
	glDeleteBuffers(1, &EBOLampu);
	glDeleteVertexArrays(1, &VAOKasur);
	glDeleteBuffers(1, &VBOKasur);
	glDeleteBuffers(1, &EBOKasur);
	glDeleteVertexArrays(1, &VAOSprei);
	glDeleteBuffers(1, &VBOSprei);
	glDeleteBuffers(1, &EBOSprei);
	glDeleteVertexArrays(1, &VAOMeja);
	glDeleteBuffers(1, &VBOMeja);
	glDeleteBuffers(1, &EBOMeja);
	glDeleteVertexArrays(1, &VAOAtap);
	glDeleteBuffers(1, &VBOAtap);
	glDeleteBuffers(1, &EBOAtap);
	glDeleteVertexArrays(1, &VAOSaklar);
	glDeleteBuffers(1, &VBOSaklar);
	glDeleteBuffers(1, &EBOSaklar);
	glDeleteVertexArrays(1, &VAOLemari);
	glDeleteBuffers(1, &VBOLemari);
	glDeleteBuffers(1, &EBOLemari);
	glDeleteVertexArrays(1, &VAOLemariDepan);
	glDeleteBuffers(1, &VBOLemariDepan);
	glDeleteBuffers(1, &EBOLemariDepan);
}

void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}
void Demo::Update(double deltaTime) {
}
void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set BG to black

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Projection
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Camera
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Lighting
	GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, "lightPos");
	
	glUniform3f(lightPosLoc, 2, 7, 10);
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 0, 0);
	GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	DrawColoredTanah();
	DrawColoredTembok();
	DrawColoredPintu();
	DrawColoredLampu();
	DrawColoredKasur();
	DrawColoredSprei();
	DrawColoredMeja();
	DrawColoredAtap();
	DrawColoredSaklar();
	DrawColoredLemari();
	DrawColoredLemariDepan();


	glDisable(GL_DEPTH_TEST);
}

// ---------- Objek Benda ----------
void Demo::BuildColoredTembok() {
	// -------- Loading the Image --------  
	glGenTextures(1, &txtTembok);
	glBindTexture(GL_TEXTURE_2D, txtTembok);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Creamy.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image -------- 

	// -------- Coordinates -------- 
	float vertices[] = {
		// format position, tex coords, Normal
		// Kanan
		8.0,   7.5,  8.0,		0, 0,  -1.0f, 0.0f, 0.0f,	// 0
		8.0,   7.5,  -8.0,		1, 0,  -1.0f, 0.0f, 0.0f,	// 1
		8.0,   -0.5, -8.0,		1, 1,  -1.0f, 0.0f, 0.0f,	// 2
		8.0,   -0.5,  8.0,		0, 1,  -1.0f, 0.0f, 0.0f,	// 3

		// Belakang
		-8.0, -0.5, -8.0,		0, 0,	0.0f, 0.0f, -1.0f,	// 4 
		8.0,  -0.5, -8.0,		1, 0,	0.0f, 0.0f, -1.0f,	// 5
		8.0,   7.5, -8.0,		1, 1,	0.0f, 0.0f, -1.0f,	// 6
		-8.0,  7.5, -8.0,		0, 1,	0.0f, 0.0f, -1.0f,	// 7

		// Kiri
		-8.0, -0.5, -8.0,		0, 0,	1.0f, 0.0f, 0.0f,	// 8
		-8.0, -0.5,  8.0,		1, 0,	1.0f, 0.0f, 0.0f,	// 9
		-8.0,  7.5,  8.0,		1, 1,	1.0f, 0.0f, 0.0f,	// 10
		-8.0,  7.5, -8.0,		0, 1,	1.0f, 0.0f, 0.0f,	// 11
	};
	// End -------- Coordinates -------- 

	// -------- Coordinates -------- 
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // right
		4,  6,  5,  4,  7,  6,   // back
		8, 10,	9,	8,	11, 10,  // left
	};

	glGenVertexArrays(1, &VAOTembok);
	glGenBuffers(1, &VBOTembok);
	glGenBuffers(1, &EBOTembok);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOTembok);

	glBindBuffer(GL_ARRAY_BUFFER, VBOTembok);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOTembok);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredTembok() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, txtTembok);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, txtTembok);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 0);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOTembok); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTanah() {
	// -------- Loading the Image -------- 
	glGenTextures(1, &txtTanah);
	glBindTexture(GL_TEXTURE_2D, txtTanah);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("S.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image --------

	// -------- Coordinates --------
	GLfloat vertices[] = { // format position, tex coords, Normal
		-8.0, -0.5, -8.0,	0, 0,	0.5f,  0.0f,  0.0f,
		 8.0, -0.5, -8.0,	8, 0,	0.5f,  0.0f,  0.0f,
		 8.0, -0.5,  8.0,	8, 8,	0.5f,  0.0f,  0.0f,
		-8.0, -0.5,  8.0,	0, 8,	0.5f,  0.0f,  0.0f,
	};
	// End -------- Coordinates --------

	// -------- Indices --------
	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAOTanah);
	glGenBuffers(1, &VBOTanah);
	glGenBuffers(1, &EBOTanah);

	glBindVertexArray(VAOTanah);

	glBindBuffer(GL_ARRAY_BUFFER, VBOTanah);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOTanah);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	// End -------- Indices --------
}
void Demo::DrawColoredTanah() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, txtTanah);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, txtTanah);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOTanah); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPintu() {
	// -------- Loading the Image -------- 
	glGenTextures(1, &txtPintu);
	glBindTexture(GL_TEXTURE_2D, txtPintu);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Pintu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image --------

	// -------- Coordinates --------
	GLfloat vertices[] = {// format position, tex coords, Normal
		// front
		-0.5, -0.5, 0.2, 0, 0,		0.0f,  0.0f,  1.0f,// 0
		0.5, -0.5, 0.2, 1, 0,		0.5f,  0.0f,  1.0f,// 1
		0.5,  1.0, 0.2, 1, 1,		0.5f,  0.0f,  1.0f,// 2
		-0.5,  1.0, 0.2, 0, 1,		0.5f,  0.0f,  1.0f,// 3

		// right
		0.5,  1.0, 0.2, 0, 0,		1.0f,  0.0f,  0.0f,// 4
		0.5,  1.0, -0.2, 1, 0,		1.0f,  0.0f,  0.0f,// 5
		0.5, -0.5, -0.2, 1, 1,		1.0f,  0.0f,  0.0f,// 6
		0.5, -0.5,  0.2, 0, 1,		1.0f,  0.0f,  0.0f,// 7

		// back
		-0.5, -0.5, -0.2, 0, 0,		0.0f,  0.0f,  -1.0f,// 8 
		0.5,  -0.5, -0.2, 1, 0,		0.0f,  0.0f,  -1.0f,// 9
		0.5,   1.0, -0.2, 1, 1,		0.0f,  0.0f,  -1.0f,// 10
		-0.5,  1.0, -0.2, 0, 1,		0.0f,  0.0f,  -1.0f,// 11

		// left
		-0.5, -0.5, -0.2, 0, 0,		-1.0f,  0.0f,  0.0f,// 12
		-0.5, -0.5,  0.2, 1, 0,		-1.0f,  0.0f,  0.0f,// 13
		-0.5,  1.0,  0.2, 1, 1,		-1.0f,  0.0f,  0.0f,// 14
		-0.5,  1.0, -0.2, 0, 1,		-1.0f,  0.0f,  0.0f,// 15

		// upper
		0.5, 1.0,  0.2, 0, 0,		0.0f,  1.0f,  0.0f,// 16
		-0.5, 1.0,  0.2, 1, 0,		0.0f,  1.0f,  0.0f,// 17
		-0.5, 1.0, -0.2, 1, 1,		0.0f,  1.0f,  0.0f,// 18
		0.5, 1.0, -0.2, 0, 1,		0.0f,  1.0f,  0.0f,// 19

		// bottom
		-0.5, -0.5, -0.2, 0, 0,		0.0f,  -1.0f,  0.0f,// 20
		0.5, -0.5, -0.2, 1, 0,		0.0f,  -1.0f,  0.0f,// 21
		0.5, -0.5,  0.2, 1, 1,		0.0f,  -1.0f,  0.0f,// 22
		-0.5, -0.5,  0.2, 0, 1,		0.0f,  -1.0f,  0.0f,// 23
	};
	// End -------- Coordinates --------

	// -------- Indices --------
	GLuint indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAOPintu);
	glGenBuffers(1, &VBOPintu);
	glGenBuffers(1, &EBOPintu);

	glBindVertexArray(VAOPintu);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPintu);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPintu);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// End -------- Indices --------
}
void Demo::DrawColoredPintu() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, txtPintu);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, txtPintu);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 2);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOPintu); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 1.45, -7.5));
	model = glm::scale(model, glm::vec3(4, 4, 4));
	angle = -1.58f;
	model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.8, 0, -2.19));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLampu() {
	// -------- Loading the Image -------- 
	glGenTextures(1, &txtLampu);
	glBindTexture(GL_TEXTURE_2D, txtLampu);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Lamp.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image --------

	// -------- Coordinates --------
	GLfloat vertices[] = {
		// format position, tex coords
		// front
		-0.5, 0.01, 0.1, 0, 0,	0.0f,  0.0f,  1.0f,  // 0
		0.5, 0.01, 0.1, 1, 0,	0.0f,  0.0f,  1.0f,   // 1
		0.5,  0.05, 0.1, 1, 1,	0.0f,  0.0f,  1.0f,   // 2
		-0.5,  0.05, 0.1, 0, 1,	0.0f,  0.0f,  1.0f,  // 3

		// right
		0.5,  0.05, 0.1, 0, 0,  1.0f,  0.0f,  0.0f,// 4
		0.5,  0.05, 0.05, 1, 0,  1.0f,  0.0f,  0.0f,// 5
		0.5, 0.01, 0.05, 1, 1,  1.0f,  0.0f,  0.0f,// 6
		0.5, 0.01,  0.1, 0, 1,  1.0f,  0.0f,  0.0f,// 7

		// back
		-0.5,  0.01, 0.05, 0, 0, 0.0f,  0.0f,  -1.0f,// 8 
		0.5,  0.01, 0.05, 1, 0, 0.0f,  0.0f,  -1.0f,// 9
		0.5,  0.05, 0.05, 1, 1, 0.0f,  0.0f,  -1.0f,// 10
		-0.5,  0.05, 0.05, 0, 1, 0.0f,  0.0f,  -1.0f,// 11

		// left
		-0.5, 0.01, 0.05, 0, 0, -1.0f,  0.0f,  0.0f,// 12
		-0.5, 0.01,  0.1, 1, 0, -1.0f,  0.0f,  0.0f,// 13
		-0.5,  0.05,  0.1, 1, 1, -1.0f,  0.0f,  0.0f,// 14
		-0.5,  0.05, 0.05, 0, 1, -1.0f,  0.0f,  0.0f,// 15

		// upper
		0.5, 0.05,  0.1, 0, 0,   0.0f,  1.0f,  0.0f,// 16
		-0.5, 0.05,  0.1, 1, 0,  0.0f,  1.0f,  0.0f,// 17
		-0.5, 0.05, 0.05, 1, 1,  0.0f,  1.0f,  0.0f,// 18
		0.5, 0.05, 0.05, 0, 1,   0.0f,  1.0f,  0.0f,// 19

		// bottom
		-0.5, 0.01, 0.05, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		0.5, 0.01, 0.05, 1, 0,  0.0f,  -1.0f,  0.0f,// 21
		0.5, 0.01,  0.1, 1, 1,  0.0f,  -1.0f,  0.0f,// 22
		-0.5, 0.01,  0.1, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
	};
	// End -------- Coordinates --------

	// -------- Indices --------
	GLuint indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom

	};

	glGenVertexArrays(1, &VAOLampu);
	glGenBuffers(1, &VBOLampu);
	glGenBuffers(1, &EBOLampu);

	glBindVertexArray(VAOLampu);

	glBindBuffer(GL_ARRAY_BUFFER, VBOLampu);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOLampu);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredLampu() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, txtLampu);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 3);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, txtLampu);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 3);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOLampu); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(5, 5, 5));
	model = glm::translate(model, glm::vec3(0, 1.42, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredKasur() {
	// -------- Loading the Image -------- 
	glGenTextures(1, &txtKasur);
	glBindTexture(GL_TEXTURE_2D, txtKasur);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Kasur2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image --------

	// -------- Coordinates --------
	GLfloat vertices[] = {
		// format position, tex coords
		// bagian A
		// front
		-1.0, -0.25, 0.5, 0, 0,		0.0f,  0.0f,  1.0f,// 0
		-0.5, -0.25, 0.5, 1, 0,		0.0f,  0.0f,  1.0f,// 1
		-0.5,  1.5, 0.5, 1, 1,		0.0f,  0.0f,  1.0f,// 2
		-1.0,  1.5, 0.5, 0, 1,		0.0f,  0.0f,  1.0f,// 3

		// right
		-0.5,  1.5, 0.5, 0, 0,  1.0f,  0.0f,  0.0f,// 4
		-0.5,  1.5, -1.0, 1, 0,  1.0f,  0.0f,  0.0f,// 5
		-0.5, -0.25, -1.0, 1, 1,  1.0f,  0.0f,  0.0f,// 6
		-0.5, -0.25,  0.5, 0, 1,  1.0f,  0.0f,  0.0f,// 7

		// back
		-1.0, -0.25, -1.0, 0, 0,	0.0f,  0.0f,  -1.0f,// 8 
		-0.5,  -0.25, -1.0, 1, 0,	0.0f,  0.0f,  -1.0f,// 9
		-0.5,   1.5, -1.0, 1, 1,	0.0f,  0.0f,  -1.0f,// 10
		-1.0,  1.5, -1.0, 0, 1,		0.0f,  0.0f,  -1.0f,// 11

		// left
		-1.0, -0.25, -1.0, 0, 0,	-1.0f,  0.0f,  0.0f,// 12
		-1.0, -0.25,  0.5, 1, 0,	-1.0f,  0.0f,  0.0f,// 13
		-1.0,  1.5,  0.5, 1, 1,		-1.0f,  0.0f,  0.0f,// 14
		-1.0,  1.5, -1.0, 0, 1,		-1.0f,  0.0f,  0.0f,// 15

		// upper
		-0.5, 1.5,  0.5, 0, 0,   0.0f,  1.0f,  0.0f,// 16
		-1.0, 1.5,  0.5, 1, 0,  0.0f,  1.0f,  0.0f,// 17
		-1.0, 1.5, -1.0, 1, 1,  0.0f,  1.0f,  0.0f,// 18
		-0.5, 1.5, -1.0, 0, 1,   0.0f,  1.0f,  0.0f,// 19

		// bottom
		-1.0, -0.25, -1.0, 0, 0,	0.0f,  -1.0f,  0.0f,// 20
		-0.5, -0.25, -1.0, 1, 0,	0.0f,  -1.0f,  0.0f,// 21
		-0.5, -0.25,  0.5, 1, 1,	0.0f,  -1.0f,  0.0f,// 22
		-1.0, -0.25,  0.5, 0, 1,	0.0f,  -1.0f,  0.0f,// 23

		// bagian B
		// front
		-0.5, -0.25, 0.5, 0, 0,		0.0f,  0.0f,  1.0f,// 24 - 0
		2.0, -0.25, 0.5, 1, 0,   0.0f,  0.0f,  1.0f,// 25 - 1
		2.0,  0.2, 0.5, 1, 1,   0.0f,  0.0f,  1.0f,// 26 - 2
		-0.5,  0.2, 0.5, 0, 1,  0.0f,  0.0f,  1.0f,// 27 - 3

		// right
		2.0,  0.2, 0.5, 0, 0,  1.0f,  0.0f,  1.0f,// 28 - 4
		2.0,  0.2, -1.0, 1, 0,  1.0f,  0.0f,  1.0f,// 29 - 5
		2.0, -0.25, -1.0, 1, 1,  1.0f,  0.0f,  1.0f,// 30 - 6 
		2.0, -0.25,  0.5, 0, 1,  1.0f,  0.0f,  1.0f,// 31 - 7

		// back
		-0.5, -0.25, -1.0, 0, 0, 0.0f,  0.0f,  -1.0f,// 32 - 8
		2.0,  -0.25, -1.0, 1, 0, 0.0f,  0.0f,  -1.0f,// 33 - 9
		2.0,   0.2, -1.0, 1, 1, 0.0f,  0.0f,  -1.0f,// 34 - 10
		-0.5,  0.2, -1.0, 0, 1, 0.0f,  0.0f,  -1.0f,// 35 - 11

		// left
		-0.5, -0.25, -1.0, 0, 0,	-1.0f,  0.0f,  0.0f,// 36 - 12
		-0.5, -0.25,  0.5, 1, 0,	-1.0f,  0.0f,  0.0f,// 37 - 13
		-0.5,  0.2,  0.5, 1, 1,		-1.0f,  0.0f,  0.0f,// 38 - 14
		-0.5,  0.2, -1.0, 0, 1,		-1.0f,  0.0f,  0.0f,// 39 - 15

		// upper
		2.0, 0.2,  0.5, 0, 0,   0.0f,  1.0f,  0.0f,// 40 - 16
		-0.5, 0.2,  0.5, 1, 0,  0.0f,  1.0f,  0.0f,// 41 - 17
		-0.5, 0.2, -1.0, 1, 1,  0.0f,  1.0f,  0.0f,// 42 - 18
		2.0, 0.2, -1.0, 0, 1,   0.0f,  1.0f,  0.0f,// 43 - 19

		// bottom
		-0.5, -0.25, -1.0, 0, 0,	0.0f,  -1.0f,  0.0f,// 44 - 20
		2.0, -0.25, -1.0, 1, 0,		0.0f,  -1.0f,  0.0f,// 45 - 21
		2.0, -0.25,  0.5, 1, 1,		0.0f,  -1.0f,  0.0f,// 46 - 22
		-0.5, -0.25,  0.5, 0, 1,	0.0f,  -1.0f,  0.0f,// 47 - 23
	};
	// End -------- Coordinates --------

	// -------- Indices --------
	GLuint indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom
		24,  25,  26, 24, 26, 27,   // front
		28,  29,  30, 28, 30, 31,   // right
		32,  33,  34, 32, 34, 35,  // back
		36, 38, 37, 36, 39, 38,  // left
		40, 42, 41, 40, 43, 42,  // upper
		44, 46, 45, 44, 47, 46   // bottom

	};

	glGenVertexArrays(1, &VAOKasur);
	glGenBuffers(1, &VBOKasur);
	glGenBuffers(1, &EBOKasur);

	glBindVertexArray(VAOKasur);

	glBindBuffer(GL_ARRAY_BUFFER, VBOKasur);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOKasur);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawColoredKasur(){
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, txtKasur);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 4);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, txtKasur);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 4);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOKasur); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(2.4, 2.4, 2.4));
	angle = -1.58f; model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-2.3, 0.05, 2.82));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredSprei() {
	// -------- Loading the Image -------- 
	glGenTextures(1, &txtSprei);
	glBindTexture(GL_TEXTURE_2D, txtSprei);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("stoff_0001_c.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image --------

	// -------- Coordinates --------
	GLfloat vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.1, 0.5, 0, 0,  0.0f,  0.0f,  1.0f,// 0
		2.0, -0.1, 0.5, 1, 0,   0.0f,  0.0f,  1.0f,// 1
		2.0,  0.1, 0.5, 1, 1,   0.0f,  0.0f,  1.0f,// 2
		-0.5,  0.1, 0.5, 0, 1,  0.0f,  0.0f,  1.0f,// 3

		// right
		2.0,  0.1, 0.5, 0, 0,  1.0f,  0.0f,  0.0f,// 4
		2.0,  0.1, -1.0, 1, 0,  1.0f,  0.0f,  0.0f,// 5
		2.0, -0.1, -1.0, 1, 1,  1.0f,  0.0f,  0.0f,// 6 
		2.0, -0.1,  0.5, 0, 1,  1.0f,  0.0f,  0.0f,// 7

		// back
		-0.5, -0.1, -1.0, 0, 0, 0.0f,  0.0f,  -1.0f,// 8
		2.0,  -0.1, -1.0, 1, 0, 0.0f,  0.0f,  -1.0f,// 9
		2.0,   0.1, -1.0, 1, 1, 0.0f,  0.0f,  -1.0f,// 10
		-0.5,  0.1, -1.0, 0, 1, 0.0f,  0.0f,  -1.0f,// 11

		// left
		-0.5, -0.1, -1.0, 0, 0, -1.0f,  0.0f,  0.0f,// 12
		-0.5, -0.1,  0.5, 1, 0, -1.0f,  0.0f,  0.0f,// 13
		-0.5,  0.1,  0.5, 1, 1, -1.0f,  0.0f,  0.0f,// 14
		-0.5,  0.1, -1.0, 0, 1, -1.0f,  0.0f,  0.0f,// 15

		// upper
		2.0, 0.1,  0.5, 0, 0,   0.0f,  1.0f,  0.0f,// 16
		-0.5, 0.1,  0.5, 1, 0,  0.0f,  1.0f,  0.0f,// 17
		-0.5, 0.1, -1.0, 1, 1,  0.0f,  1.0f,  0.0f,// 18
		2.0, 0.1, -1.0, 0, 1,   0.0f,  1.0f,  0.0f,// 19

		// bottom
		-0.5, -0.1, -1.0, 0, 0, 0.0f,  -1.0f,  0.0f,// 20
		2.0, -0.1, -1.0, 1, 0,  0.0f,  -1.0f,  0.0f,// 21
		2.0, -0.1,  0.5, 1, 1,  0.0f,  -1.0f,  0.0f,// 22
		-0.5, -0.1,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f,// 23
	};
	// End -------- Coordinates --------

	// -------- Indices --------
	GLuint indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom

	};

	glGenVertexArrays(1, &VAOSprei);
	glGenBuffers(1, &VBOSprei);
	glGenBuffers(1, &EBOSprei);

	glBindVertexArray(VAOSprei);

	glBindBuffer(GL_ARRAY_BUFFER, VBOSprei);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSprei);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawColoredSprei() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, txtSprei);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 5);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, txtSprei);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 5);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOSprei); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(2.4, 2.4, 2.4));
	angle = -1.58f; model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-2.3, 0.33, 2.82));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredMeja() {
	// -------- Loading the Image -------- 
	glGenTextures(1, &txtMeja);
	glBindTexture(GL_TEXTURE_2D, txtMeja);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image --------

	// -------- Coordinates --------
	GLfloat vertices[] = {
		// format position, tex coords, normal

		-0.5f,  0.5f, 0.5f, 0 ,0, 1.0f, 0.0f, 0.0f, // front top left 0
		0.5f, 0.5f, 0.5f,  1, 0, 1.0f, 0.0f, 0.0f,  // front top right 1
		0.5f, 0.5f, -0.5f, 1, 1, 1.0f, 0.0f, 0.0f,  // back top right 2
		-0.5f,  0.5f, -0.5f, 0, 1, 1.0f, 0.0f, 0.0f, // back top left 3 

		-0.5f, 0.4f, 0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // front bottom left 4
		0.5f, 0.4f, 0.5f,  1, 0, 0.0f, 0.0f, 1.0f,// front bottom right 5
		0.5f, 0.4f, -0.5f, 1, 1, 0.0f, 0.0f, 1.0f,// back bottom right 6
		-0.5f, 0.4f, -0.5f, 0, 1, 0.0f, 0.0f, 1.0f,// back bottom left 7

		//kaki kiri depan
		-0.5f, 0.1f, 0.5f, 0, 0, 1.0f, 0.0f, 0.0f, // 8
		-0.4f, 0.1f, 0.5f,  1, 0, 1.0f, 0.0f, 0.0f, // 9
		-0.4f, 0.1f, 0.4f,  1, 1, 1.0f, 0.0f, 0.0f, // 10
		-0.5f, 0.1f, 0.4f, 0, 1, 1.0f, 0.0f, 0.0f, // 11

		-0.5f, 0.4f, 0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // 12
		-0.4f, 0.4f, 0.5f,  1, 0, 0.0f, 0.0f, 1.0f, // 13
		-0.4f, 0.4f, 0.4f,  1, 1, 0.0f, 0.0f, 1.0f, // 14
		-0.5f, 0.4f, 0.4f, 0, 1, 0.0f, 0.0f, 1.0f, // 15

		//kaki kanan depan
		0.5f, 0.1f, 0.5f, 0, 0, 1.0f, 0.0f, 0.0f, // 16
		0.4f, 0.1f, 0.5f,  1, 0, 1.0f, 0.0f, 0.0f, // 17
		0.4f, 0.1f, 0.4f,  1, 1, 1.0f, 0.0f, 0.0f, // 18
		0.5f, 0.1f, 0.4f, 0, 1, 1.0f, 0.0f, 0.0f, // 19

		0.5f, 0.4f, 0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // 20
		0.4f, 0.4f, 0.5f,  1, 0, 0.0f, 0.0f, 1.0f, // 21
		0.4f, 0.4f, 0.4f,  1, 1, 0.0f, 0.0f, 1.0f, // 22
		0.5f, 0.4f, 0.4f, 0, 1, 0.0f, 0.0f, 1.0f, // 23

		//kaki kiri belakang
		-0.5f, 0.1f, -0.5f, 0, 0, 1.0f, 0.0f, 0.0f, // 24
		-0.4f, 0.1f, -0.5f,  1, 0, 1.0f, 0.0f, 0.0f, // 25
		-0.4f, 0.1f, -0.4f,  1, 1, 1.0f, 0.0f, 0.0f, // 26
		-0.5f, 0.1f, -0.4f, 0, 1, 1.0f, 0.0f, 0.0f, // 27

		-0.5f, 0.4f, -0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // 28
		-0.4f, 0.4f, -0.5f,  1, 0, 0.0f, 0.0f, 1.0f, // 29
		-0.4f, 0.4f, -0.4f,  1, 1, 0.0f, 0.0f, 1.0f, // 30
		-0.5f, 0.4f, -0.4f, 0, 1, 0.0f, 0.0f, 1.0f, // 31

		//kaki kanan belakang
		0.5f, 0.1f, -0.5f, 0, 0, 1.0f, 0.0f, 0.0f, // 32
		0.4f, 0.1f, -0.5f,  1, 0, 1.0f, 0.0f, 0.0f, // 33
		0.4f, 0.1f, -0.4f,  1, 1, 1.0f, 0.0f, 0.0f, // 34
		0.5f, 0.1f, -0.4f, 0, 1, 1.0f, 0.0f, 0.0f, // 35

		0.5f, 0.4f, -0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // 36
		0.4f, 0.4f, -0.5f,  1, 0, 0.0f, 0.0f, 1.0f, // 37
		0.4f, 0.4f, -0.4f,  1, 1, 0.0f, 0.0f, 1.0f, // 38
		0.5f, 0.4f, -0.4f, 0, 1, 0.0f, 0.0f, 1.0f, // 39


	};
	// End -------- Coordinates --------

	// -------- Indices --------
	GLuint indices[] = {

	 0, 1, 2,  // Top Face
	 0, 2, 3,  // --------

	 4, 5, 6,   // Bottom Face
	 4, 6, 7,   // -----------

	 4, 5, 1,   // Front Face
	 4, 1, 0,   // ----------

	 6, 7, 3,   // Back Face
	 6, 3, 2,   // ---------

	 5, 6, 2,   // Right Face
	 5, 2, 1,   // ----------

	 7, 4, 0,   // Left Face
	 7, 0, 3,    // ----------

	 //kaki depan kiri
	 8, 9, 13,   // depan
	 8, 13, 12,    // ----------

	 9, 10, 14,   // kanan
	 9, 14, 13,    // ----------

	 11, 8, 12,   // kiri
	 11, 12, 15,    // ----------

	 10, 11, 15,   // blkng
	 11, 15, 14,    // ----------

	 8, 9, 10,   // bawah
	 8, 10, 11,    // ----------

	 //kaki depan kanan
	 16, 17, 21,   // depan
	 16, 21, 20,    // ----------

	 17, 18, 22,   // kanan
	 17, 22, 21,    // ----------

	 19, 16, 20,   // kiri
	 19, 20, 23,    // ----------

	 18, 19, 23,   // blkng
	 18, 23, 22,    // ----------

	 16, 17, 18,   // bawah
	 16, 18, 19,    // ----------


	 //kaki blkng kiri
	 24, 25, 29,   // depan
	 24, 29, 28,    // ----------

	 25, 26, 30,   // kanan
	 25, 30, 29,    // ----------

	 27, 24, 28,   // kiri
	 27, 28, 31,    // ----------

	 26, 27, 31,   // blkng
	 26, 31, 30,    // ----------

	 24, 25, 26,   // bawah
	 24, 26, 27,    // ----------

	 //kaki blkng kanan
	 32, 33, 37,   // depan
	 32, 37, 36,    // ----------

	 33, 34, 38,   // kanan
	 33, 38, 37,    // ----------

	 35, 32, 36,   // kiri
	 35, 36, 39,    // ----------

	 34, 35, 39,   // blkng
	 34, 39, 38,    // ----------

	 32, 33, 34,   // bawah
	 32, 34, 35    // ----------
	};

	glGenVertexArrays(1, &VAOMeja);
	glGenBuffers(1, &VBOMeja);
	glGenBuffers(1, &EBOMeja);

	glBindVertexArray(VAOMeja);

	glBindBuffer(GL_ARRAY_BUFFER, VBOMeja);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOMeja);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	// End -------- Indices --------
}
void Demo::DrawColoredMeja() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, txtMeja);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 6);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, txtMeja);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 6);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOMeja); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(2.7, 2.7, 2.7));
	model = glm::translate(model, glm::vec3(-1.0, -0.28, -2.4));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 156, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredAtap() {
	// -------- Loading the Image --------  
	glGenTextures(1, &txtAtap);
	glBindTexture(GL_TEXTURE_2D, txtAtap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("cream.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image -------- 

	// -------- Coordinates -------- 
	float vertices[] = {
		// format position, tex coords, Normal
		// Atas
		8.0, 7.5,  8.0,			0, 0,  0.0f, -1.0f, 0.0f,	// 0
		-8.0, 7.5,  8.0,		1, 0,  0.0f, -1.0f, 0.0f,	// 1
		-8.0, 7.5, -8.0,		1, 1,  0.0f, -1.0f, 0.0f,	// 2
		8.0, 7.5, -8.0,			0, 1,  0.0f, -1.0f, 0.0f,	// 3
	};
	// End -------- Coordinates -------- 

	// -------- Coordinates -------- 
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // Atas
	};

	glGenVertexArrays(1, &VAOAtap);
	glGenBuffers(1, &VBOAtap);
	glGenBuffers(1, &EBOAtap);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOAtap);

	glBindBuffer(GL_ARRAY_BUFFER, VBOAtap);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOAtap);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredAtap() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, txtAtap);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 7);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, txtAtap);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 7);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOAtap); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredSaklar(){
	// -------- Loading the Image --------  
	glGenTextures(1, &txtSaklar);
	glBindTexture(GL_TEXTURE_2D, txtSaklar);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Saklar.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image -------- 

	// -------- Coordinates -------- 
	GLfloat vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.0, 0, 0, 0.0f,  0.0f,  1.0f,  // 0
		0.5, -0.5, 0.0, 1, 0, 0.0f,  0.0f,  1.0f,  // 1
		0.5,  0.5, 0.0, 1, 1, 0.0f,  0.0f,  1.0f,  // 2
		-0.5,  0.5, 0.0, 0, 1, 0.0f,  0.0f,  1.0f,  // 3

		// right
		0.5,  0.5, 0.0, 0, 0,  1.0f,  0.0f,  0.0f,// 4
		0.5,  0.5, -0.2, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.2, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.2, 0, 0,0.0f,  0.0f,  1.0f, // 8 
		0.5,  -0.5, -0.2, 1, 0,0.0f,  0.0f,  1.0f, // 9
		0.5,   0.5, -0.2, 1, 1,0.0f,  0.0f,  1.0f, // 10
		-0.5,  0.5, -0.2, 0, 1,0.0f,  0.0f,  1.0f, // 11

		// left
		-0.5, -0.5, -0.2, 0, 0, 1.0f,  0.0f,  0.0f,// 12
		-0.5, -0.5,  0.0, 1, 0, 1.0f,  0.0f,  0.0f,// 13
		-0.5,  0.5,  0.0, 1, 1, 1.0f,  0.0f,  0.0f,// 14
		-0.5,  0.5, -0.2, 0, 1, 1.0f,  0.0f,  0.0f,// 15

		// upper
		0.5, 0.5,  0.0, 0, 0, 0.0f,  0.0f,  1.0f,  // 16
		-0.5, 0.5,  0.0, 1, 0,0.0f,  0.0f,  1.0f,  // 17
		-0.5, 0.5, -0.2, 1, 1,0.0f,  0.0f,  1.0f,  // 18
		0.5, 0.5, -0.2, 0, 1, 0.0f,  0.0f,  1.0f,  // 19

		// bottom
		-0.5, -0.5, -0.2, 0, 0, 1.0f,  0.0f,  0.0f,// 20
		0.5, -0.5, -0.2, 1, 0,  1.0f,  0.0f,  0.0f,// 21
		0.5, -0.5,  0.0, 1, 1,  1.0f,  0.0f,  0.0f,// 22
		-0.5, -0.5,  0.0, 0, 1, 1.0f,  0.0f,  0.0f// 23
	};
	// End -------- Coordinates -------- 

	// -------- Coordinates -------- 
	GLuint indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAOSaklar);
	glGenBuffers(1, &VBOSaklar);
	glGenBuffers(1, &EBOSaklar);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOSaklar);

	glBindBuffer(GL_ARRAY_BUFFER, VBOSaklar);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSaklar);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredSaklar(){
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, txtSaklar);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 8);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, txtSaklar);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 8);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOSaklar); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 4.45, -7.7));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLemari() {
	// -------- Loading the Image --------  
	glGenTextures(1, &txtLemari);
	glBindTexture(GL_TEXTURE_2D, txtLemari);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image -------- 

	// -------- Coordinates -------- 
	float vertices[] = {
		// format position, tex coords, Normal
		-0.5f,  0.5f, 0.5f, 0 ,0, 1.0f, 0.0f, 0.0f, // front top left 0
		0.5f, 0.5f, 0.5f,  1, 0, 1.0f, 0.0f, 0.0f,  // front top right 1
		0.5f, 0.5f, 0.2f, 1, 1, 1.0f, 0.0f, 0.0f,  // back top right 2
		-0.5f,  0.5f, 0.2f, 0, 1, 1.0f, 0.0f, 0.0f, // back top left 3 

		-0.5f, 1.5f, 0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // front bottom left 4
		0.5f, 1.5f, 0.5f,  1, 0, 0.0f, 0.0f, 1.0f,// front bottom right 5
		0.5f, 1.5f, 0.2f, 1, 1, 0.0f, 0.0f, 1.0f,// back bottom right 6
		-0.5f, 1.5f, 0.2f, 0, 1, 0.0f, 0.0f, 1.0f,// back bottom left 7
	};
	// End -------- Coordinates -------- 

	// -------- Coordinates -------- 
	unsigned int indices[] = {
	 0, 1, 2,  // Top Face
	 0, 2, 3,  // --------

	 4, 5, 6,   // Bottom Face
	 4, 6, 7,   // -----------

	 4, 5, 1,   // Front Face
	 4, 1, 0,   // ----------

	 6, 7, 3,   // Back Face
	 6, 3, 2,   // ---------

	 5, 6, 2,   // Right Face
	 5, 2, 1,   // ----------

	 7, 4, 0,   // Left Face
	 7, 0, 3,    // ----------
	};

	glGenVertexArrays(1, &VAOLemari);
	glGenBuffers(1, &VBOLemari);
	glGenBuffers(1, &EBOLemari);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOLemari);

	glBindBuffer(GL_ARRAY_BUFFER, VBOLemari);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOLemari);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredLemari() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, txtLemari);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 9);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, txtLemari);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 9);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOLemari); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(3, 3, 3));
	model = glm::translate(model, glm::vec3(1.0, -0.68, -2.70));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLemariDepan() {
	// -------- Loading the Image --------  
	glGenTextures(1, &txtLemariDepan);
	glBindTexture(GL_TEXTURE_2D, txtLemariDepan);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("LD.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// End -------- Loading the Image -------- 

	// -------- Coordinates -------- 
	float vertices[] = {
		// format position, tex coords, Normal
		-0.5f,  0.5f, 0.5f, 0 ,0, 1.0f, 0.0f, 0.0f, // front top left 0
		0.5f, 0.5f, 0.5f,  1, 0, 1.0f, 0.0f, 0.0f,  // front top right 1
		-0.5f, 1.5f, 0.5f, 0, 0, 0.0f, 0.0f, 1.0f, // front bottom left 2
		0.5f, 1.5f, 0.5f,  1, 0, 0.0f, 0.0f, 1.0f,// front bottom right 3
	};
	// End -------- Coordinates -------- 

	// -------- Coordinates -------- 
	unsigned int indices[] = {
	 2, 3, 1,   // Front Face
	 2, 1, 0,   // ----------
	};

	glGenVertexArrays(1, &VAOLemariDepan);
	glGenBuffers(1, &VBOLemariDepan);
	glGenBuffers(1, &EBOLemariDepan);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOLemariDepan);

	glBindBuffer(GL_ARRAY_BUFFER, VBOLemariDepan);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOLemariDepan);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredLemariDepan() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, txtLemariDepan);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 10);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, txtLemariDepan);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 10);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAOLemariDepan); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(3, 3, 3));
	model = glm::translate(model, glm::vec3(1.0, -0.68, -2.69));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// End ---------- Objek Benda ----------


void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 3.2f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.003f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("KamarTidur_Märchen", 1280, 720, false, false);
}