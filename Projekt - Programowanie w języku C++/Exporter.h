#pragma once

#include "ConverterManager.h"
#include <string>


class Exporter {
public:
    static void ExportToCSV(ConverterManager& manager);
    static std::string ShowSaveFileDialog();
};
