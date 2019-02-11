#ifndef CGLOWNEOKNO_H
#define CGLOWNEOKNO_H

#include <QMainWindow>

namespace Ui {
class CGlowneOkno;
}

class CSzachownica;
class CGra;



class CGlowneOkno : public QMainWindow
{
    Q_OBJECT

public:
    explicit CGlowneOkno(QWidget *parent = 0);
    ~CGlowneOkno();

private slots:
    /**
     * @brief on_nowa_gra_clicked
     *Funkcja powracająca do szachownicy po wciśnięciu przycisku na której zostały od nowa ułożone figury (Nowa Gra)
     */
    void on_nowa_gra_clicked();

    /**
     * @brief on_close_clicked
     *Funkcja zamykająca grę po wciśnięciu przycisku
     */
    void on_close_clicked();

    /**
     * @brief czyKoniec
     *Funkcja przechwytująca zmiany parametru z klasy CSzachownica który zwraca true gdy wystąpił Szach Mat
     * @param czy_koniec
     */
    void czyKoniec(bool czy_koniec);


private:

    Ui::CGlowneOkno *ui;

    /**
     * @brief szachownica
     *Szachwonica na której odbywa się cała gra, odpowiadająca za wyświetlenie na ekranie
     */
    CSzachownica *szachownica;

    CGra *gra;



};

#endif // CGLOWNEOKNO_H
