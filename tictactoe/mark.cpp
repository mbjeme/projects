/* Ristinolla
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 *
 * */

#include "mark.hh"

Mark::Mark(int x, int y, char character): x_(x), y_(y), mark_(character) {}

char Mark::print() const {
    return mark_;
}

bool Mark::has_mark() const {
    if (mark_ == '0' or mark_ == 'X') {
        return true;
    } else {
        return false;
    }
}

void Mark::add_mark(char value) {
    mark_ = value;
}
