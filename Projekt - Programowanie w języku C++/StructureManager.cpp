#include "StructureManager.h"

void StructureManager::AddNewStructure(Converter& converter, Wardrobe& wardrobe) {
    structures.emplace_back(Structure(converter, wardrobe));
    currentIndex = structures.size() - 1;
}

Structure& StructureManager::GetCurrentStructure() {
    if (currentIndex < structures.size()) {
        return structures[currentIndex];
    }
    throw std::out_of_range("Brak aktualnej struktury!");
}

void StructureManager::UpdateCurrentStructure(Converter& converter, Wardrobe& wardrobe) {
    if (currentIndex < structures.size()) {
        structures[currentIndex] = Structure(converter, wardrobe);
    }
}

int StructureManager::GetTotalStructures()
{
    return structures.size();
}

void StructureManager::CollectCombinedBufferData(std::vector<Structure::Vertex>& outVertices, std::vector<GLuint>& outIndices)
{
    size_t vertexOffset = 0;
    for (auto& structure : structures)
    {
        const auto& verts = structure.Vertices;
        const auto& indices = structure.GetCuboidIndices();

        // Add Vertices
        outVertices.insert(outVertices.end(), verts.begin(), verts.end());

        // Dodaj Indices with offsets
        for (GLuint idx : indices)
            outIndices.push_back(idx + static_cast<GLuint>(vertexOffset));

        vertexOffset += verts.size();
    }
}

void StructureManager::UpdateStructurePosition(glm::vec3 newposition)
{
    Structure& structure = GetCurrentStructure();
    structure.SetStructureBasePosition(newposition);
}

void StructureManager::ShowStructureHitBoxes()
{
    for (int i = 0; i < GetTotalStructures(); i++)
    {
        structures.at(i).ShowHitboxes();
    }
}

void StructureManager::HideStructureHitBoxes()
{
    for (int i = 0; i < GetTotalStructures(); i++)
    {
        structures.at(i).HideHitboxes();
    }
}

Structure& StructureManager::GetStructureByIndex(int i)
{
    if (i >= 0 && i < static_cast<int>(structures.size()))
    {
        return structures[i];
    }
    throw std::out_of_range("Nieprawid³owy indeks struktury!");
}
