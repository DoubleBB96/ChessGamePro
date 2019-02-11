#include "CSkoczek.h"
#include "CFigura.h"



    CSkoczek::CSkoczek(char kolor) : CFigura(kolor, "Bishop") {}
    CSkoczek::~CSkoczek() {}

    char CSkoczek::figureSign()
    {
        return 'S';
    }
    bool CSkoczek::move(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8], int tour)
    {
        if( abs(poczRow - docRow) == abs(poczCol - docCol))
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

    bool CSkoczek::getDoubleFieldMove()
    {
        return false;
    }

    void CSkoczek::setDoubleFieldMove(bool a)
    {
    }
