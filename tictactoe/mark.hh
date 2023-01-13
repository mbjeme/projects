/* Ristinolla
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 * */

#ifndef MARK_HH
#define MARK_HH

#include <iostream>
#include <vector>

class Mark;
using Board = std::vector<std::vector<Mark>>;

class Mark {
public:

    // Luotu rakentaja oliolle, joka on ristinollapelilaudan yksi ruutu.
    Mark(int x, int y, char mark = '.');

    // Print() tulostaa ruudun merkin.
    char print() const;
    // Tarkastelee, onko ruudussa jo jomman kumman pelaajan merkki.
    bool has_mark() const;
    // Lisää haluttuun ruutuun pelaajan merkin
    void add_mark(char value);


private:
    // Ruudun koordinaatit ja sisältämä merkki.
    int x_ = 0;
    int y_ = 0;
    char mark_= '.';

};

#endif // MARK_HH
