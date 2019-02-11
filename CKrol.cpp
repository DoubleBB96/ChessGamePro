#include "CKrol.h"
#include "CFigura.h"



    CKrol::CKrol(char kolor) : CFigura(kolor, "King") {}
    CKrol::~CKrol() {}

    char CKrol::figureSign()
    {
        return 'K';
    }
    bool CKrol::move(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8], int tour)
    {
        int rowDif = docRow - poczRow;
        int colDif = docCol - poczCol;

        int diff = (docCol - poczCol>0) ? 1 : -1;

        if ((abs(rowDif) <= 1) && (abs(colDif) <= 1))
            return true;
        else if(szachownica[poczRow][poczCol]->getMoveAmount() == 0 && abs(poczCol - docCol) == 2 && docRow == poczRow)
        {
                for(int j = poczCol + diff; j != docCol; j += diff )
                {
                    if(szachownica[poczRow][j] != 0)
                        return false;
                }

                if((szachownica[poczRow][docCol + 1] != 0 && szachownica[poczRow][docCol + 1]->figureSign() == 'W' && szachownica[poczRow][docCol + 1]->getMoveAmount() == 0) ||
                        (szachownica[poczRow][docCol - 2] != 0 && szachownica[poczRow][docCol - 2]->figureSign() == 'W' && szachownica[poczRow][docCol - 2]->getMoveAmount() == 0 && szachownica[poczRow][docCol - 1] == 0))
                    return true;

                return false;

        }

        return false;
    }

    bool CKrol::getDoubleFieldMove()
    {
        return doubleFieldMove;
    }

    void CKrol::setDoubleFieldMove(bool a)
    {
        doubleFieldMove = a;
    }
