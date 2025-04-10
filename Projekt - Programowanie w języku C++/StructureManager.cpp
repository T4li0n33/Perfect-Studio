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
    auto allVertices = CollectVertices(); // Wektor referencji
    std::vector<std::reference_wrapper<Structure::Vertex>> allVerticesToColor;

    // ZnajdŸ wierzcho³ki z Elem_ID == "S"
    for (auto& vertexRef : allVertices)
    {
        if (vertexRef.get().Elem_ID == "S")
        {
            allVerticesToColor.push_back(vertexRef);
        }
    }

    // Sortuj po Position.x (od najmniejszego do najwiêkszego)
    std::sort(
        allVerticesToColor.begin(),
        allVerticesToColor.end(),
        [](const std::reference_wrapper<Structure::Vertex>& a, const std::reference_wrapper<Structure::Vertex>& b) {
            return a.get().Position.x < b.get().Position.x;
        }
    );

    // Zmieñ kolory tylko w pierwszych 24 wierzcho³kach (najbardziej "lewe")
    for (int i = 0; i < 24 && i < allVerticesToColor.size(); i++)
    {
        auto& vertex = allVerticesToColor[i].get();
        vertex.Color.x = 0.0f;
        vertex.Color.y = 1.0f;
        vertex.Color.z = 0.0f;
    }

    // Zmieñ kolory tylko w ostatnich 24 wierzcho³kach (najbardziej "prawe")
    for (size_t i = (allVerticesToColor.size() >= 24) ? allVerticesToColor.size() - 24 : 0;
        i < allVerticesToColor.size(); i++)
    {
        auto& vertex = allVerticesToColor[i].get();
        vertex.Color.x = 0.0f;
        vertex.Color.y = 1.0f;
        vertex.Color.z = 0.0f;
    }

    auto output = allVerticesToColor; // (jeœli potrzebujesz output)
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
