#ifndef STRUCTURE_MANAGER_H
#define STRUCTURE_MANAGER_H

#include "DrawFunctions.h"
#include "Wardrobe.h"
#include "Converter.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <set>
class StructureManager {
private:
    std::vector<Structure> structures;
    size_t currentIndex = 0;

public:
    void AddNewStructure(Converter& converter, Wardrobe& wardrobe);
    Structure& GetCurrentStructure();
    void UpdateCurrentStructure(Converter& converter, Wardrobe& wardrobe);
    int GetTotalStructures();
    void GenerateGlobalIndices();
    void CollectCombinedBufferData(std::vector<Structure::Vertex>& outVertices, std::vector<GLuint>& outIndices);
    std::vector<std::reference_wrapper<Structure::Vertex>> CollectVertices();
    void UpdateStructurePosition(glm::vec3 newposition);
    void ShowStructureHitBoxes();
    void HideStructureHitBoxes();
    Structure& GetStructureByIndex(int i);
};

#endif
