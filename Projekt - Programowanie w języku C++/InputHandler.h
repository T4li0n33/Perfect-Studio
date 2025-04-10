#pragma once

#include "Camera.h"
#include "StructureManager.h"
#include "SceneSelector.h"
#include "Settings.h"
#include "imgui.h"
#include <iostream>

class InputHandler {
public:
    static void HandleRightDoubleClick(
        GLFWwindow* window,
        Camera& camera,
        StructureManager& structureManager,
        SceneSelector& sceneSelector,
        bool& newStructureFlag,
        Settings& settings
    );
};