#include "InputHandler.h"

void InputHandler::HandleRightDoubleClick(
    GLFWwindow* window,
    Camera& camera,
    StructureManager& structureManager,
    SceneSelector& sceneSelector,
    bool& newStructureFlag,
    Settings& settings)
{
    static double lastClickTime = 0.0;
    double currentTime = glfwGetTime();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (currentTime - lastClickTime < 0.3) // dwuklik w <300ms
        {
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            glm::vec3 rayDir = camera.GetRayDirection(mouseX, mouseY);
            glm::vec3 rayOrigin = camera.Position;

            for (size_t i = 0; i < structureManager.GetTotalStructures(); ++i)
            {
                Structure& structure = structureManager.GetStructureByIndex(i);

                std::cout << structure.GetMaxQuadCount();
                if (sceneSelector.CheckRayHit(rayOrigin, rayDir, structure))
                {
                    glm::vec3 newPos = sceneSelector.CalculatePlacementOnFace(
                        structure.HitboxMin,
                        structure.HitboxMax,
                        rayDir,
                        structureManager.GetCurrentStructure());

                    structureManager.UpdateStructurePosition(newPos);

                    bool lokalna = newPos != glm::vec3(0.0f);

                    if (lokalna)
                    {
                        structureManager.HideStructureHitBoxes();
                        newStructureFlag = false;
                        settings.SetMode(3);
                        settings.SetWindow(2);
                        ImGui::SetNextWindowCollapsed(false);
                        ImGui::Begin("Tryb Projektowy");
                        ImGui::End();
                    }
                    break;
                }
            }
        }
        lastClickTime = currentTime;
    }
}