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
