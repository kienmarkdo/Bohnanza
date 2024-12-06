#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <vector>
#include "Card.h"
#include <iostream>

class DiscardPile {
public:
    DiscardPile();
    void push(Card* card);
    Card* pickUp();
    Card* top() const;
    void print(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& discardPile);

private:
    std::vector<Card*> pile;
};

#endif // DISCARDPILE_H