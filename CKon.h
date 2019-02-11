#ifndef CKON_H
#define CKON_H
#include "CFigura.h"

/**
 * @brief The CKon class
 * Klasa figury Koń
 */
class CKon : public CFigura
{
public:
    /**
     * @brief CKon
     * Konstruktor klasy
     * @param kolor Kolor danego Konia
     */
    CKon(char kolor);
    ~CKon();
private:
    /**
     * @brief figureSign
     * Funkcja przypisująca znak dla Konia
     * @return Znak 'H'
     */
    virtual char figureSign();

    /**
     * @brief move
     * Funkcja wprowadzająca algorytm ruchu dla Konia
     * @param poczRow   Współrzędna wierszu figury
     * @param poczCol    Współrzędna kolumny figury
     * @param docRow    Współrzędna wierszu celu
     * @param docCol     Współrzędna kolumny celu
     * @param szachownica   Szachownica na której odbywa się rzeczywista gra
     * @return Wartość logiczna czy dany ruch jest możliwy
     */
    bool move(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8], int tour);
    bool getDoubleFieldMove();
    void setDoubleFieldMove(bool a);
};

#endif // CKON_H
