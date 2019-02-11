#include "CKrolowa.h"
#include "CFigura.h"
#include <cmath>
#include <QDebug>


    CKrolowa::CKrolowa(char kolor) : CFigura(kolor, "Queen") {}
    CKrolowa::~CKrolowa() {}

    char CKrolowa:: figureSign()
    {
        return 'Q';
    }

    bool CKrolowa::move(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8], int tour)
    {
        if (poczRow == docRow)         // realizacja poruszania się wzdłuż wierszy
        {
            int colDif = (docCol - poczCol>0) ? 1 : -1;

            for (int j = poczCol + colDif; j != docCol; j = j + colDif)
            {
                if (szachownica[poczRow][j] != 0) // jezeli cel jest zajety zwraca false
                {
                    return false;
                }
            }
            return true;
        }
        else if (poczCol == docCol)        //realizacja poruszania się wzdłuż kolumn
        {
            int rowDif = (docRow - poczRow>0) ? 1 : -1;    //jeżeli ruch w dół przypisanie RoznicaWierszy=1 jezeli w góre RoznicaWierszy=-1
            for (int i = poczRow + rowDif; i != docRow; i = i + rowDif)
            {                                                         // sprawdzenie po kolei czy nic nie stoi na drodze
                if (szachownica[i][poczCol] != 0)       //jeżeli cel jest zajęty zwraca false
                {
                    return false;
                }
            }
            return true;

        }else if( abs(poczRow - docRow) == abs(poczCol - docCol))
        {

            int colDif = (docCol - poczCol>0) ? 1 : -1;
            int rowDif = (docRow - poczRow>0) ? 1 : -1;

            int checkCol;
            int checkRow;

            for (checkRow = poczRow + rowDif, checkCol = poczCol + colDif ;
                 checkRow != docRow;
                 checkRow += rowDif, checkCol += colDif)
            {
                if (szachownica[checkRow][checkCol] != 0)
                {
                    return false;
                }
            }
            return true;

        }else

            return false;

}

    bool CKrolowa::getDoubleFieldMove()
    {
        return false;
    }


    void CKrolowa::setDoubleFieldMove(bool a)
    {
    }
