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

bool SceneSelector::CheckRayHit(const glm::vec3& rayOrigin,
    const glm::vec3& rayDir,
    const Structure& structure) {
    // Najpierw sprawdŸ AABB (szybki test wstêpny)
    if (!RayIntersectsAABB(rayOrigin, rayDir, structure.HitboxMin, structure.HitboxMax))
        return false;

    // Jeœli potrzebujesz dok³adniejszego testu na siatce trójk¹tów:
    // return CheckRayTriangleIntersection(rayOrigin, rayDir, structure.HitboxVertices);

    return true; // Tylko test AABB
}

bool SceneSelector::IsNewPositionSelected(glm::vec3 position)
{
    glm::vec3 basePosition = glm::vec3(0.0f);
    if (position == basePosition)
        return false;
    return true;
}

glm::vec3 SceneSelector::CalculatePlacementOnFace(const glm::vec3& minBox, const glm::vec3& maxBox, const glm::vec3& rayDir, Structure& newStructure)
{
    // Oblicz szerokoœæ (X) i g³êbokoœæ (Z) obiektu
    float width = maxBox.x - minBox.x;
    float depth = maxBox.z - minBox.z;
    float newX;
    if (rayDir.x > 0)
    {
        newStructure.SetDrawDirection("right");
        newX = maxBox.x;
    }

    else
    {
        newStructure.SetDrawDirection("left");
        newX = minBox.x;
    }

    // Zachowujemy Y i Z takie same jak poprzedni obiekt
    return glm::vec3(
        newX,
        minBox.y,  // lub maxBox.y, jeœli chcesz wyrównaæ do górnej krawêdzi
        minBox.z    // lub (minBox.z + maxBox.z) / 2.0f, jeœli chcesz wycentrowaæ
    );
}


