/* Ristinolla
 *
 * Kuvaus:
 * Ohjelma luo laajennettavan ristinollapelin, jossa pelilauta on
 * aluksi 3 x 3 kokoinen. Laudalla on kolmenlaisia merkkeinä risti (X),
 * nolla (0) ja tyhjä (.). Pelaaja, joka pelaa ristillä aloittaa ja
 * pelivuoro siirtyy vuorotellen pelaajalta toiselle. Peli kysyy
 * vuoron aikana pelaajalta koordinaatteja, joiden avulla pelaajan
 * merkki sijoitetaan pelilaudalle. Peli päättyy, kun jompi kumpi
 * pelaajista saa muodostettua merkeillään täyden rivin, sarakkeen
 * tai diagonaalin tai jos pelilauta täyttyy kokonaan merkeistä.
 * Pelin aikana annetut koordinaatit tarkistetaan ja niiden pitää olla
 * joko pelilaudan sisällä tai ne saavat ylittyä tai alittua korkeintaan
 * yhdellä, mutta eivät kuitenkaan samanaikaisesti. Jos koordinaatti
 * ylittyy, laajenee pelilauta oikealle tai alas. Mikäli koordinaatti
 * alittuu, laajenee lauta vasemmalle ja alaspäin. Pelin päättyessä
 * peli kertoo pelin tilanteen ja mahdollisen voittajan.
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Ohjelma on toteutettu luokalla, jonka oliot esittävät pelilaudan
 * ruutuja. Pelilauta on toteutettu vektorina, joka sisältää rivivektoreita,
 * joiden alkioina toimivat luokan oliot, jotka kuvastavat ruutuja. Luokan
 * kautta päästään käsittelemään ruutujen muokkaamista suoraan.
 *
 * */


#include "mark.hh"
#include <iostream>

void initBoard(Board& board, int size) {
    // Luo vektorin sisään vektorin, joka koostu Mark olioista, jotka
    // kuvastavat pelilaudan ruutuja.
    //
    //:param board: funktiossa luotava vektorin sisäinen vektori
    //:param size: int, kertoo pelilaudan koon.

    for (int y = 0; y < size; ++y) {
        // Luo rivivektorin, johon oliot tallennetaan riveittäin.
        std::vector<Mark> row = {};

        for (int x = 0; x < size; ++x) {
            Mark new_mark(x,y);
            row.push_back(new_mark);
        }

        // Lisää rivivektorit yksitellen ulommaiseen vektoriin.
        board.push_back(row);

    }
}

Board changeBoard(Board& board, int x_value, int y_value, int size, char player) {
    // Funktio luo laajennetun pelilaudan.
    //
    //:param board: pelilautavektori
    //:param x_value: int, annettu x-koordinaatti
    //:param y_value: int, annettu y-koordinaatti
    //:param size: int, pelilaudan koko
    //:param player: char, vuorossa olevan pelaajan merkki
    //:return: Board, laajennuksella muokattu pelilautavektori

    Board new_board = {};

    // Tutkitaan, ylittyykö annettu koordinaatti.
    if ((x_value +1) == size or (y_value +1) == size) {

        // Käydään läpi alkuperäisen vektorin sisäiset vektorit ja
        // lisätään rivivektoreihin uusi olio.
        for (std::vector<Mark>& row : board) {
            Mark new_mark_1 ((size + 1),(size +1));
            row.push_back(new_mark_1);
        }

        // Luodaan pelilaudalle vielä yksi ylimääräinen rivi alapuolelle.
        std::vector<Mark> new_row = {};
        for (int x=0; x < size; ++x) {
            Mark new_mark_2(x,(size +1));
            new_row.push_back(new_mark_2);

        }

        board.push_back(new_row);

        // Lisätään pelaajan merkki uudistetulle pelilaudalle.
        board.at(y_value).at(x_value).add_mark(player);

        new_board = board;

    } else {

        // Luodaan kokonaan uusi pelilautavektori, joka sisältää
        // rivivektoreita
        for (int y = 0; y < size; ++y) {
            std::vector<Mark> row = {};
            for (int x = 0; x < size; ++x) {
                Mark new_mark_3(x,y);
                row.push_back(new_mark_3);
            }
            new_board.push_back(row);

        }
        // Lisätään pelilaudalle pelaajan lisäämä merkki.
        new_board.at(y_value +1).at(x_value +1).add_mark(player);

        // Lisätään uuteen tyhjään pelilautaan vanhan pelilaudan merkit.
        for (int y = 0; y < size -1; ++y) {
            for (int x = 0; x < (size -1); ++x) {
                if (board.at(y).at(x).has_mark() == true) {
                    char mark_place = board.at(y).at(x).print();
                    new_board.at(y+1).at(x+1).add_mark(mark_place);

                }
            }
        }

    }
    return new_board;

}

void printBoard(Board& board, int size) {
    // Funktio tulostaa pelilaudan.
    //
    //:param board: vector, pelilautavektori
    //:param size: int, pelilaudan koko

    //Tulostaa pelilaudan yläreunan numerorivin.
    std::cout << "  ";
    for (int x = 0; x < size; ++x) {
        if (x == (size -1)) {
            std::cout << (x +1) % 10;
        } else {
            std::cout << (x +1) % 10 << ' ';
        }

    }
    std::cout << std::endl;;

    // Tulostaa pelilaudan muut rivit, jotka alkavat numerolla ja
    // jatkuvat pelilautavektorin olioilla.
    for (int y = 0; y < size; ++y) {
        std::cout << (y +1) % 10 << ' ';
        for (int x = 0; x < size; ++x) {
            if (x == (size -1)) {
                std::cout << board.at(y).at(x).print() << std::endl;
            } else {
                std::cout << board.at(y).at(x).print();
                std::cout << " ";
            }
}
    }
}

bool isNumber(std::string answer) {
    // Tarkastelee, sisältääkö annettu teksti numeroita

    //:param answer: string, annettu tarkasteltava teksti syötteestä
    //:return: bool, sisältääkö annettu teksti vain numeroita.

    bool number = true;
    for (std::string::size_type index = 0; index < answer.length(); ++index) {
        char character = answer.at(index);

        if (isdigit(character) == true) {
            number = true;
        } else {
            number = false;
        }
    }
    return number;
}

bool isOnTheBoard(unsigned int x,unsigned int y,unsigned int size) {
    // Tarkastelee, onko annettu koordinaatti pelilaudalla.

    //:param x: unsigned int, koordinaatti x
    //:param y: unsigned int, koordinaatti y
    //:param size: unsigned int, pelilaudan koko
    //:return: bool, kertoo, onko koordinaatti pelilaudalla.

    if (0 < x and x <= size and 0 < y and y <= size) {
        return true;
    } else {
        return false;
    }

}

bool isAllowedNumber(unsigned int x,unsigned int y,unsigned int size) {
    // Tutkii erilaisten tilanteiden avulla, ovatko annetut koordinaatit
    // oikeellisia pelin sääntöjen perusteella

    //:param x: unsigned int, koordinaatti x
    //:param y: unsigned int, koordinaatti y
    //:param size: unsigned int, pelilaudan koko

    if (isOnTheBoard(x,y,size) == true) {
        return true;
    } else if ((x == 0 or x == (size +1)) and (0 < y and y <= size)) {
        return true;
    } else if ((0 < x and x <= size) and (y == 0 or y == (size +1))) {
        return true;
    } else if (x == 0 and y == 0) {
        return true;
    } else if (x == (size +1) and y == (size +1)) {
        return true;
    } else {
        return false;
    }
}

std::vector<unsigned int> getInput(unsigned int size, char player) {
    // Kysyy pelaajalta koordinaatit ja tutkii niiden oikeellisuuden.

    //:param size: unsigned int, kertoo pelilaudan koon
    //:param player: char, antaa vuorossa olevan pelaajan merkin.
    //:return: vector, palauttaa koordinaatit vektorina

    std::string answer_x = "";
    std::string answer_y = "";
    std::vector<unsigned int> coordinate_numbers = {};

    bool loop = true;

    while (loop) {
        // Kysyy koordinaatteja ja tallentaa ensimmäisen osan muuttujaan.
        std::cout << "For " << player << ", enter coordinates: x y> ";
        std::cin >> answer_x;

        // Tarkastelee syötteen ensimmäisen osan arvoa.
        if (answer_x == "q") {
            std::cout << "Why on earth you are giving up the game?" << 
                         std::endl;
            
            // Jos pelaaja haluaa lopettaa pelin, tallennetaan vektoriin 
            // koordinaatit (-1,-1), joiden avulla pääohjelma lopetetaan.
            coordinate_numbers.push_back(-1);
            coordinate_numbers.push_back(-1);
            loop = false;
        } else {
            // Jos ensimmäinen syöte ei ollut "q", tallennetaan myös syötteen
            // toinen osa eri muuttujaan.
            std::cin >> answer_y;

            // Tutkitaan annettujen koordinaattien oikeellisuutta ja
            // tallennetaan ne vektoriin kokonaislukuina, mikäli syöte on oikein
            // ja annetaan virheviesti, mikäli ne eivät ole oikein
            if (isNumber(answer_x) == true and isNumber(answer_y)) {
                unsigned int x = std::stoi(answer_x);
                unsigned int y = std::stoi(answer_y);

                if (isAllowedNumber(x,y,size)) {
                    coordinate_numbers.push_back(x);
                    coordinate_numbers.push_back(y);

                    loop = false;

                } else {
                    std::cout << "Coordinate outside the board" << std::endl;
                }
            } else {
                std::cout << "Coordinate outside the board" << std::endl;
            }
        }
    }
    return coordinate_numbers;

}

bool hasWon(Board board, unsigned int x_value, unsigned int y_value, int size, char player) {
    // Tutkii, onko pelaaja voittanut pelin uusilla koordinaateilla.

    //:param board: vector, pelilautavektori
    //:param x_value: unsigned int, koordinaatti x
    //:param y_value: unsigned int, koordinaatti y
    //:param size: unsigned int, pelilaudan koko
    //:param player: char, vuorossa olevan pelaajan merkki
    //:return: bool, kertoo, onko vuorossa oleva pelaaja voittanut pelin

    int x_count = 0;
    int y_count = 0;
    int diagonal_count_1 = 0;
    int diagonal_count_2 = 0;
    std::string player_str = "";
    int help_number = size -1;

    for (int ind = 0; ind < size; ++ind) {

        // Tutkii rivin, jossa annettu y-koordinaatti on
        if (board.at(y_value).at(ind).print() == player) {
            ++y_count;
        }

        // Tutkii sarakkeen, jossa annettu x-koordinaatti on
        if (board.at(ind).at(x_value).print() == player) {
            ++x_count;
        }

        // Tutkii toisen diagonaalin voittomahdollisuuden
        if (board.at(ind).at(ind).print() == player) {
            ++diagonal_count_1;
        }

        // Tutkii toisinpäin diagonaalin voittomahdollisuuden.
        if (board.at(help_number).at(ind).print() == player) {
            ++diagonal_count_2;
            help_number -= 1;
        }
    }

    
    if (player == 'X') {
        player_str = "Cross";
    } else {
        player_str = "Nought";
    }

    // Kertoo, kumpi pelaaja voitti ja millä tavalla.
    if (y_count == size) {
        std::cout << player_str <<" won horizontally" << std::endl;
        return true;
    } else if (x_count == size) {
        std::cout << player_str <<" won vertically" << std::endl;
        return true;
    } else if (diagonal_count_1 == size or diagonal_count_2 == size) {
        std::cout << player_str <<" won diagonally" << std::endl;
        return true;
    }

    else {
        return false;
    }
}

bool isFull(Board board, int size) {
    // Kertoo, onko pelilauta täynnä
    
    //:param board: vector, pelilautavektori
    //:param size: int, pelilaudan koko
    //:return: bool, onko pelilauta täynnä
    
    int count = 0;

    // Laskee, kuinka montaa tyhjää kohtaa laudalla on. 
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (board.at(y).at(x).print() == '.') {
                ++count;
            }
            }
    }

    // Jos tyhjiä kohtia ei ole, palautetaan, että funktio on tosi. 
    if (count == 0) {
        return true;
    } else {
        return false;
    }
}

bool menu() {
    // Luo ohjelmalle rungon ja tulostaa pelilaudat sekä pelin eri vaiheet
    
    //:param: bool, kertoo, onko ohjelma vielä toiminnassa vai onko se loppunut
    
    Board board = {};

    // Määrittää alkuarvot laudan koolle sekä vuorojen laskennalle sekä
    // luo tyhjän pelilaudan.
    unsigned int turn = 1;
    unsigned int size = 3;
    char player = ' ';
    initBoard(board, size);

    // Tulostaa pelilaudan ja pelin aloituksen. 
    std::cout << "Start game:" << std::endl;
    printBoard(board,size);
    std::cout << std::endl;

    while(true) {

        // Tutkii, kumpi pelaaja on vuorossa.
        if (turn % 2 == 0) {
            player = '0';
        } else {
            player = 'X';
        }

        // Hakee syötteen funktion avulla ja tallentaa koordinaatit 
        // erillisiin muuttujiin. 
        std::vector<unsigned int> coord = getInput(size,player);
        int x = coord.front();
        int y = coord.back();

        // Syötteestä saadaan arvoksi funktiosta koordinaatit (-1,-1) jos
        // pelaaja on halunnut lopettaa pelin
        if (x == -1 and y == -1) {
            return false;
            
        } else if (isOnTheBoard(x,y,size) == true) {
            
            // Jos koordinaatit ovat laudalla, muokata
            x -= 1;
            y -= 1;
            if (board.at(y).at(x).has_mark() == true) {
                std::cout << "The given place is already occupied" << std::endl;
            } else {
                board.at(y).at(x).add_mark(player);
                ++ turn;
                printBoard(board,size);
                std::cout << std::endl;

                if (isFull(board, size) == true) {
                    std::cout << "No empty places" << std::endl;
                    std::cout << "Game over!" << std::endl;
                    return false;
                }

                if (hasWon(board,x,y,size,player) == true) {
                    std::cout << "Game over!" << std::endl;
                    return false;
                }
                }
        } else {
            x -= 1;
            y -= 1;

            ++ size;
            board = changeBoard(board,x,y,size, player);
            printBoard(board, size);
            std::cout << std::endl;

            ++ turn;
        }
    }
}

int main() {
    menu();
}
