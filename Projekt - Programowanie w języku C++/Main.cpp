#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN
#ifdef byte
#undef byte
#endif
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
#include "WardrobeManager.h"
#include "ConverterManager.h"
#include "StructureManager.h"
#include "SceneSelector.h"
#include "InputHandler.h"
#include "Exporter.h"

using namespace std;

int main()
{
   // FreeConsole();
    SetConsoleOutputCP(CP_UTF8);
    Settings settings;
    WardrobeManager manager;
    ConverterManager converterManager;
    StructureManager structureManager;
    
    manager.AddNewWardrobe();

    converterManager.AddNewConverter();
    Converter& converter = converterManager.GetCurrentConverter();

    structureManager.AddNewStructure(converter, manager.GetCurrentWardrobe());
    Structure& structure = structureManager.GetCurrentStructure();

   
   

    Camera camera(settings.WindowWidth(), settings.WindowHeight(), glm::vec3(3.0f, 5.0f, 15.0f));
    SceneSelector sceneSelector;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(settings.WindowWidth(), settings.WindowHeight(),
        "PerfectStudio - Srodowisko projektowe", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create a window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    GLFWimage images[1];
    images[0].pixels = stbi_load("icon.png", &images[0].width, &images[0].height, 0, 4);
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);
    gladLoadGL();
    glViewport(0, 0, settings.WindowWidth(), settings.WindowHeight());
    glEnable(GL_DEPTH_TEST);

    Shader shaderProgram("default.vert", "default.frag");

    // Tekstury
    Texture projectTexture("Texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture frontTexture("Texture2.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture drawerTexture("Drawer_Texture1.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);

    // Bufory
    EBO EBO1;
    VAO VAO1;
    VBO VBO1;
    GUI Ortega_GUI(window);

    bool newStructureFlag = false;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(34.0f / 255.0f, 43.0f / 255.0f, 52.0f / 255.0f, 0.6f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Ortega_GUI.INI();
        Ortega_GUI.Menu(settings);

        // **G³ówna zmiana: Przekazujemy `WardrobeManager` do GUI**
        Ortega_GUI.ProjectionGUI(settings, manager);

        if (settings.GetMode(3) && settings.GetWindow(2))
        {
            bool x = true;
            ImGui::SetNextWindowCollapsed(x);
            if (!x) settings.SetMode(1);
            ImGui::Begin("Tryb Projektowy");
            ImGui::End();

            shaderProgram.Activate();
            projectTexture.BindTexUnit(0, projectTexture.ID);
            frontTexture.BindTexUnit(1, frontTexture.ID);
            drawerTexture.BindTexUnit(2, drawerTexture.ID);
            shaderProgram.texUnitLoader("u_Textures");

            for (size_t i = 0; i < structureManager.GetTotalStructures(); ++i)
            {
                Wardrobe& currentWardrobe = manager.GetWardrobeByIndex(i);
                Converter& converter = converterManager.GetConverterByIndex(i);
                Structure& structure = structureManager.GetStructureByIndex(i);

                converter.Calculate(currentWardrobe);

                if (currentWardrobe.CheckRatioChanges())
                {
                    structure.UpdateStructure(converter);
                    structure.DrawStructure(converter, currentWardrobe);
                    structure.UpdateHitboxData();
                }
            }
            structureManager.GenerateGlobalIndices();


            VAO1.Bind();
            VBO1.Bind();
            EBO1.Bind();
            vector<Structure::Vertex> combinedVertices;
            vector<GLuint> combinedIndices;

            Wardrobe& currentWardrobe = manager.GetCurrentWardrobe();
          


                structureManager.CollectCombinedBufferData(combinedVertices, combinedIndices);
                VBO1.VBOUpdate(combinedVertices.size() * sizeof(Structure::Vertex));
                glBufferSubData(GL_ARRAY_BUFFER, 0, combinedVertices.size() * sizeof(Structure::Vertex), combinedVertices.data());

                EBO1.EBOUpdate(combinedIndices, combinedIndices.size());

                VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Position));
                VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Color));
                VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, Texture));
                VAO1.LinkAttrib(VBO1, 3, 1, GL_FLOAT, sizeof(Structure::Vertex), (void*)offsetof(Structure::Vertex, TexIndex));

                glClear(GL_COLOR_BUFFER_BIT);
                
            

            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(0.1f, 0.1f);

            glDrawElements(GL_TRIANGLES, combinedIndices.size(), GL_UNSIGNED_INT, 0);
            glDisable(GL_POLYGON_OFFSET_FILL);

            ImGui::SetNextWindowPos(ImVec2(1010, 20));
            ImGui::SetNextWindowSize(ImVec2(190, 300));
            ImGui::Begin("Podglad 3D", &x, ImGuiWindowFlags_NoSavedSettings);
            
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
            }

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);
            if (ImGui::Button("Dodaj kolejna szafke"))
            {   
                if (!newStructureFlag) {
                    newStructureFlag = true;
                    manager.AddNewWardrobe();
                    manager.GetCurrentWardrobe().SetWardrobeType(1);
                    converterManager.AddNewConverter();
                    structureManager.AddNewStructure(converterManager.GetCurrentConverter(), manager.GetCurrentWardrobe());
                    structureManager.ShowStructureHitBoxes();
                }
            }

            if (ImGui::Button("Wyeksportuj projekt"))
            {
                Exporter::ExportToCSV(converterManager);
            }

            InputHandler::HandleRightDoubleClick(
                window,
                camera,
                structureManager,
                sceneSelector,
                newStructureFlag,
                settings
            );

       

            if (!Ortega_GUI.GetIO().WantCaptureMouse)
            {
                camera.Inputs(window);
                camera.Matrix(45.0f, 0.1f, 100000.0f, shaderProgram, "camMatrix");
            }

            ImGui::End();
        }

        settings.RepairWindow();
        Ortega_GUI.Calc(settings);
        Ortega_GUI.HoldEvents(window);

        if (window)
        {
            Ortega_GUI.Exit(settings, VBO1, VAO1, EBO1, shaderProgram, projectTexture, window);
        }
    }

    Ortega_GUI.Shutdown();
    glfwTerminate();
    return 0;
}
