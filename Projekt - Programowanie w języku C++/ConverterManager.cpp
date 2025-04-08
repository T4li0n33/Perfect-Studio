#include "ConverterManager.h"

void ConverterManager::AddNewConverter() {
    converters.emplace_back(Converter());
    currentIndex = converters.size() - 1;
}

Converter& ConverterManager::GetCurrentConverter() {
    if (currentIndex < converters.size()) {
        return converters[currentIndex];
    }
    throw std::out_of_range("Brak aktualnego konwertera!");
}
