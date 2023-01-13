/* Miinaharava
 *
 * Kuvaus:
 * Käynnistettäessä ohjelma luo graafisen käyttöjärjestelmän
 * miinaharava pelille. Tässä vaiheessa luodaan oletusarvona
 * 6 x 6 kokoinen pelilauta painonapeista. Pelin alussa pelille
 * annetaan seed arvo, jonka perusteella luodaan pelilauta ja
 * sijoitetaan miinat. Tämän jälkeen peliä voi pelata painamalla
 * pelilaudan ruutuja. Pelissä on action napissa kaksi eri toimintoa,
 * joiden välillä voi vaihdella nappia painamalla. Peli hävitään,
 * mikäli avataan ruutu, joka sisältää miinan. Pelin voi voittaa,
 * jos kaikki miinan sisältävät ruudut merkitään lipuilla.
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Ohjelmassa pelilauta on toteutettu painonappeina, joihin
 * tulee ikonien avulla näkyviin avattu ominaisuus. Painonapit ja
 * niiden x ja y koordinaatit on tallennettu tietueeseen, jotka
 * on tallennettu edelleen vektoriin, josta niitä on helppo
 * käsitellä. Pelissä myös laudan kokoa voi vaihtaa käyttöliittymän
 * avulla.
 *
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Luodaan käyttöjärjestelmään tarvittavia elementtejä, jotka
    // asemoidaan siististi avautuvaan ikkunaan.

    QLabel* label = new QLabel("Minesweeper", this);
    label->setGeometry(50, 25, 100, 25);

    QLabel* sizeLabel =new QLabel("Board size: ", this);
    sizeLabel->setGeometry(50, 85, 150, 25);

    QLabel* seed_lbl = new QLabel("Give a seed value: ", this);
    seed_lbl->setGeometry(50, 55, 150, 25);

    QLabel* timeLabel = new QLabel("Time:", this);
    timeLabel->setGeometry(50,175, 100, 25);

    QLabel* actionLabel = new QLabel("Action", this);
    actionLabel->setGeometry(50, 115, 100, 25);

    seedLineEdit_ = new QLineEdit(this);
    seedLineEdit_->setGeometry(225, 55, 50, 25);

    // Asetetaan laudan koon oletusarvoksi 6 ja säädetään, että
    // annettavat arvot voivat olla ainoastaan väliltä 3-9.
    b_size_ = new QSpinBox(this);
    b_size_->setGeometry(225, 85, 50, 25);
    b_size_->setMinimum(3);
    b_size_->setMaximum(9);
    b_size_->setValue(6);

    seedButton_ = new QPushButton("Start",this);
    seedButton_->setGeometry(325, 55, 75, 25);

    QPushButton* resetButton = new QPushButton("Reset", this);
    resetButton->setGeometry(325, 85, 75, 25);

    infoTextBrowser_ = new QTextBrowser(this);
    infoTextBrowser_->setGeometry(425, 55, 160, 55);

    commandPushButton_ = new QPushButton("Open squares", this);
    commandPushButton_->setGeometry(50, 145, 100, 25);

    min_ = new QLCDNumber(this);
    min_->setGeometry(50, 205, 70, 35);
    sec_ = new QLCDNumber(this);
    sec_->setGeometry(120, 205, 70, 35);

    // Muokataan luotuja elementtejä käyttöjärjestelmässä.
    min_->setSegmentStyle(QLCDNumber::Flat);
    min_->setAutoFillBackground(true);

    QPalette Pal_1 = min_->palette();
    Pal_1.setColor(QPalette::Normal, QPalette::WindowText,
                   QColor(255,69,0));
    min_->setPalette(Pal_1);

    sec_->setSegmentStyle(QLCDNumber::Flat);
    sec_->setAutoFillBackground(true);

    QPalette Pal_2 = min_->palette();
    Pal_2.setColor(QPalette::Normal, QPalette::WindowText,
                   QColor(255,69,0));
    sec_->setPalette(Pal_2);

    // Luodaan painonapille kaksi erilaista palettia, joiden avulla
    // napin ulkonäköä muokataan pelin aikana.
    pal_3 = commandPushButton_->palette();
    pal_3.setColor(QPalette::Button, QColor(255,102,102));
    pal_4 = commandPushButton_->palette();
    pal_4.setColor(QPalette::Button, QColor(178,255,102));
    commandPushButton_->setAutoFillBackground(true);
    commandPushButton_->setPalette(pal_3);
    commandPushButton_->update();

    timer_ = new QTimer(this);

    // Yhdistetään erilaisia elementtejä niille ominaisiin komentoihin.
    // Muutos b_size_ arvossa muuttaa laudan kokoa.
    connect(b_size_, &QSpinBox::valueChanged, this,
            &MainWindow::changeBoardSize);

    // Painonapin klikkaaminen aloittaa pelin ensimmäistä kertaa.
    connect(seedButton_, &QPushButton::clicked, this,
            &MainWindow::startGame);

    // Reset painonappi aloittaa pelin uudelleen ja alustaa pelin
    // random seed arvolla.
    connect(resetButton, &QPushButton::clicked, this,
            &MainWindow::resetGame);

    connect(timer_, SIGNAL(timeout()), this, SLOT(displayTime()));

    // Painonappia painamalla käyttäjä voi vaihtaa, haluaako asettaa
    // lippuja vai avata ruutuja. Myös napin ulkoasu muuttuu.
    connect(commandPushButton_, &QPushButton::clicked,this,
            &MainWindow::setFlags);

    // Luo ensimmäiset painonapit laudan koon oletusarvolla 6.
    createButtons();
    inactivateButtons();

    printText();
}

MainWindow::~MainWindow()
{
    // Poistaa osoittimiin tallennettuja arvoja.
    delete ui;
    delete board_;

    for (Coordinate values : buttons_) {
        delete values.btn;
    }
}

void MainWindow::printText() {

    // Tulostaa tulosruutuun halutun tekstin.
    QString str = "";
    str.append(printed_text_);
    infoTextBrowser_->setText(str);

}

void MainWindow::deleteButtons()
{
    // Poistaa pelilaudan painonapit ja tyhjentää vektorin, johon
    // painonappien tiedot oli tallennettuna.
    for (Coordinate values : buttons_) {
        delete values.btn;
    }

    while (buttons_.size() != 0) {
        buttons_.pop_back();
    }

}

void MainWindow::setFlags() {

    if (flag_pressed_ == false) {

        // Jos peli on avausmuodossa, muuttaa muotoon, jossa pelaaja
        // voi lisätä pelilaudalle lippuja.
        flag_pressed_ = true;

        // Muokkaa painonappia, jotta pelaaja näkee, että peli
        // on muodossa, jossa voidaan asettaa lippuja.
        commandPushButton_->setText("Set a flag");
        commandPushButton_->setPalette(pal_4);
        commandPushButton_->update();

    } else {

        // Asettaa pelin muotoon, jossa pelaaja voi avata ruutuja.
        flag_pressed_ = false;

        // Muokkaa painonappia, jotta pelaaja näkee, että pelistä
        // voidaan avata ruutuja.
        commandPushButton_->setText("Open squares");
        commandPushButton_->setPalette(pal_3);
        commandPushButton_->update();
    }
}

void MainWindow::displayTime()
{
    // Luo minuutit ja sekuntit ajastimeen.
    if (sec_count_ == 60) {
        sec_count_ = 0;
        ++min_count_;
    } else {
        ++sec_count_;
    }

    min_->display(min_count_);
    sec_->display(sec_count_);
}

void MainWindow::changeBoardSize()
{
    // Hakee laudan koon spinboxista.
    size_ = b_size_->value();

    // Aloittaa ajastimen uudelleen alusta.
    timer_->stop();

    min_count_ = 0;
    sec_count_ = 0;

    min_->display(min_count_);
    sec_->display(sec_count_);

    timer_->start(1000);

    // Poistaa vanhan laudan ja luo uuden oikean kokoisen
    // pelilaudan.
    delete board_;

    board_ = new GameBoard(size_);
    board_->init(seed_);

    // Poistaa vanhat napit ja luo uudet perustuen uuden kokoiseen
    // pelilautaan.
    deleteButtons();
    createButtons();
}

void MainWindow::startGame()
{
    // Aloittaa ajastimen ja pelin ja asettaa start painonapin
    // ja seed line edit alueen pois päältä.
    timer_->start(1000);

    game_started = true;
    seedButton_->setEnabled(false);
    seedLineEdit_->setEnabled(false);
    activateAllButtons();

    // Hakee pelaajan antaman seed arvon ja laudan koon ja luo
    // uuden laudan.
    getSeed();
    size_ = b_size_->value();

    board_ = new GameBoard(size_);
    board_->init(seed_);
    board_->print(std::cout);

    // Luo napeista uuden pelilaudan, jos laudan koko ei vastaa
    // annettua oletusarvoa.
    if (size_ != 6) {
        deleteButtons();
        createButtons();
    }

}

void MainWindow::resetGame()
{
    // Aloittaa pelin ja alustaa ajastimen ja aloittaa sen uudelleen
    printed_text_ = "Restarting the game!";
    printText();

    b_size_->setEnabled(true);
    commandPushButton_->setEnabled(true);
    game_started = true;

    timer_->stop();

    min_count_ = 0;
    sec_count_ = 0;

    min_->display(min_count_);
    sec_->display(sec_count_);

    timer_->start(1000);

    // Käy läpi pelilaudan napit ja asettaa ne valmiiksi peliin.
    for (auto& value : buttons_) {
        value.btn->setText("");
        value.btn->setEnabled(true);
        value.btn->setIcon(QIcon());
    }

    int size = board_->getSize();

    // Poistaa edellisen pelilaudan ja luo uuden random seed arvolla.
    delete board_;

    board_ = new GameBoard(size);
    board_->init(time(NULL));

}

void MainWindow::getSeed()
{
    // Hakee seed arvon ja muuttaa sen int muotoon.
    QString txt_seed = seedLineEdit_->text();

    if (txt_seed == "") {
        seed_ = time(NULL);
    } else {
        seed_ = txt_seed.toInt();
    }
}

void MainWindow::buttonClicked()
{
    printed_text_ = "";
    printText();

    // Nappia voidaan klikata vain, jos peli on aloitettu ja se ei ole
    // päättynyt vielä.
    if (game_started == true and not board_->isGameOver()) {

        const std::string PREFIX("Resources/");
        const std::string SUFFIX(".png");

        // Luodaan kuva, joka asetetaan painonappiin, jos napin
        // alla on pommi. Kuva skaatalaan oikeaksi.
        std::string filename = PREFIX + "bomb" + SUFFIX;
        QPixmap image(QString::fromStdString(filename));

        image = image.scaled(50,50);

        // Käydään läpi pelilaudan painonapit.
        for (auto& value : buttons_) {

            // Tutkitaan, mikä nappi on painettu ja tutkitaan
            // ruudun ominaisuuksia.
            if (value.btn == sender()) {

                Square square = board_->getSquare(value.x, value.y);

                if (flag_pressed_ == true) {

                    // Jos käyttäjä haluaa asettaa lipun, asetetaan
                    // kuvaksi lipun kuva.
                    std::string flag_filename = PREFIX + "flag" +
                            SUFFIX;
                    QPixmap flag_image(QString::fromStdString
                                       (flag_filename));

                    flag_image = flag_image.scaled(50,50);
                    value.btn->setIcon(flag_image);

                    // Jos ruudussa on jo lippu, poistetaan ruudusta
                    // lippu, muuten lisätään ruutuun lippu.
                    if (square.hasFlag()) {
                        square.removeFlag();
                        value.btn->setIcon(QIcon());
                    } else {
                        square.addFlag();
                    }
                    board_->setSquare(square, value.x, value.y);

                } else {

                    if (not board_->openSquare(value.x,value.y)) {

                        // Jos kyseessä on pommi, pysäytetään ajastin
                        // ja asetetaan ruutuun kuvaksi pommi.
                        timer_->stop();

                        value.btn->setIcon(image);

                        // Ilmoitetaan häviöstä ja lopetetaan peli.
                        printed_text_ = "Game Over!";
                        printText();
                        game_started = false;

                        // Käydään läpi kaikki napit ja näytetään
                        // kaikki pommit ja asetetaan muut
                        // painonapit pois päältä.
                        for (auto& button : buttons_) {

                            Square bomb = board_->getSquare(button.x,
                                                            button.y);

                            if (bomb.hasMine()) {
                                button.btn->setIcon(image);
                            } else {
                                button.btn->setEnabled(false);
                            }
                        }

                    } else {

                        int size = board_->getSize();

                        // Käydään läpi laudan koordinaatteja ja
                        // avataan myös tarvittaessa viereisiä ruutuja.
                        for (int x = 0; x < size; ++x) {
                            for (int y = 0; y < size; ++y) {
                                Square current_button = board_->
                                        getSquare(x,y);

                                int mine_num =
                                        current_button.countAdjacent();
                                QString mines =
                                        QString::number(mine_num);
                                std::string number =
                                        mines.toStdString();

                                std::string file = PREFIX + number +
                                        SUFFIX;
                                QPixmap num_image(
                                            QString::fromStdString(file));

                                num_image = num_image.scaled(50,100);


                                // Asetetaan avatuille ruuduille kuvaksi
                                // miinoja vastaavat numerot.
                                for (auto& coordinate : buttons_) {
                                    if (coordinate.x == x and
                                            coordinate.y == y) {
                                        Square test = board_->getSquare(
                                                    coordinate.x,
                                                    coordinate.y);

                                        if (test.isOpen()) {
                                            coordinate.btn->setIcon(
                                                        num_image);
                                        }
                                    }
                                }
                        }
                    }

                    return;
                }
                    board_->setSquare(square, value.x, value.y);
                }
        }
    }
    }

    // Tarkastellaan, onko peli voitettu.
    if (board_->isGameOver() == true) {
        printed_text_ = "You won the game!";
        inactivateButtons();
        b_size_->setEnabled(false);
        commandPushButton_->setEnabled(false);
        printText();
        timer_->stop();
    }


}


void MainWindow::createButtons()
{

    // Luodaan koordinaattien avulla lauta, jolle sijoitetaan eri
    // koordinaateille painonapit.
    for (int x = 0; x < size_; ++x) {

        for (int y = 0; y < size_; ++y) {

            QPushButton* button = new QPushButton(this);
            button->setGeometry(225+x*50,120+y*50,50,50);
            button->show();

            // Yhdistetään napit funktioon, joka käsittelee niiden
            // painamisen.
            connect(button, &QPushButton::clicked, this,
                    &MainWindow::buttonClicked);

            // Lisätään painonapit ja niiden x ja y koordinaatit
            // tietueeseen, jotka lisätään kaikki vektoriin.
            Coordinate values = {button, x, y};
            buttons_.push_back(values);
        }

    }
}

void MainWindow::inactivateButtons()
{
    for (auto value : buttons_) {
        value.btn->setEnabled(false);
    }
}

void MainWindow::activateAllButtons()
{
    for (auto value : buttons_) {
        value.btn->setEnabled(true);
    }
}
