/* Miinaharava peli
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "gameboard.hh"
#include "square.hh"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QLCDNumber>
#include <QTextBrowser>
#include <QCheckBox>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Toteuttaa peliin ajastimen.
    void displayTime();

private:
    Ui::MainWindow *ui = nullptr;
    QTimer* timer_ = nullptr;

    // Tallennetaan muuttujiin ja osoittajiin pelin kannalta
    // hyödyllisiä arvoja, joita voidaan käyttää funktioissa.
    QLineEdit* seedLineEdit_ = nullptr;
    QSpinBox* b_size_ = nullptr;
    int size_ = 6;
    GameBoard* board_ = nullptr;
    QPushButton* seedButton_ = nullptr;
    int seed_ = 0;
    bool flag_pressed_ = false;
    bool change_board_ = false;
    bool game_started = false;

    QLCDNumber* min_ = nullptr;
    QLCDNumber* sec_ = nullptr;
    int min_count_ = 0;
    int sec_count_ = 0;
    QString printed_text_ = "Start game by giving the seed value";
    QTextBrowser* infoTextBrowser_ = nullptr;
    QPushButton* commandPushButton_ = nullptr;
    QPalette pal_3;
    QPalette pal_4;

    // Tietue, johon tallennetaan laudan painonappi ja sen
    // x ja y koordinaatti.
    struct Coordinate {
        QPushButton* btn = nullptr;
        int x = 0;
        int y = 0;
    };

    // Vektori, johon tallennetaan laudan painonappien tietueet.
    std::vector<Coordinate> buttons_ = {};

    // Muuttaa pelilaudan kokoa annetun pelilaudan koon perusteella.
    void changeBoardSize();

    // Luo pelilaudan graafiset painonapit pelin koon perusteella.
    void createButtons();

    // Muuttaa kaikki pelilaudan painonapit epäaktiivisiksi.
    void inactivateButtons();

    // Muuttaa kaikki pelilaudan painonapit aktiivisiksi.
    void activateAllButtons();

    // Funktio, joka reagoi laudan painonapin painamiseen ja
    // luo erilaiset tapahtumat, jotka aiheutuvat painonapin
    // painamisesta sen perusteella, mitä ruudussa on.
    void buttonClicked();

    // Lukee seed arvon ja aloittaa pelin.
    void startGame();

    // Aloittaa pelin uudelleen alusta ja luo uuden laudan.
    void resetGame();

    // Hakee käyttäjän antaman seed arvon.
    void getSeed();

    // Hakee sen, asetetaanko pelilaudalle lippuja vai avataanko
    // ruutuja. Lisäksi vastaa kyseisen toiminto painonapin
    // ulkoasun muutoksesta, kun toiminto muuttuu.
    void setFlags();

    // Tulostaa uuden tulosteen textbrowser elementtiin.
    void printText();

    // Poistaa kaikki pelilaudan painonapit.
    void deleteButtons();

};
#endif // MAINWINDOW_HH
