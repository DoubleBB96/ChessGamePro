#include "CPion.h"
#include "CFigura.h"
#include <QDebug>



    CPion::CPion(char kolor) : CFigura(kolor, "Pawn") {}  //konstruktor nadający kolor
    CPion::~CPion() {}

    char CPion::figureSign() //Znak w konsoli , w GUI będzie to grafika dla danej figury
    {
        return 'P';
    }
    bool CPion::move(int poczRow, int poczCol, int docRow, int docCol, CFigura *szachownica[8][8], int tour) {   // ruch (współrzędne początka i końca ruchu oraz wskaźnik do planszy)czy ruch moze zostac wykonany

        CFigura *aim = szachownica[docRow][docCol];                  //potrzebny nam cel ponieważ ruch przy biciu piona rózni się od jego ruchu podstawowego

        int rowDif = (docRow - poczRow > 0) ? 1 : -1;


        if (aim == 0)
        {                                             // Cel nie jest zajety przez pionek przeciwnego koloru

            if (poczCol == docCol)                            // pion porusza sie wzdłuż kolumny
            {
                if (setColor() == 'B')
                {
                    if ((docRow == poczRow-1))
                    {
                        for(int i = poczRow + rowDif; i != docRow; i += rowDif)
                        {
                            if(szachownica[i][poczCol] != 0)
                            {
                                return false;
                            }
                        }
                       return true;

                    }else if(poczRow==6 && (docRow == poczRow-2))
                    {
                        for(int i = poczRow + rowDif; i != docRow; i += rowDif)
                        {
                            if(szachownica[i][poczCol] != 0)
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
                else
                {
                    if ((docRow == poczRow +1))
                    {
                        for(int i = poczRow + rowDif; i != docRow; i += rowDif)
                        {
                            if(szachownica[i][poczCol] != 0)
                                return false;
                        }
                        return true;

                    }else if((poczRow==1 && (docRow == poczRow +2)))
                    {
                        for(int i = poczRow + rowDif; i != docRow; i += rowDif)
                        {
                            if(szachownica[i][poczCol] != 0)
                                return false;
                        }

                        return true;
                    }
                }

            }else if ((poczCol == docCol + 1) || (poczCol == docCol - 1))  //bicie w przelocie
            {
                if(setColor() == 'B')
                {
                    if (docRow == poczRow - 1)
                    {

                        if(szachownica[poczRow][docCol] != 0 && szachownica[poczRow][docCol]->figureSign() == 'P' && szachownica[poczRow][docCol]->setColor() == 'C'     //jezeli obok znajduje sie pion przeciwnika
                                && szachownica[poczRow][docCol]->getDoubleFieldMove() == true)                                                                                                                    // i ruszyl sie o dwa pola
                        {
                            if(tour - szachownica[poczRow][docCol]->getDoubleMoveTour() == 1)                                                  // w poprzedniej rundzie
                                return true;
                        }


                    }
                }else
                {
                    if (docRow == poczRow + 1)
                    {
                        if(szachownica[poczRow][docCol] != 0 && szachownica[poczRow][docCol]->figureSign() == 'P' && szachownica[poczRow][docCol]->setColor() == 'B'
                                && szachownica[poczRow][docCol]->getDoubleFieldMove() == true)
                        {
                            if(tour - szachownica[poczRow][docCol]->getDoubleMoveTour() == 1)
                                return true;
                        }
                    }
                }
            }
        }
        else if(aim != 0)                                                               //bicie
        {
            if ((poczCol == docCol + 1) || (poczCol == docCol - 1))                 //bicie normalne
            {
                if (setColor() == 'B')
                {
                     if (docRow == poczRow -1)                                 //realizacja bicia po skosie (w dół planszy) (zmiana wiersza) (kol. + wier. - ruch po skosie)
                              return true;

                } else                                //realizacja bicia po skosie (w góre planszy)
                {
                    if (docRow == poczRow + 1)
                             return true;
                }
            }

         }
        return false;

}

    bool CPion::getDoubleFieldMove()
    {
        return doubleFieldMove;
    }

    void CPion::setDoubleFieldMove(bool a)
    {
        doubleFieldMove = a;
    }

