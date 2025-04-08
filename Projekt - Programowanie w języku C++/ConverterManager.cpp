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

Converter& ConverterManager::GetConverterByIndex(int i)
{
    {
        if (i >= 0 && i < static_cast<int>(converters.size()))
        {
            return converters[i];
        }
        throw std::out_of_range("Nieprawid³owy indeks struktury!");
    }
}
