#include "CPoleSzachownicy.h"
#include <QBrush>
#include <QColor>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <CFigura.h>

const int WYMIAR_POLA = 100; // w pikselach

CPoleSzachownicy::CPoleSzachownicy(int y, int x, QGraphicsItem *parent) :
    QGraphicsRectItem(x * WYMIAR_POLA, y * WYMIAR_POLA, WYMIAR_POLA, WYMIAR_POLA, parent),
    pozycja(x, y)
{
}

CPoleSzachownicy::~CPoleSzachownicy()
{
}

void CPoleSzachownicy::ustawKolor(QColor kolor)   // ustawia kolor danego pola szachownicy (GUI)
{
    this->kolor = kolor;
    setBrush(kolor);
}

void CPoleSzachownicy::ustawFigure(CFigura *f)  //ustawia figura na danym polu szachownicy (GUI)
{
    figura = f;
    scene()->update();
}

CFigura *CPoleSzachownicy::zdejmijFigure()   // zdejmuje figure z danego pola szachownicy i zwraca ją (która figura została zdjęta)
{
    CFigura *ret = figura;
    figura = nullptr;
    scene()->update();
    return ret;
}

CFigura *CPoleSzachownicy::pobierzFigure()  //funkcja pobierająca figurę z danego pola
{
    return figura;
}

int CPoleSzachownicy::pobierzWiersz()        // funkcja zwracająca wiersz
{
    return pozycja.y();
}

int CPoleSzachownicy::pobierzKolumne()       // funkcja zwracająca kolumne
{
    return pozycja.x();
}

QPoint CPoleSzachownicy::pobierzPozycje()     //funkcja zwracająca pozycję danego pola
{
    return pozycja;
}

void CPoleSzachownicy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget); // ????

    if (figura)
    {
        painter->drawPixmap(boundingRect().toAlignedRect(), figura->Obrazek());    //wstawienie obrazka na odpowiednie miejsce ??? co to jest te                       boundingRect().toAlignedRect()
    }
}

void CPoleSzachownicy::mousePressEvent(QGraphicsSceneMouseEvent *)     //funkcja emitująca sygnał, że dane pole szachownicy zostało kliknięte
{
    emit kliknieto(this);
}

void CPoleSzachownicy::ustawWybrane(bool wybrane)      //funkcja zaznaczająca dane pole jako wybrane
{
    this->wybrane = wybrane;
    ustawKolorSpecjalny(wybrane, Qt::darkGreen);
}

bool CPoleSzachownicy::jestWybrane()    //zwraca czy dane pole zostało wybrane
{
    return wybrane;
}

void CPoleSzachownicy::ustawMozliwyRuch(bool mozliwy) // ustawienie dla danego pola że jest możliwe do poruszenia się
{
    this->mozliwy = mozliwy;
    ustawKolorSpecjalny(mozliwy, Qt::green);
}

bool CPoleSzachownicy::jestMozliwyRuch() // zwraca czy dane pole jest polem na którym jest możliwy ruch
{
    return mozliwy;
}

void CPoleSzachownicy::ustawKolorSpecjalny(bool specjalny, QColor kolor)
{
    if (specjalny)      // jeżeli specjalny (czyli wybrany lub możliwy) jest true
    {
        setBrush(kolor);       // pokolorowanie na drakGreen lub green
    }
    else
    {
        setBrush(this->kolor);     // pokolorowanie na standardowe kolory
    }
    scene()->update();
}
