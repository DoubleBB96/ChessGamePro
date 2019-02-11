#ifndef CPOLESZACHOWNICY_H
#define CPOLESZACHOWNICY_H

#include <QGraphicsRectItem>

class CFigura;

/**
 * @brief The CPoleSzachownicy class
 * Klasa Pól Szachownicy
 */
class CPoleSzachownicy : public QObject, public QGraphicsRectItem
{

    Q_OBJECT
public:
    /**
     * @brief CPoleSzachownicy
     *Konstruktor każdego z pól
     * @param y współrzedna wiersza
     * @param x wspólrzędna kolumny
     * @param parent ???
     */
    explicit CPoleSzachownicy(int y, int x, QGraphicsItem *parent = nullptr);

    ~CPoleSzachownicy();

    /**
     * @brief ustawKolor
     *Funkcja ustawiająca w GUI kolor danego pola przy tworzeniu szachownicy
     * @param kolor Parametr typu QColor, odpowiadający za aktualny kolor danego pola
     */
    void ustawKolor(QColor kolor);

    /**
     * @brief ustawFigure
     *Funkcja ustawiająca obiekt klasy CFigura na danym polu
     * @param f Przekazywana figura do ustawienia na polu
     */
    void ustawFigure(CFigura *f);

    /**
     * @brief pobierzFigure
     *Funkcja pobierająca figurę z danego pola
     * @return Figura znajdująca się na danym polu
     */
    CFigura *pobierzFigure();

    /**
     * @brief zdejmijFigure
     *Funkcja usuwająca figurę z jej początkowego miejsca
     * @return Figura, która została zdjęta ze swojej pozycji
     */
    CFigura * zdejmijFigure();

    /**
     * @brief pobierzWiersz
     *Funkcja zwracająca numer wierszu danego pola
     * @return Wiersz danego pola
     */
    int pobierzWiersz();

    /**
     * @brief pobierzKolumne
     *Funkcja zwracająca numer kolumny danego pola
     * @return Kolumna danego pola
     */
    int pobierzKolumne();

    /**
     * @brief pobierzPozycje
     *Funkcja zwracająca punkt o współrzędnych gdzie dane pole znajduje sie na GUI
     * @return Pozycja punktu typu QPoint
     */
    QPoint pobierzPozycje();

    /**
     * @brief paint
     *Wirtualna funkcja należąca do interfejsu QGraphicsRectItem
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief mousePressEvent
     *Wirtualna funkcja obsługująca zdarzenia związane z kliknięciem myszy. Emituje on sygnał, że dane pole zostało kliknięte
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief ustawWybrane
     *Funkcja ustawiająca dane pole jako wybrane przez użytkownika na którym znajduje się figura
     * @param wybrane Zmienna logiczna do przekazania informacji czy dane pole jest wybrane
     */
    void ustawWybrane(bool wybrane);

    /**
     * @brief jestWybrane
     *Funkcja zwracająca atrybut logiczny wybrane
     * @return Atrybut logiczny wybrane
     */
    bool jestWybrane();

    /**
     * @brief ustawMozliwyRuch
     *Funkcja ustawiająca dane pole jako te na które może być wykonany ruch
     * @param mozliwy Zmienna logiczna do przekazania informacji czy na dane pole może być wykonany ruch
     */
    void ustawMozliwyRuch(bool mozliwy);

    /**
     * @brief jestMozliwyRuch
     *Funkcja zwracająca atrybut logiczny mozliwy
     * @return Atrybut logiczny mozliwy
     */
    bool jestMozliwyRuch();

signals:

    /**
     * @brief kliknieto
     * Funkcja generująca sygnał, gdy dane pole zostało kliknięte
     */
    void kliknieto(CPoleSzachownicy *);

protected:

    /**
     * @brief ustawKolorSpecjalny
     *Funkcja która odpowiada za pokolorowanie pola wybranego przez gracza na którym znajduje się figura, oraz pól na które mozliwy jest ruch wybranej figury
     * @param specjalny Zmienna logiczna która ma stan wysoki dla pól które mają być pokolorowane
     * @param kolor Zmienna typu QColor która ustawia kolor dla danego pola
     */
    void ustawKolorSpecjalny(bool specjalny, QColor kolor = QColor());

private:

    /**
     * @brief pozycja Aktualna pozycja pola na GUI
     */
    QPoint pozycja;

    /**
     * @brief figura Obiekt(Figura) klasy CFigura znajdujący się na danym polu
     */
    CFigura *figura = nullptr;

    /**
     * @brief kolor Kolor danego pola
     */
    QColor kolor;

    /**
     * @brief wybrane Zmienna logiczna zwracający czy dane pole zostało wybrane przez gracza
     */
    bool wybrane = false;

    /**
     * @brief mozliwy Zmienna logiczna zwracająca czy na dane pole może zostać wykonany ruch
     */
    bool mozliwy = false;
};

#endif // CPOLESZACHOWNICY_H
