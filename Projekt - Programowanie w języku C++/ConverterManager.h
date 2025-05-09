#ifndef CONVERTER_MANAGER_H
#define CONVERTER_MANAGER_H

#include "Converter.h"
#include <vector>
#include <stdexcept>

class ConverterManager {
private:
    std::vector<Converter> converters;
    size_t currentIndex = 0;

public:
    void AddNewConverter();
    Converter& GetCurrentConverter();
    Converter& GetConverterByIndex(int i);
    std::vector<Converter> GetAllConverters();
};

#endif 