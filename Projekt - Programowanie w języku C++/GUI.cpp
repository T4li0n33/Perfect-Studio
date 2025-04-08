#include "GUI.h"
#include <GLFW/glfw3.h>
#include "WardrobeManager.h"


void GUI::INI()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(400, 800));

	// Setup style
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.31f, 0.25f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.74f, 0.74f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.62f, 0.70f, 0.72f, 0.56f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.95f, 0.33f, 0.14f, 0.47f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.84f, 0.04f, 0.53f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 0.84f, 0.04f, 0.53f); // 255, 214, 10
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.85f, 0.04f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.40f, 0.62f, 0.80f, 0.15f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.39f, 0.64f, 0.80f, 0.30f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.67f, 0.80f, 0.59f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.48f, 0.53f, 0.67f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.48f, 0.47f, 0.47f, 0.71f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.31f, 0.47f, 0.99f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(177.00f / 255.00f, 192.0f / 255.00f, 197.0f / 255.00f, 0.78f); //ImVec4(1.00f, 0.79f, 0.18f, 0.78f); 
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.42f, 0.82f, 1.00f, 0.81f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.72f, 1.00f, 1.00f, 0.86f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.65f, 0.78f, 0.84f, 0.80f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.88f, 0.94f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.46f, 0.84f, 0.90f, 1.00f);//ImVec4(0.55f, 0.68f, 0.74f, 0.80f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.60f, 0.60f, 0.80f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.99f, 0.54f, 0.43f);
	style.Alpha = 1.0f;
	style.FrameRounding = 4;
	style.IndentSpacing = 12.0f;



}

void GUI::Menu(Settings &settings)
{
	if (ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImGui::SetCursorPos(ImVec2(110, 30));
		ImGui::Text("Witamy w programie PerfectStudio");

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
}

void GUI::ProjectionGUI(Settings &settings, WardrobeManager& manager)
{

	Wardrobe& wardrobe = manager.GetCurrentWardrobe();
	float top_margins = 20.0f;
	float small_margin = 5.0f;
	ImColor blue(13, 146, 244);

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
		
		if (!wardrobe.GetWardrobeType(1) && !wardrobe.GetWardrobeType(2) && !wardrobe.GetWardrobeType(3)) 
		{
			ImGui::PushFont(boldFont);
			ImGui::TextColored(blue, "Wybierz rodzaj szafki :");
			ImGui::PopFont();
		};

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);;
		if (ImGui::Checkbox("Szafka dolna", &a))
		{
			wardrobe.SetWardrobeType(1);
		};
		ImGui::SameLine();
		if (ImGui::Checkbox("Szafka gorna", &b))								// Choosing wardrobe type
		{

			wardrobe.SetWardrobeType(2);
			wardrobe.SetWardrobeModel(1);

		};
		ImGui::SameLine();
		if (ImGui::Checkbox("Niestandardowa", &c))
		{
			wardrobe.SetWardrobeType(3);
		};


		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);
		if (!wardrobe.GetBaseSettings(1) || !wardrobe.GetBaseSettings(2) || !wardrobe.GetBaseSettings(3)) 
		{
			ImGui::PushFont(boldFont);
			ImGui::TextColored(blue, "Wpisz wymiary szafki :");
			ImGui::PopFont();
		}
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);

		float d = wardrobe.GetBaseSettings(1), e = wardrobe.GetBaseSettings(2), f = wardrobe.GetBaseSettings(3);
		ImGui::Text("Wpisz szerokosc :");
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);
		if (ImGui::SmallButton("Auto x")) d = 600;  
		ImGui::SameLine();
		ImGui::InputFloat("##Width", &d, 0, 0);
		wardrobe.SetSize(1, d);

		ImGui::Text("Wpisz wysokosc :");
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);
		if (ImGui::SmallButton("Auto y")) e = 720;
		ImGui::SameLine();
		ImGui::InputFloat("##Lenght", &e, 0, 0);  // Wardrobe size inputs
		wardrobe.SetSize(2, e);
		ImGui::Text("Wpisz glebokosc :");
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);
		if (ImGui::SmallButton("Auto z")) f = 510;
		ImGui::SameLine();
		ImGui::InputFloat("##Height", &f, 0, 0);
		wardrobe.SetSize(3, f);

		std::string st = wardrobe.GetVeener();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins); //Veneer Color
		ImGui::InputText("Kolor okleiny", &st);
		wardrobe.SetVeenerColor(st);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);
		bool g = wardrobe.GetWardrobeModel(1), h = wardrobe.GetWardrobeModel(2), j = wardrobe.GetWardrobeModel(3), k = wardrobe.GetWardrobeModel(4);
		if (ImGui::Checkbox("Polka", &g)) // Shelf Checkbox
		{
			wardrobe.SetWardrobeModel(1);
			wardrobe.SetDrawers(0, 0);
		};
		
		ImGui::SameLine();
		if(!wardrobe.GetWardrobeType(2))
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
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);
			
		};
		
		
		if (!wardrobe.GetWardrobeType(2))
		{
			ImGui::SameLine();
			if (ImGui::Checkbox("Cargo", &j)) // Cargo Checkbox
			{
				wardrobe.SetWardrobeModel(4);

				if (wardrobe.GetWardrobeType(2))
				{
					wardrobe.SetWardrobeType(1);
				}
			};
		}
		

		if (wardrobe.GetWardrobeModel(1) || wardrobe.GetWardrobeModel(4))
		{
			wardrobe.SetDrawers(0, 0);
			int shelf_number = wardrobe.GetAmount(2);
			float* shelf_ratio = wardrobe.shelf_ratio;
			bool ratio = wardrobe.GetAutoRatio(1);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);

			ImGui::Text("Wpisz ilosc polek:");
			ImGui::InputInt("##shelf_number", &shelf_number, 1, 10);
			if (shelf_number > 4) { ImGui::TextColored(ImVec4(1, 0, 0, 1), "Mozesz miec tylko 4 polki!"); }// Number of shelfs

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);;
			ImGui::Checkbox("Podzielic automatycznie?", &ratio); // Automatic shelf height ratio

			if (!ratio)
			{
				wardrobe.SetAutoRatio(1);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);;
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

			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1));
			int selected = wardrobe.GetDrawerColor();
			const char* colour[3] = { "szara", "biala", "czarna" };
			int n = 0;
			static const char* current_item = colour[selected];
			ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;
			float w = ImGui::CalcItemWidth();
			ImGuiStyle local_style = ImGui::GetStyle();
			float spacing = local_style.ItemInnerSpacing.x;
			float button_sz = ImGui::GetFrameHeight();
			ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);

			//Chooseing drawer color
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);
			if (ImGui::BeginCombo("Kolor szuflady", current_item, ImGuiComboFlags_NoArrowButton))
			{
				for (; n < IM_ARRAYSIZE(colour); n++)
				{
					bool is_selected = (current_item == colour[n]);
					if (ImGui::Selectable(colour[n], is_selected))
					{
						current_item = colour[n];
						wardrobe.SetDrawerColor(n);
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();


			}
			ImGui::PopItemWidth();
			ImGui::PopStyleColor();


			wardrobe.SetShelfs(0, 0);
			int drawer_number = wardrobe.GetAmount(1);
			float* drawer_ratio = wardrobe.drawer_ratio;
			bool ratio2 = wardrobe.GetAutoRatio(2);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);
			ImGui::Text("Wpisz ilosc szuflad:");
			ImGui::InputInt("##drawer_number", &drawer_number, 1, 10); // Number of drawers
			if (drawer_number > 4) {
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Mozesz miec tylko 4 szuflady!");
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);
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

	


		//[FRONTS INPUT]
		bool fronts = wardrobe.GetFrontBool(1);
		bool ratio3 = wardrobe.GetAutoRatio(3);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);;
		//ImGui::Spacing(); ImGui::Spacing();
		ImGui::Checkbox("Szafka z frontami?", &fronts);
		if (fronts)
		{
			wardrobe.SetFrontBool(2);

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + small_margin);
			ImGui::Text("Wpisz ilosc frontow:");
			int front_number = wardrobe.GetAmount(3);
			float* front_ratio = wardrobe.front_ratio;

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);;
			ImGui::InputInt("##front_number", &front_number, 1, 10);
			wardrobe.SetFronts(front_number, front_ratio);
			if (front_number > 4) {
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "Mozesz miec tylko 4 fronty!");
			}// Number of fronts



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
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + top_margins);

		if (wardrobe.AreOptionsPicked()) // Confirm button
		{
			if (ImGui::Button("Potwierdz dane i wygeneruj podglad"))
			{
				settings.SetMode(3);
			};
		};

		ImGui::End();

	};

}

void GUI::ProjectionBegin(Settings settings, Wardrobe wardrobe)
{
}

void GUI::ProjectionGUI_End(Settings &settings, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture, Camera& camera, ImGuiIO io, GLFWwindow* window, bool i, WardrobeManager& manager)
{
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
		texture.Unbind();
		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();


	};
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);
	if (ImGui::Button("Dodaj kolejn¹ szafkê"))
	{
		manager.AddNewWardrobe();
		settings.SetMode(1);  // Ponownie przechodzi do trybu projektowego
	}
	if (!io.WantCaptureMouse) // Handles Camera input based on cursor position
	{
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");
	}
	ImGui::End();

}

//void GUI::ProjectionEnd(Settings settings)
//{
//	ImGui::SetNextWindowPos(ImVec2(1000, 700));
//	bool i = true;
//	ImGui::Begin("Podglad 3D", &i, ImGuiWindowFlags_NoSavedSettings); //3D Projection Mode
//	if (!i)settings.SetWindow(2);
//	if (ImGui::Button("Zakoncz tryb projektowy"))
//	{
//		settings.SetMode(3);
//		settings.SetWindow(2);
//		ImGui::SetNextWindowCollapsed(false);
//		ImGui::Begin("Tryb Projektowy");
//		ImGui::End();
//	}
//	ImGui::End();
//}

void GUI::Calc(Settings &settings)
{
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
}

//void GUI::Exit(Settings settings, VBO vbo, VAO vao, EBO ebo, Shader shader, Texture texture, GLFWwindow &window)
//{
//
//	if (settings.GetMode(4))
//	{
//		vao.Delete();
//		vbo.Delete();
//		ebo.Delete();
//		texture.Delete();
//		shader.Delete();
//		//s.~Structure();
//		glfwDestroyWindow(&window);
//		
//	}; //Exit Button
//}

void GUI::Exit(Settings& settings, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture, GLFWwindow* window)
{
    if (settings.GetMode(4))
    {
        vao.Delete();
        vbo.Delete();
        ebo.Delete();
        texture.Delete();
        shader.Delete();
        if (window != nullptr) {
            glfwSetWindowShouldClose(window, GLFW_FALSE);
            glfwDestroyWindow(window);
            window = nullptr; // Ustawienie wskaŸnika na nullptr po zniszczeniu okna
        }
        //s.~Structure();
    } //Exit Button
}

void GUI::HoldEvents(GLFWwindow* window)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();

}

GUI::GUI(GLFWwindow *window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	SetImGuiLocation();
	ImFontConfig config;
	style = &ImGui::GetStyle();
	ImGuiIO& localIo = *io;
	localIo.Fonts->AddFontFromFileTTF("Regular.ttf", 16.0f, NULL);
	ImFont* boldFont = localIo.Fonts->AddFontFromFileTTF("Bold.ttf", 16.0f, NULL);
	this->boldFont = boldFont;

	localIo.Fonts->Build();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330"); // Standard ImGui presets

}

void GUI::SetImGuiLocation()
{
	io = &ImGui::GetIO();
}

void GUI::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

