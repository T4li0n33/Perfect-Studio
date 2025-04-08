#include "WardrobeManager.h"

void WardrobeManager::AddNewWardrobe() {
    wardrobes.emplace_back(Wardrobe()); // Dodaje now� pust� szafk�
    currentIndex = wardrobes.size() - 1; // Ustawia indeks na now� szafk�
}

void WardrobeManager::ResetCurrentWardrobe() {
    if (currentIndex >= 0 && currentIndex < wardrobes.size()) {
        wardrobes[currentIndex] = Wardrobe(); // Resetuje aktualn� szafk�
    }
}

Wardrobe& WardrobeManager::GetCurrentWardrobe() {
    if (currentIndex >= 0 && currentIndex < wardrobes.size()) {
        return wardrobes[currentIndex];
    }
    throw std::out_of_range("Brak aktualnej szafki!");
}

bool WardrobeManager::HasWardrobes() const {
    return !wardrobes.empty();
}

size_t WardrobeManager::GetWardrobeCount() const {
    return wardrobes.size();
}

Wardrobe& WardrobeManager::GetWardrobeByIndex(int i)
{
    {
        if (i >= 0 && i < static_cast<int>(wardrobes.size()))
        {
            return wardrobes[i];
        }
        throw std::out_of_range("Nieprawid�owy indeks struktury!");
    }
}
