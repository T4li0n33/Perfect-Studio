#include "SceneSelector.h"

bool SceneSelector::RayIntersectsAABB(const glm::vec3& rayOrigin,const glm::vec3& rayDir,const glm::vec3& min,const glm::vec3& max)
{ 
    float tmin = 0.0f; float tmax = std::numeric_limits<float>::max();

    for (int i = 0; i < 3; ++i) {
        if (std::abs(rayDir[i]) < 1e-6) {
           
            if (rayOrigin[i] < min[i] || rayOrigin[i] > max[i])
                return false;
        }
        else {
            float invDir = 1.0f / rayDir[i];
            float t1 = (min[i] - rayOrigin[i]) * invDir;
            float t2 = (max[i] - rayOrigin[i]) * invDir;

            if (t1 > t2) std::swap(t1, t2);
            tmin = std::max(tmin, t1);
            tmax = std::min(tmax, t2);

            if (tmax < tmin)
                return false;
        }
    }
    return true;
}

void SceneSelector::GetAABB(const Structure& s, glm::vec3& outMin, glm::vec3& outMax)
{
    bool found = false;
    glm::vec3 min;
    glm::vec3 max;

    for (const auto& v : s.Vertices)
    {
        if (v.Elem_ID && strcmp(v.Elem_ID, "S") == 0)
        {
            if (!found)
            {
                min = max = v.Position;
                found = true;
            }
            else
            {
                min = glm::min(min, v.Position);
                max = glm::max(max, v.Position);
            }
        }
    }

    if (!found)
    {
        outMin = glm::vec3(0.0f);
        outMax = glm::vec3(0.0f);
        return;
    }

    outMin = min;
    outMax = max;
}

bool SceneSelector::CheckRayHit(
    const glm::vec3& rayOrigin,
    const glm::vec3& rayDir,
    Structure& structure,
    RayHitInfo* outHitInfo, std::vector<Structure::Vertex>& globalVertices)  // Dodaj opcjonalny parametr
{
    if (!RayIntersectsAABB(rayOrigin, rayDir, structure.HitboxMin, structure.HitboxMax))
        return false;

    // Pe³ny test – trójk¹ty
    return CheckRayTriangleIntersection(rayOrigin, rayDir, structure, globalVertices, outHitInfo);
}


bool SceneSelector::CheckRayTriangleIntersection(
    const glm::vec3& rayOrigin,
    const glm::vec3& rayDir,
    Structure& structure, std::vector<Structure::Vertex>& globalVertices,
    RayHitInfo* outHitInfo)
{
    float closestT = std::numeric_limits<float>::max();
    bool hit = false;

    for (const auto& elem : structure.ElementVector) {
        bool allVerticesHitAvailable = true;
        for (const auto& index : elem.Indices) {
            if (index >= globalVertices.size() || !globalVertices[index].HitAvailable) {
                allVerticesHitAvailable = false;
                break;
            }
        }
        if (!allVerticesHitAvailable) {
            continue; // Pomijamy element, jeœli którykolwiek wierzcho³ek nie mo¿e byæ trafiony
        }

        const auto& inds = elem.Indices;

        if (inds.empty() || inds.size() % 3 != 0) {
            std::cerr << "B³¹d: nieprawid³owa liczba indeksów w elemencie!" << std::endl;
            continue;
        }

        for (size_t i = 0; i + 2 < inds.size(); i += 3) {
            // SprawdŸ, czy indeksy nie wykraczaj¹ poza zakres GLOBALNEJ tablicy
            if (inds[i] >= globalVertices.size() ||
                inds[i + 1] >= globalVertices.size() ||
                inds[i + 2] >= globalVertices.size())
            {
                std::cerr << "Ostrze¿enie: indeks wykracza poza globaln¹ tablicê wierzcho³ków. Pomijanie trójk¹ta." << std::endl;
                continue;
            }

            const Structure::Vertex& vert0 = globalVertices[inds[i]];
            const Structure::Vertex& vert1 = globalVertices[inds[i + 1]];
            const Structure::Vertex& vert2 = globalVertices[inds[i + 2]];

            const glm::vec3& v0 = vert0.Position;
            const glm::vec3& v1 = vert1.Position;
            const glm::vec3& v2 = vert2.Position;

            glm::vec3 edge1 = v1 - v0;
            glm::vec3 edge2 = v2 - v0;
            glm::vec3 h = glm::cross(rayDir, edge2);
            float a = glm::dot(edge1, h);

            if (std::fabs(a) < 1e-6f)
                continue;

            float f = 1.0f / a;
            glm::vec3 s = rayOrigin - v0;
            float u = f * glm::dot(s, h);
            if (u < 0.0f || u > 1.0f)
                continue;

            glm::vec3 q = glm::cross(s, edge1);
            float v = f * glm::dot(rayDir, q);
            if (v < 0.0f || u + v > 1.0f)
                continue;

            float t = f * glm::dot(edge2, q);
            if (t > 1e-6f && t < closestT) {
                closestT = t;
                hit = true;

                if (outHitInfo) {
                    outHitInfo->ElemID = vert0.Elem_ID;
                    outHitInfo->Normal = glm::normalize(glm::cross(edge1, edge2));
                    outHitInfo->HitPoint = rayOrigin + rayDir * t;
                }
            }
        }
    }

    return hit;
}



bool SceneSelector::IsNewPositionSelected(glm::vec3 position)
{
    glm::vec3 basePosition = glm::vec3(0.0f);
    if (position == basePosition)
        return false;
    return true;
}

glm::vec3 SceneSelector::CalculatePlacementOnFace(const glm::vec3& minBox, const glm::vec3& maxBox,const glm::vec3& rayDir, const char* FatherStructureRotation,
    Structure& newStructure, const RayHitInfo& hitInfo)
{
    float width = maxBox.x - minBox.x;
    float depth = maxBox.z - minBox.z;
    float newX;

    if (hitInfo.ElemID == "K") {
        // Trafiliœmy naro¿nik
        if (rayDir.x > 0)
        {
            newStructure.SetDrawDirection("corner_right");
            newStructure.SetStructureRotation(FatherStructureRotation);
        }      
        else
        {
            newStructure.SetDrawDirection("corner_left");
            newStructure.SetStructureRotation(FatherStructureRotation);
        }
            

        // Dopasuj pozycjê – np. z prawej strony naro¿nika
        newX = rayDir.x > 0 ? maxBox.x : minBox.x;
    }
    else {
        // Domyœlna logika – element "S"
        if (rayDir.x > 0) {
            newStructure.SetDrawDirection("right");
            newStructure.SetStructureRotation(FatherStructureRotation);
            newX = maxBox.x;
        }
        else {
            newStructure.SetDrawDirection("left");
            newStructure.SetStructureRotation(FatherStructureRotation);
            newX = minBox.x;
        }
    }

    return glm::vec3(
        newX,
        minBox.y,
        minBox.z // lub centrowanie jak chcesz
    );
}



