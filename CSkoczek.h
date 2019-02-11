#ifndef CSKOCZEK_H
#define CSKOCZEK_H
#include "CFigura.h"

/**
 * @brief The CSkoczek class
 *Klasa figury Skoczek
 */
class CSkoczek : public CFigura
{
public:
    /**
     * @brief CSkoczek
     * @param kolor
     */
    CSkoczek(char kolor);
    ~CSkoczek();
private:

    /**
     * @brief figureSign
     *Funkcja przypisująca znak dla Królowej
     * @return Znak 'S'
     */
    virtual char figureSign();

    /**
     * @brief move
     * Funkcja wprowadzająca algorytm ruchu dla Skoczka
     * @param poczRow   Współrzędna wierszu figury
     * @param poczCol    Współrzędna kolumny figury
     * @param docRow    Współrzędna wierszu celu
     * @param docCol     Współrzędna kolumny celu
     * @param szachownica   Szachownica na której odbywa się rzeczywista gra
     * @return Wartość logiczna czy dany ruch jest możliwy
     */
    bool move(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8],int tour);
    bool getDoubleFieldMove();
    void setDoubleFieldMove(bool a);
};

#endif // CSKOCZEK_H
