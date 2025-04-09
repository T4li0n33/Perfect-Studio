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
    // Najpierw sprawd� AABB (szybki test wst�pny)
    if (!RayIntersectsAABB(rayOrigin, rayDir, structure.HitboxMin, structure.HitboxMax))
        return false;

    // Je�li potrzebujesz dok�adniejszego testu na siatce tr�jk�t�w:
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

glm::vec3 SceneSelector::CalculatePlacementOnFace(const glm::vec3& minBox, const glm::vec3& maxBox, const glm::vec3& rayDir)
{
    float width = maxBox.x - minBox.x;
    float depth = maxBox.z - minBox.z;

    // Kierunek promienia okre�la stron�
    bool placeOnRight = (rayDir.x > 0);

    float offset = width; // u�ywamy szeroko�ci istniej�cej szafki jako przesuni�cia

    float newX = placeOnRight ? maxBox.x + offset : minBox.x - offset;

    return glm::vec3(
        newX,
        minBox.y - 0.18f, // wysoko�� mo�na wyr�wna� do w�asnych potrzeb
        (minBox.z + maxBox.z) / 2.0f // centrowanie w osi Z
    );
}

PlacementDirection SceneSelector::GetPlacementDirection(const glm::vec3& rayDir)
{
    return (rayDir.x > 0) ? PlacementDirection::Right : PlacementDirection::Left;
}


