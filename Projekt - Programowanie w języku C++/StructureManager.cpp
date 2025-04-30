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

void StructureManager::GenerateGlobalIndices()
{
    GLuint globalVertexOffset = 0;

    for (auto& structure : structures)
    {
        for (auto& element : structure.ElementVector)
        {
            element.Indices.clear();
            element.Indices.reserve(36); // 6 ścian * 2 trójkąty * 3 wierzchołki

            static const GLuint baseIndices[36] = {
                0, 1, 2, 2, 3, 0,     // Bottom
                4, 5, 6, 6, 7, 4,     // Top
                8, 9,10,10,11, 8,     // Front
               12,13,14,14,15,12,     // Back
               16,17,18,18,19,16,     // Left
               20,21,22,22,23,20      // Right
            };

            for (int i = 0; i < 36; ++i)
            {
                element.Indices.push_back(baseIndices[i] + globalVertexOffset);
            }

            globalVertexOffset += static_cast<GLuint>(element.Vertices.size());
        }
    }
}


void StructureManager::CollectCombinedBufferData(std::vector<Structure::Vertex>& outVertices, std::vector<GLuint>& outIndices)
{
    size_t vertexOffset = 0;

    for (auto& structure : structures)
    {
        for (const auto& element : structure.ElementVector)
        {
            // Dodaj wierzchołki danego elementu
            outVertices.insert(outVertices.end(), element.Vertices.begin(), element.Vertices.end());

            for (GLuint index : element.Indices)
            {
                outIndices.push_back(index);
            }

            vertexOffset += static_cast<GLuint>(element.Vertices.size());
        }
    }
}


std::vector<std::reference_wrapper<Structure::Vertex>> StructureManager::CollectVertices()
{
    std::vector<std::reference_wrapper<Structure::Vertex>> temp;
    for (auto& structure : structures)
    {
        for (auto& vertex : structure.Vertices)
        {
            temp.emplace_back(vertex); // Dodaj referencję do oryginalnego wierzchołka
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
    struct ElemRef {
        Structure::ElementData* elem;
        float minX;
    };

    std::vector<ElemRef> allElements;

    // Zbierz wszystkie elementy z każdej struktury
    for (auto& structure : structures) {
        for (auto& elem : structure.ElementVector) {
            if (elem.Vertices.empty()) continue;

            // Wylicz minimalne X jako pozycję bazową
            float minX = std::min_element(elem.Vertices.begin(), elem.Vertices.end(),
                [](const auto& a, const auto& b) {
                    return a.Position.x < b.Position.x;
                })->Position.x;

            allElements.push_back({ &elem, minX });
        }
    }

    // Posortuj po X
    std::sort(allElements.begin(), allElements.end(),
        [](const ElemRef& a, const ElemRef& b) {
            return a.minX < b.minX;
        });

    auto takeElemWindow = [&](int fromIndex, int count) {
        std::vector<ElemRef> w;
        int N = (int)allElements.size();
        for (int i = fromIndex; i < fromIndex + count && i < N; ++i)
            w.push_back(allElements[i]);
        return w;
        };

    auto pickInElemWindow = [&](std::vector<ElemRef>& win, const std::string& type) {
        std::vector<ElemRef> fil;
        for (auto& ref : win)
            if (!ref.elem->Vertices.empty() && ref.elem->Vertices.front().Elem_ID == type)
                fil.push_back(ref);
        if (!fil.empty()) return fil;
        return win;
        };

    // ==== LEWE OKNO ====
    auto leftWin = takeElemWindow(0, 3);  // np. 3 elementy po lewej
    bool sharedL = false;
    {
        std::set<std::tuple<float, float, float>> sPos, kPos;
        for (auto& e : leftWin) {
            for (auto& v : e.elem->Vertices) {
                auto t = std::make_tuple(v.Position.x, v.Position.y, v.Position.z);
                if (v.Elem_ID == "S") sPos.insert(t);
                else if (v.Elem_ID == "K") kPos.insert(t);
            }
        }
        for (auto& p : sPos) if (kPos.find(p) != kPos.end()) { sharedL = true; break; }
    }

    auto leftCandidates = pickInElemWindow(leftWin, sharedL ? "K" : "S");
    Structure::ElementData* leftPick = leftCandidates.empty() ? nullptr : leftCandidates.front().elem;

    // ==== PRAWE OKNO ====
    int N = (int)allElements.size();
    auto rightWin = takeElemWindow(std::max(0, N - 3), 3);
    bool sharedR = false;
    {
        std::set<std::tuple<float, float, float>> sPos, kPos;
        for (auto& e : rightWin) {
            for (auto& v : e.elem->Vertices) {
                auto t = std::make_tuple(v.Position.x, v.Position.y, v.Position.z);
                if (v.Elem_ID == "S") sPos.insert(t);
                else if (v.Elem_ID == "K") kPos.insert(t);
            }
        }
        for (auto& p : sPos) if (kPos.find(p) != kPos.end()) { sharedR = true; break; }
    }

    auto rightCandidates = pickInElemWindow(rightWin, sharedR ? "K" : "S");
    Structure::ElementData* rightPick = rightCandidates.empty() ? nullptr : rightCandidates.back().elem;

    // ===== KOLOROWANIE + DEBUG =====
    std::cout << "\n--- ShowStructureHitBoxes Debug ---\n";
    if (leftPick) {
        for (auto& v : leftPick->Vertices) {
            v.Color = { 0, 1, 0 };
            v.HitAvailable = true;
        }
        std::cout << "[LEFT]  " << leftPick->Vertices.front().Elem_ID
            << " Pos(" << leftPick->Vertices.front().Position.x << ","
            << leftPick->Vertices.front().Position.y << ","
            << leftPick->Vertices.front().Position.z << ")\n";
    }
    if (rightPick && rightPick != leftPick) {
        for (auto& v : rightPick->Vertices) {
            v.Color = { 0, 1, 0 };
            v.HitAvailable = true;
        }
        std::cout << "[RIGHT] " << rightPick->Vertices.front().Elem_ID
            << " Pos(" << rightPick->Vertices.front().Position.x << ","
            << rightPick->Vertices.front().Position.y << ","
            << rightPick->Vertices.front().Position.z << ")\n";
    }
    std::cout << "--- Koniec debugowania ---\n\n";
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
    throw std::out_of_range("Nieprawidłowy indeks struktury!");
}
