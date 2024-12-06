#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include <memory>
#include "Card.h"

class Deck {
public:
    Deck(std::vector<std::unique_ptr<Card>>&& cards);
    Card* draw();
    int size() const; // Get the number of cards remaining
    friend std::ostream& operator<<(std::ostream& out, const Deck& deck);

private:
    std::vector<Card*> cards;
};

#endif // DECK_H