#ifndef HAND_H
#define HAND_H

#include <list>
#include <iostream>
#include "Card.h"
#include "CardFactory.h"

class Hand {
public:
    Hand(std::istream& in, const CardFactory* factory);
    Hand& operator+=(Card* card);
    Card* play();
    Card* top() const;
    Card* operator[](int index) const;
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);

private:
    std::list<Card*> cards;
};

#endif // HAND_H