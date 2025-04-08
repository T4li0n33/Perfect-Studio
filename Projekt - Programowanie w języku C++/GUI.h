#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Settings.h"
#include "Wardrobe.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "shaderClass.h"
#include "Camera.h"
#include "WardrobeManager.h"




class GUI
{
private:
	ImGuiStyle* style = nullptr;
	ImGuiIO* io;
	ImFont* boldFont;
public:

	void INI();
	void Menu(Settings &settings);
	void ProjectionGUI(Settings& settings, WardrobeManager& manager);
	void ProjectionBegin(Settings settings, Wardrobe wardrobe);
	void ProjectionGUI_End(Settings& settings, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture, Camera& camera, ImGuiIO io, GLFWwindow* window, bool i, WardrobeManager& manager);
	//void ProjectionGUI_End(Settings settings, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture, Camera& camera);
	void Calc(Settings &settings);
	//void Exit(Settings settings, VBO vbo, VAO vao, EBO ebo, Shader shader, Texture texture, GLFWwindow& window);
	void Exit(Settings &settings, VBO &vbo, VAO &vao, EBO &ebo, Shader &shader, Texture &texture, GLFWwindow* window);
	void HoldEvents(GLFWwindow *window);
	GUI(GLFWwindow *window);
	ImGuiIO& GetIO() { return *io; }
	void SetImGuiLocation();
	void Shutdown();
};

