#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <future>
#include <iostream>
#include <stb/stb_image.h>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "Camera.h"
#include "Texture.h"
#include <array>
#include "DrawFunctions.h"
#include "Converter.h"
#include "Settings.h"
#include "Wardrobe.h"
#include "GUI.h"


using namespace std;

int main()
{
	FreeConsole();
	Settings settings;
	Wardrobe wardrobe;
	Camera camera(settings.WindowWidth(), settings.WindowHeight(), glm::vec3(3.0f, 5.0f, 15.0f));
	Converter c1;
	Structure s1(c1, wardrobe);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW Presets

	GLFWwindow* window = glfwCreateWindow(settings.WindowWidth(), settings.WindowHeight(), "PerfectStudio - Srodowisko projektowe oraz konwerter wymiarow geometrycznych", NULL, NULL); //Creating an GlFW window
	if (window == NULL)
	{
		cout << "Failed to create a window" << endl;
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(window);
	GLFWimage images[1];
	images[0].pixels = stbi_load("icon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);
	gladLoadGL();
	glViewport(0,0, settings.WindowWidth(), settings.WindowHeight()); //Viewport
	glEnable(GL_DEPTH_TEST);
	Shader shaderProgram("default.vert", "default.frag");


	//Loading textures 

	Texture projectTexture("Texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture frontTexture("Texture2.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture drawerTexture("Drawer_Texture1.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);


	//Initializing buffers
	EBO EBO1;
	VAO VAO1;
	VBO VBO1;
	GUI Ortega_GUI(window);
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(34.0f / 255.0f, 43.0f / 255.0f, 52.0f / 255.0f, 0.6f); //Background color 142, 202, 230
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//// Setup style
		ImGuiStyle& style = ImGui::GetStyle();
		Ortega_GUI.INI();
		Ortega_GUI.Menu(settings);
		Ortega_GUI.ProjectionGUI(settings, wardrobe);


		if (settings.GetMode(3) && settings.GetWindow(2))
		{
			bool x = true, i = true;
			//ImGui window manage
			ImGui::SetNextWindowCollapsed(x);
			if (!x)settings.SetMode(1);
			ImGui::Begin("Tryb Projektowy");
			ImGui::End();

			//Ortega_GUI.ProjectionBegin(settings, wardrobe);
				//[Texture loading]
			shaderProgram.Activate();

			projectTexture.BindTexUnit(0, projectTexture.ID);
			frontTexture.BindTexUnit(1, frontTexture.ID);
			drawerTexture.BindTexUnit(2, drawerTexture.ID);
			shaderProgram.texUnitLoader("u_Textures");

			//[Binding buffers] 
			VAO1.Bind();
			VBO1.Bind();
			EBO1.Bind();

			if (c1.Checkchanges(wardrobe) || wardrobe.CheckRatioChanges())

			{
				//Doing math to create elements
				c1.Calculate(wardrobe);
				s1.UpdateStructure(c1);

				EBO1.EBOUpdate(s1.GetCuboidIndices(), s1.GetMaxIndexCount());
				VBO1.VBOUpdate(s1.GetMaxVertexCount());

				VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Position));
				VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Color));
				VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Texture));
				VAO1.LinkAttrib(VBO1, 3, 1, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, TexIndex));

				glClear(GL_COLOR_BUFFER_BIT); // Clearing Buffer


				s1.DrawStructure(c1, wardrobe);
			}


			//glDisable(GL_CULL_FACE);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(0.1f, 0.1f);  // Eksperymentuj z mniejszymi wartoœciam
			glBufferSubData(GL_ARRAY_BUFFER, 0, s1.Vertices.size() * (sizeof(Structure::Vertex)), s1.Vertices.data());
			glDrawElements(GL_TRIANGLES, s1.GetMaxIndexCount(), GL_UNSIGNED_INT, 0);
			glDisable(GL_POLYGON_OFFSET_FILL);
			//Ortega_GUI.ProjectionGUI_End(settings, VBO1, VAO1, EBO1, shaderProgram, projectTexture, camera, io, window, i);
			//Ortega_GUI.ProjectionEnd(settings);
			
			ImGui::SetNextWindowPos(ImVec2(1000, 700));
			//bool i;
			ImGui::Begin("Podglad 3D", &i, ImGuiWindowFlags_NoSavedSettings); //3D Projection Mode
			if (!i)settings.SetWindow(2);
			if (ImGui::Button("Zakoncz tryb projektowy"))
			{
				settings.SetMode(3);
				settings.SetWindow(2);
				ImGui::SetNextWindowCollapsed(false);
				ImGui::Begin("Tryb Projektowy");
				ImGui::End();
				projectTexture.Unbind();
				VAO1.Unbind();
				VBO1.Unbind();
				EBO1.Unbind();


			};
			
			if (!Ortega_GUI.GetIO().WantCaptureMouse) // Handles Camera input based on cursor position
			{
				camera.Inputs(window);
				camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
			}
			ImGui::End();

		};


		settings.RepairWindow();

		Ortega_GUI.Calc(settings);
		Ortega_GUI.HoldEvents(window);
	
		//s1.~Structure(); // Change it so structure objects will be destroyed too (Now left for temporary reminder)
		if (window)
		{
			Ortega_GUI.Exit(settings, VBO1, VAO1, EBO1, shaderProgram, projectTexture, window);
		}
		
		
	}	
		
		Ortega_GUI.Shutdown();
		glfwTerminate();
		return 0;
	}