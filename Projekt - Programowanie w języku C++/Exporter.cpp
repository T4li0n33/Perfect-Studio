#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define NOCRYPT

#ifdef byte
#undef byte
#endif


#include "Exporter.h"
#include <windows.h>
#include <commdlg.h>
#include <fstream>
#include <map>
#include <tuple>
#include <algorithm>

void Exporter::ExportToCSV(ConverterManager& manager) {
    std::string filename = ShowSaveFileDialog();
    if (filename.empty()) return;  // anulowano

    using Key = std::tuple<float, float, std::vector<std::string>>;
    std::map<Key, int> elementCounts;

    auto normalize = [](float a, float b, float c) -> std::pair<float, float> {
        std::vector<float> dims = { a, b, c };
        std::sort(dims.begin(), dims.end(), std::greater<float>());
        return { dims[0], dims[1] };
        };

    for (const auto& conv : manager.GetAllConverters()) {
        for (const auto& elem : conv.Elements_vector) {
            auto [length, width] = normalize(elem.x, elem.y, elem.z);
            Key key = std::make_tuple(length, width, elem.veneer);
            ++elementCounts[key];
        }
    }

    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Nie mo¿na otworzyæ pliku CSV do zapisu.");

    file << "Dlugosc,Szerokosc,Ilosc,Oklejanie_DL1,Oklejanie_DL2,Oklejanie_SZ1,Oklejanie_SZ2\n";

    for (const auto& [key, count] : elementCounts) {
        auto [length, width, veneer] = key;
        auto toFlag = [](const std::string& v) {
            return v.empty() ? "" : "1";
            };

        file << length << "," << width << "," << count << ",";
        file << toFlag(veneer.size() > 0 ? veneer[0] : "") << ",";
        file << toFlag(veneer.size() > 1 ? veneer[1] : "") << ",";
        file << toFlag(veneer.size() > 2 ? veneer[2] : "") << ",";
        file << toFlag(veneer.size() > 3 ? veneer[3] : "") << "\n";
    }

    file.close();
}


std::string Exporter::ShowSaveFileDialog() {
    char filename[MAX_PATH] = "";

    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = "Pliki CSV\0*.csv\0Wszystkie pliki\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "csv";
    ofn.lpstrTitle = "Zapisz jako";

    if (GetSaveFileNameA(&ofn)) {
        return std::string(filename);
    }
    return ""; // u¿ytkownik anulowa³
}