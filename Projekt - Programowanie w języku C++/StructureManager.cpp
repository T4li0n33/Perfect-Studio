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

std::vector<std::reference_wrapper<Structure::Vertex>> StructureManager::CollectVertices()
{
    std::vector<std::reference_wrapper<Structure::Vertex>> temp;
    for (auto& structure : structures)
    {
        for (auto& vertex : structure.Vertices)
        {
            temp.emplace_back(vertex); // Dodaj referencjê do oryginalnego wierzcho³ka
        }
    }
    return temp;
}

void StructureManager::UpdateStructurePosition(glm::vec3 newposition)
{
    Structure& structure = GetCurrentStructure();
    structure.SetStructureBasePosition(newposition);
}

void StructureManager::ShowStructureHitBoxes()
{
    auto allVertices = CollectVertices();
    std::vector<std::reference_wrapper<Structure::Vertex>> allVerticesToColor;
    std::vector<std::reference_wrapper<Structure::Vertex>> kVertices;

    // Separate "K" vertices and other vertices ("S")
    for (auto& vertexRef : allVertices)
    {
        if (vertexRef.get().Elem_ID == "K")
        {
            kVertices.push_back(vertexRef);
        }
        else if (vertexRef.get().Elem_ID == "S")
        {
            allVerticesToColor.push_back(vertexRef);
        }
    }

    // Sort regular vertices by Position.x
    std::sort(
        allVerticesToColor.begin(),
        allVerticesToColor.end(),
        [](const auto& a, const auto& b) {
            return a.get().Position.x < b.get().Position.x;
        }
    );

    // Sort K vertices by Position.x
    std::sort(
        kVertices.begin(),
        kVertices.end(),
        [](const auto& a, const auto& b) {
            return a.get().Position.x < b.get().Position.x;
        }
    );

    // Create final vector with K vertices at both ends
    std::vector<std::reference_wrapper<Structure::Vertex>> finalVertices;

    // Add first 24 K vertices (or all if less than 24)
    size_t kCount = std::min(kVertices.size(), static_cast<size_t>(24));
    finalVertices.insert(finalVertices.end(), kVertices.begin(), kVertices.begin() + kCount);

    // Add all sorted S vertices
    finalVertices.insert(finalVertices.end(), allVerticesToColor.begin(), allVerticesToColor.end());

    // Add last 24 K vertices (or all if less than 24)
    if (kVertices.size() > 24) {
        finalVertices.insert(finalVertices.end(), kVertices.end() - 24, kVertices.end());
    }

    // Color the first 24 elements (prioritizing K vertices)
    for (int i = 0; i < 24 && i < finalVertices.size(); i++)
    {
        auto& vertex = finalVertices[i].get();
        vertex.Color.x = 0.0f;
        vertex.Color.y = 1.0f;
        vertex.Color.z = 0.0f;
    }

    // Color the last 24 elements (prioritizing K vertices)
    for (size_t i = (finalVertices.size() >= 24) ? finalVertices.size() - 24 : 0;
        i < finalVertices.size(); i++)
    {
        auto& vertex = finalVertices[i].get();
        vertex.Color.x = 0.0f;
        vertex.Color.y = 1.0f;
        vertex.Color.z = 0.0f;
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
