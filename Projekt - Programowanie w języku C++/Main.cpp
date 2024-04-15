#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <future>
#include <iostream>
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

using namespace std;

int main()
{
	Settings settings;
	Wardrobe wardrobe;
	Camera camera(settings.WindowWidth(), settings.WindowHeight(), glm::vec3(0.0f, 0.0f, 2.0f));
	Converter c1;
	Structure s1(c1, wardrobe);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW Presets

	GLFWwindow* window = glfwCreateWindow(settings.WindowWidth(), settings.WindowHeight(), "Ortega - Konwerter wymiarow geometrycznych", NULL, NULL); //Creating an GlFW window
	if (window == NULL)
	{
		cout << "Failed to create a window" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0,0, settings.WindowWidth(), settings.WindowHeight()); //Viewport


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330"); // Standard ImGui presets
	glEnable(GL_DEPTH_TEST);
	Shader shaderProgram("default.vert", "default.frag");
	Texture projectTexture("Texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	EBO EBO1;
	VAO VAO1;
	VBO VBO1;
	while (!glfwWindowShouldClose(window))
	{

		

		shaderProgram.Activate();
		

		glClearColor(2.0f / 255.0f, 62.0f / 255.0f, 125.0f / 255.0f, 1.0f); //Background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(400,800));
		ImGuiStyle &style = ImGui::GetStyle();
		style.WindowRounding = 5;
		style.Colors[ImGuiCol_WindowBg] = ImVec4( 0.0f/255.0f, 18.0f/255.0f, 51.0f/255.0f, 1.0f);
		style.Colors[ImGuiCol_Button]  =  ImVec4( 92.0f/255.0f, 103.0f/255.0f, 125.0f/255.0f, 1.0f); // Window Style edit
		style.Colors[ImGuiCol_ChildBg] = ImVec4( 51.0f/255.0f, 65.0f/255.0f, 92.0f/255.0f, 1.0f);
		//	ImGui Color Styling


	
		//[Sector] Main_Menu
		if (ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			ImGui::SetCursorPos(ImVec2(110, 30));
			ImGui::Text("Witamy w programie Ortega");

			ImGui::SetCursorPos(ImVec2(75, 90));
			if (ImGui::Button("Tryb projektowy", ImVec2(250, 40))) {
					
				settings.SetMode(1);
				
			};

			ImGui::SetCursorPos(ImVec2(75, 150));
			if (ImGui::Button("Kalkulator wycen", ImVec2(250, 40)))
			{
				settings.SetMode(2);
			};

			ImGui::SetCursorPos(ImVec2(75, 210));
			if (ImGui::Button("Wyjscie", ImVec2(250, 40))) {
			
				settings.SetMode(4);
			};

		}ImGui::End();


		//[Sector] Project_mode
		if (settings.GetMode(1) && settings.GetWindow(1)) // Project_mode options
		{	
			bool x = true, a = wardrobe.GetWardrobeType(1), b = wardrobe.GetWardrobeType(2), c = wardrobe.GetWardrobeType(3);
			ImGui::SetNextWindowPos(ImVec2(400, 0));
			ImGui::SetNextWindowSize(ImVec2(800, 450));
			ImGui::Begin("Tryb Projektowy", &x, ImGuiWindowFlags_NoSavedSettings);
			if (!x)
			{
				settings.SetWindow(1);
				x = !x;
			}
			//ImGui::Text("Jest to okno trybu projektowego");
			if (!wardrobe.GetWardrobeType(1) && !wardrobe.GetWardrobeType(2) && !wardrobe.GetWardrobeType(3)) { ImGui::Text("Wybierz rodzaj szafki"); };
			
			if (ImGui::Checkbox("Szafka dolna", &a))
			{
				wardrobe.SetWardrobeType(1);
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Szafka gorna", &b))								// Choosing wardrobe type
			{	
				
				wardrobe.SetWardrobeType(2);

			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Niestandardowa", &c))
			{
				wardrobe.SetWardrobeType(3);
			};

			
			ImGui::Text("=================================");
			ImGui::Text("Wpisz wymiary szafki :");
			float d = wardrobe.GetBaseSettings(1), e = wardrobe.GetBaseSettings(2), f = wardrobe.GetBaseSettings(3);
			ImGui::Text("Wpisz szerokosc :");
			ImGui::SameLine();
			ImGui::InputFloat("##Width", &d, 0, 0);
			wardrobe.SetSize(1, d);
			ImGui::Text("Wpisz wysokosc :");
			if (ImGui::SmallButton("Auto y")) e = 720;
			ImGui::SameLine();
			ImGui::InputFloat("##Lenght", &e, 0, 0);  // Wardrobe size inputs
			wardrobe.SetSize(2, e);
			ImGui::Text("Wpisz glebokosc :");
			if (ImGui::SmallButton("Auto z")) f = 510;
			ImGui::SameLine();
			ImGui::InputFloat("##Height", &f, 0, 0);
			wardrobe.SetSize(3, f);
			
		
			ImGui::Text("=================================");
			bool g = wardrobe.GetWardrobeModel(1), h = wardrobe.GetWardrobeModel(2), j = wardrobe.GetWardrobeModel(3), k = wardrobe.GetWardrobeModel(4);
			if (ImGui::Checkbox("Polka", &g)) // Shelf Checkbox
			{
				wardrobe.SetWardrobeModel(1);
				wardrobe.SetDrawers(0, 0);
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Szuflada", &h)) // Drawer Checkbox
			{
				wardrobe.SetWardrobeModel(2);
				if (wardrobe.GetWardrobeType(2))
				{
					wardrobe.SetWardrobeType(1);
				}
				
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Szafka narozna", &k)) // Corner Checkbox
			{
				wardrobe.SetWardrobeModel(3);
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Cargo", &j)) // Cargo Checkbox
			{
				wardrobe.SetWardrobeModel(4);

				if (wardrobe.GetWardrobeType(2))
				{
					wardrobe.SetWardrobeType(1);
				}
			};
			
			
			if (wardrobe.GetWardrobeModel(1))
			{
				wardrobe.SetDrawers(0, 0);
				int shelf_number = wardrobe.GetAmount(2);
				float* shelf_ratio = wardrobe.shelf_ratio;
				bool ratio = wardrobe.GetAutoRatio(1);
				ImGui::Text("=================================");
				ImGui::Text("Wpisz ilosc polek:");
				ImGui::InputInt("##shelf_number", &shelf_number , 1, 10);
				if (shelf_number > 4) { ImGui::Text("Mozesz miec tylko 4 polki!"); }// Number of shelfs
				
			
				ImGui::Checkbox("Podzielic automatycznie?", &ratio); // Automatic shelf height ratio
				
				if (!ratio)
				{
					wardrobe.SetAutoRatio(1);
					ImGui::Text("Wpisz wysokosc polki");
					ImGui::InputFloat4("##shelf_number_ratio", &shelf_ratio[0], 0); // Height of shelfs
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Jesli ilosc polek mniejsza niz 4 - nie zmieniac wartosci okna");
					wardrobe.SetShelfs(shelf_number, shelf_ratio);
				}
				else
				{
					wardrobe.SetAutoRatio(4);
					wardrobe.SetShelfs(shelf_number, shelf_ratio);
				}
				
			}

			if (wardrobe.GetWardrobeModel(2))
			{
				wardrobe.SetShelfs(0, 0);
				int drawer_number = wardrobe.GetAmount(1);
				float* drawer_ratio = wardrobe.drawer_ratio;
				bool ratio2 = wardrobe.GetAutoRatio(2);
				ImGui::Text("=================================");
				ImGui::Text("Wpisz ilosc szuflad:");
				ImGui::InputInt("##drawer_number", &drawer_number, 1, 10); // Number of drawers

				ImGui::Checkbox("Podzielic automatycznie?", &ratio2);// Automatic drawer height ratio
				

				if (!ratio2)
				{
					wardrobe.SetAutoRatio(2);
					ImGui::Text("Wpisz wysokosc szuflady");
					ImGui::InputFloat4("##drawer_number_ratio", &drawer_ratio[0], 0); // Height of drawers
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Jesli ilosc szuflad mniejsza niz 4 - nie zmieniac wartosci okna");
					wardrobe.SetDrawers(drawer_number, drawer_ratio);
				}
				else 
				{
					wardrobe.SetAutoRatio(3);
					wardrobe.SetDrawers(drawer_number, drawer_ratio);
				}
			}

			if (wardrobe.GetWardrobeModel(4))
			{
				ImGui::Text("=================================");
				bool cor = wardrobe.GetWardrobeTypeCorner(2), cor2 = wardrobe.GetWardrobeTypeCorner(1);
				if (ImGui::Checkbox("Polka naroznik", &cor))
				{
					wardrobe.SetWardrobeTypeCorner(2);
					wardrobe.SetShelfs(1, 0);
				}; // Corner wardrobe type
				if (!b) { if (ImGui::Checkbox("Lemans", &cor2)) wardrobe.SetWardrobeTypeCorner(1); }; 

			}
			
			
			//[FRONTS INPUT]
			bool fronts = wardrobe.GetFrontBool(1);
			bool ratio3 = wardrobe.GetAutoRatio(3);
			ImGui::Text("=================================");
			ImGui::Spacing(); ImGui::Spacing();
			ImGui::Checkbox("Szafka z frontami?", &fronts);
			if(fronts)
			{
				wardrobe.SetFrontBool(2);
				ImGui::Text("Wpisz ilosc frontow:");
				int front_number = wardrobe.GetAmount(3);
				float* front_ratio = wardrobe.front_ratio;
				
				ImGui::Text("=================================");
				ImGui::InputInt("##front_number", &front_number, 1, 10);
				if (front_number > 4) { ImGui::Text("Mozesz miec tylko 4 fronty!"); }// Number of fronts


				ImGui::Checkbox("Podzielic fronty automatycznie?", &ratio3); // Automatic front ratio

				if (!ratio3)
				{
					wardrobe.SetAutoRatio(5);
					ImGui::Text("Wpisz wysokosc frontow");
					ImGui::InputFloat4("##front_number_ratio", &front_ratio[0], 0); // Height of fronts
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Jesli ilosc frontow mniejsza niz 4 - nie zmieniac wartosci okna");
					wardrobe.SetFronts(front_number, front_ratio);
				}
				else
				{	
					wardrobe.SetAutoRatio(6);
					wardrobe.SetFronts(front_number, front_ratio);
				}
			}
			else
			{
				wardrobe.SetFrontBool(1);
				wardrobe.SetFronts(0, 0);
			}
			ImGui::Text("=================================");
			if (wardrobe.AreOptionsPicked()) // Confirm button
			{
				if (ImGui::Button("Potwierdz dane i wygeneruj podglad"))
				{
					settings.SetMode(3);
				};
			};

			ImGui::End();

		};

		if (settings.GetMode(3) && settings.GetWindow(2))
		{
			bool x = true, i = true;
			//ImGui window manage
			ImGui::SetNextWindowCollapsed(x);
			if (!x)settings.SetMode(1);
			ImGui::Begin("Tryb Projektowy");
			ImGui::End();

			VAO1.Bind();
			projectTexture.Bind();
			VBO1.Bind();
			EBO1.Bind();
		
			if (c1.Checkchanges(wardrobe) || wardrobe.CheckRatioChanges())
				//Doing math to create elements
			{
				c1.Calculate(wardrobe);
				s1.UpdateStructure(c1);

				EBO1.EBOUpdate(s1.GetCuboidIndices(), s1.GetMaxIndexCount());
				VBO1.VBOUpdate(s1.GetMaxVertexCount());

				VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Position));
				VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Color));
				VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Texture));
				projectTexture.texUnit(shaderProgram, "tex0", 0);

				GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
				glClear(GL_COLOR_BUFFER_BIT); // Clearing Buffer

				
				s1.DrawStructure(c1, wardrobe);
			}


			
		
			glBufferSubData(GL_ARRAY_BUFFER, 0, s1.Vertices.size()*(sizeof(Structure::Vertex)), s1.Vertices.data());
			glDrawElements(GL_TRIANGLES, s1.GetMaxIndexCount(), GL_UNSIGNED_INT, 0);
			ImGui::SetNextWindowPos(ImVec2(1000, 700));
			
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
			if (!io.WantCaptureMouse) // Handles Camera input based on cursor position
			{
				camera.Inputs(window);
				camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
			}	
			ImGui::End();

		};


		settings.RepairWindow();

		

		//[Sector] Calculator_Mode 
		if (settings.GetMode(2) && settings.GetWindow(1))
		{
			bool x = true;
			ImGui::Begin("Tryb Kalkulatora", &x, ImGuiWindowFlags_NoSavedSettings);

			if (!x)
			{
				settings.SetWindow(1);
				x = !x;
			}
			ImGui::Text("Funkcjonalnosc nieprzewidziana w tej wersji programu (DEMO)");
			ImGui::End();

		};
		if (settings.GetMode(2) && !settings.GetWindow(1))
		{
			settings.SetWindow(1);
			settings.SetMode(2);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (settings.GetMode(4)) 
		{
			VAO1.Delete();
			VBO1.Delete();
			EBO1.Delete();
			projectTexture.Delete();
			shaderProgram.Delete();
			s1.~Structure();
			glfwDestroyWindow(window);
			return 0;
		}; //Exit Button
	}



	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
