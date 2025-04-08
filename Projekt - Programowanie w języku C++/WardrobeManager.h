// WardrobeManager.h
#ifndef WARDROBE_MANAGER_H
#define WARDROBE_MANAGER_H
#include <vector>
#include <stdexcept>
#include "Wardrobe.h"  // Zak�adaj�c, �e klasa Wardrobe jest zdefiniowana w tym pliku

class WardrobeManager {
private:
    std::vector<Wardrobe> wardrobes;  // Lista szafek
    int currentIndex = -1;            // Indeks aktualnie edytowanej szafki

public:
    /**
     * @brief Dodaje now�, pust� szafk� do zarz�dzania
     */
    void AddNewWardrobe();

    /**
     * @brief Resetuje aktualnie wybran� szafk� do stanu pocz�tkowego
     */
    void ResetCurrentWardrobe();

    /**
     * @brief Zwraca referencj� do aktualnie edytowanej szafki
     * @return Wardrobe& Referencja do aktualnej szafki
     * @throws std::out_of_range Je�li nie ma aktualnie wybranej szafki
     */
    Wardrobe& GetCurrentWardrobe();

    /**
     * @brief Sprawdza, czy manager posiada jakie� szafki
     * @return true Je�li istnieje przynajmniej jedna szafka
     * @return false Je�li nie ma �adnych szafek
     */
    bool HasWardrobes() const;

    /**
     * @brief Zwraca liczb� szafek pod zarz�dzaniem
     * @return size_t Liczba szafek
     */
    size_t GetWardrobeCount() const;

    Wardrobe& GetWardrobeByIndex(int i);

};

#endif // WARDROBE_MANAGER_H