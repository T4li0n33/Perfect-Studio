#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <future>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

using namespace std;

int main()
{
	static bool showWindow = true, showWindow2 = true; //To change stuff
	bool project_mode = false;
	bool exit = false;
	bool calc_mode = false;
	bool wardrobe_type_bottom = false;
	bool wardrobe_type_top = false;
	bool wardrobe_type_unusual = false;
	bool wardrobe_model_shelf = false;
	bool wardrobe_model_drawer = false;
	bool wardrobe_model_corner = false;
	bool wardrobe_model_cargo = false;
	bool auto_shelf_ratio = true;
	bool auto_drawer_ratio = true;
	bool wardrobe_corner_lemans = false;
	bool wardrobe_corner_shelf = false;
	bool wardrobe_type_choosed = false;
	bool wardrobe_model_choosed = false;
	bool wardrobe_size_placed = false;
	bool opengl_presentation_mode = false;
	bool close_window = false;
	bool opengl_mode_exit = false;
	float base_x = 0, base_y = 0, base_z = 0;
	int shelf_number = 0, shelf_ration[4]{0,0,0,0};
	int drawer_number = 0, drawer_ratio[4]{ 0,0,0,0 };
	const unsigned int width = 1200;
	const unsigned int height = 800;
	


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //GLFW Presets

	GLFWwindow* window = glfwCreateWindow(width, height, "Ortega - Konwerter wymiarow geometrycznych", NULL, NULL); //Creating an GlFW window
	if (window == NULL)
	{
		cout << "Failed to create a window" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0,0,width,height); //Viewport


	Structure s1(44,7);

	EBO EBO1(s1.GetCuboidIndices(), s1.GetMaxIndexCount());

	EBO1.Unbind();

	Shader shaderProgram("default.vert", "default.frag");
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(s1.GetMaxVertexCount());

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Position));
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Color));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Texture));
	
	
	VAO1.Unbind();
	VBO1.Unbind();
	
	Texture projectTexture("Texture2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	projectTexture.texUnit(shaderProgram, "tex0", 0);

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	glClear(GL_COLOR_BUFFER_BIT); // Clearing Buffer



	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330"); // Standard ImGui presets
	glEnable(GL_DEPTH_TEST);



	


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
					
				project_mode = true;
				
			};

			ImGui::SetCursorPos(ImVec2(75, 150));
			if (ImGui::Button("Kalkulator wycen", ImVec2(250, 40)))
			{
				calc_mode = true;
			};

			ImGui::SetCursorPos(ImVec2(75, 210));
			if (ImGui::Button("Wyjscie", ImVec2(250, 40))) {
			
				exit = true;
			};

		}ImGui::End();


		//[Sector] Project_mode
		if (project_mode == true && showWindow == true) // Project_mode options
		{
			ImGui::SetNextWindowPos(ImVec2(400, 0));
			ImGui::SetNextWindowSize(ImVec2(800, 450));
			ImGui::Begin("Tryb Projektowy", &showWindow, ImGuiWindowFlags_NoSavedSettings);

			ImGui::Text("Jest to okno trybu projektowego");
			if (!wardrobe_type_bottom && !wardrobe_type_top && !wardrobe_type_unusual) { ImGui::Text("Wybierz rodzaj szafki"); };

			if (ImGui::Checkbox("Szafka dolna", &wardrobe_type_bottom))
			{
				wardrobe_type_top = false;
				wardrobe_type_unusual = false;
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Szafka gorna", &wardrobe_type_top))								// Choosing wardrobe type
			{	
				if (wardrobe_model_drawer || wardrobe_model_cargo)wardrobe_type_top = false;
				wardrobe_type_bottom = false;
				wardrobe_type_unusual = false;

			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Niestandardowa", &wardrobe_type_unusual))
			{
				wardrobe_type_top = false;
				wardrobe_type_bottom = false;
			};
			if (wardrobe_type_bottom || wardrobe_type_top || wardrobe_type_unusual)wardrobe_type_choosed = true;
			ImGui::Text("=================================");
			ImGui::Text("Wpisz wymiary szafki :");
			
			ImGui::Text("Wpisz szerokosc :");
			ImGui::SameLine();
			ImGui::InputFloat("##Width", &base_x, 0, 0);
			ImGui::Text("Wpisz wysokosc :");
			ImGui::SameLine();
			ImGui::InputFloat("##Lenght", &base_y, 0, 0);  // Wardrobe size inputs
			
			ImGui::Text("Wpisz glebokosc :");
			ImGui::SameLine();
			ImGui::InputFloat("##Height", &base_z, 0, 0);
			
			if (base_x != 0 && base_y != 0 && base_z != 0)wardrobe_size_placed = true;
			ImGui::Text("=================================");

			if (ImGui::Checkbox("Polka", &wardrobe_model_shelf)) // Shelf Checkbox
			{
				wardrobe_model_drawer = false;
				wardrobe_model_corner = false;
				wardrobe_model_cargo = false;
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Szuflada", &wardrobe_model_drawer)) // Drawer Checkbox
			{
				wardrobe_model_shelf = false;
				wardrobe_model_corner = false;
				wardrobe_model_cargo = false;
				if (wardrobe_type_top)
				{
					wardrobe_type_top = false;
				}
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Szafka narozna", &wardrobe_model_corner)) // Corner Checkbox
			{
				wardrobe_model_drawer = false;
				wardrobe_model_shelf = false;
				wardrobe_model_cargo = false;
			};
			ImGui::SameLine();
			if (ImGui::Checkbox("Cargo", &wardrobe_model_cargo)) // Cargo Checkbox
			{
				wardrobe_model_drawer = false;
				wardrobe_model_corner = false;
				wardrobe_model_shelf = false;

				if (wardrobe_type_top)
				{
					wardrobe_type_top = false;
				}
			};
			if (wardrobe_model_shelf || wardrobe_model_drawer || wardrobe_model_corner || wardrobe_model_cargo)wardrobe_model_choosed = true;

			if (wardrobe_model_shelf)
			{
				ImGui::Text("=================================");
				ImGui::InputInt("##shelf_number", &shelf_number , 1, 10); // Number of shelfs
			
				ImGui::Checkbox("Podzielic automatycznie?", &auto_shelf_ratio); // Automatic shelf height ratio

				if (!auto_shelf_ratio)
				{
						ImGui::Text("Wpisz wysokosc polki");
						ImGui::InputInt4("##shelf_number_ratio", &shelf_ration[0], 0); // Height of shelfs
						ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Jesli ilosc polek mniejsza niz 4 - nie zmieniac wartosci okna");
				}
			}

			if (wardrobe_model_drawer)
			{
				ImGui::Text("=================================");
				ImGui::InputInt("##drawer_number", &drawer_number, 1, 10); // Number of drawers

				ImGui::Checkbox("Podzielic automatycznie?", &auto_drawer_ratio); // Automatic drawer height ratio

				if (!auto_drawer_ratio)
				{
					ImGui::Text("Wpisz wysokosc szuflady");
					ImGui::InputInt4("##drawer_number_ratio", &drawer_ratio[0], 0); // Height of drawers
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Jesli ilosc szuflad mniejsza niz 4 - nie zmieniac wartosci okna");
				}
			}

			if (wardrobe_model_corner)
			{
				ImGui::Text("=================================");
				if(ImGui::Checkbox("Polka naroznik", &wardrobe_corner_shelf))wardrobe_corner_lemans = false; // Corner wardrobe type
				if (!wardrobe_type_top) { if (ImGui::Checkbox("Lemans", &wardrobe_corner_lemans)) wardrobe_corner_shelf = false; }; 

			}
			
			ImGui::Text("=================================");
			if (wardrobe_type_choosed && wardrobe_model_choosed && wardrobe_size_placed) // Confirm button
			{
				if (ImGui::Button("Potwierdz dane i wygeneruj podglad"))
				{
					opengl_presentation_mode = true;
				};
			};



			ImGui::End();

		};

		if (opengl_presentation_mode && showWindow2)
		{
			//ImGui window manage
			ImGui::SetNextWindowCollapsed(project_mode);
			ImGui::Begin("Tryb Projektowy");
			ImGui::End();
			projectTexture.Bind();
			VBO1.Bind();
			VAO1.Bind();
			EBO1.Bind();

			/*std::array<Converter::Element, 300> elems{};
			Converter::Element* e_buffer = elems.data();
			e_buffer = c1.Calculate(e_buffer, base_x, base_y, base_z, shelf_number);*/


			s1.DrawStructure(base_x, base_y, base_z, s1.GetMaxVertexCount(), shelf_number);
			glBufferSubData(GL_ARRAY_BUFFER, 0, s1.Vertices.size()*(sizeof(Structure::Vertex)), s1.Vertices.data());
			glDrawElements(GL_TRIANGLES, 1000, GL_UNSIGNED_INT, 0);
		
			ImGui::SetNextWindowPos(ImVec2(1000, 700));
			
			ImGui::Begin("Podglad 3D", &showWindow2, ImGuiWindowFlags_NoSavedSettings); //3D Projection Mode
			
			if (ImGui::Button("Zakoncz tryb projektowy"))
			{
				opengl_presentation_mode = false;
				showWindow2 = false;
				ImGui::SetNextWindowCollapsed(false);
				ImGui::Begin("Tryb Projektowy");
				ImGui::End();
				projectTexture.Unbind();
				VAO1.Unbind();
				s1.ClearVector();
			};
			if (!io.WantCaptureMouse) // Handles Camera input based on cursor position
			{
				camera.Inputs(window);
				camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
			}	
			ImGui::End();

		};

		//[Validation] Close window repairs
		{ 
			if (project_mode == true && showWindow == false)
			{
				showWindow = true;
				project_mode = false;
			}
			if (opengl_presentation_mode == true && showWindow2 == false)
			{
				showWindow2 = true;
				opengl_presentation_mode = false;
			};
		}
		


		//[Sector] Calculator_Mode 
		if (calc_mode == true && showWindow == true)
		{
			ImGui::Begin("Tryb Kalkulatora", &showWindow, ImGuiWindowFlags_NoSavedSettings);

			ImGui::Text("Funkcjonalnosc nieprzewidziana w tej wersji programu (DEMO)");
			ImGui::End();

		};
		if (calc_mode == true && showWindow == false)
		{
			showWindow = true;
			calc_mode = false;
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (exit == true) 
		{
			glfwDestroyWindow(window);
			VAO1.Delete();
			VBO1.Delete();
			EBO1.Delete();
			projectTexture.Delete();
			shaderProgram.Delete();
			s1.~Structure();
			return 0;
		}; //Exit Button
	}



	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
