// WardrobeManager.h
#ifndef WARDROBE_MANAGER_H
#define WARDROBE_MANAGER_H
#include <vector>
#include <stdexcept>
#include "Wardrobe.h"  // Zak³adaj¹c, ¿e klasa Wardrobe jest zdefiniowana w tym pliku

class WardrobeManager {
private:
    std::vector<Wardrobe> wardrobes;  // Lista szafek
    int currentIndex = -1;            // Indeks aktualnie edytowanej szafki

public:
    /**
     * @brief Dodaje now¹, pust¹ szafkê do zarz¹dzania
     */
    void AddNewWardrobe();

    /**
     * @brief Resetuje aktualnie wybran¹ szafkê do stanu pocz¹tkowego
     */
    void ResetCurrentWardrobe();

    /**
     * @brief Zwraca referencjê do aktualnie edytowanej szafki
     * @return Wardrobe& Referencja do aktualnej szafki
     * @throws std::out_of_range Jeœli nie ma aktualnie wybranej szafki
     */
    Wardrobe& GetCurrentWardrobe();

    /**
     * @brief Sprawdza, czy manager posiada jakieœ szafki
     * @return true Jeœli istnieje przynajmniej jedna szafka
     * @return false Jeœli nie ma ¿adnych szafek
     */
    bool HasWardrobes() const;

    /**
     * @brief Zwraca liczbê szafek pod zarz¹dzaniem
     * @return size_t Liczba szafek
     */
    size_t GetWardrobeCount() const;

    Wardrobe& GetWardrobeByIndex(int i);

};

#endif // WARDROBE_MANAGER_H