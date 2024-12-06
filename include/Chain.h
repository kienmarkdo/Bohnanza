#ifndef CHAIN_H
#define CHAIN_H

#include <vector>
#include <iostream>
#include "Card.h"
#include "CardFactory.h"

template <class T>
class Chain {
public:
    Chain() = default;
    Chain(std::istream& in, const CardFactory* factory);
    Chain& operator+=(Card* card);
    int sell() const;
    friend std::ostream& operator<<(std::ostream& out, const Chain<T>& chain) {
        chain.print(out);
        return out;
    }

private:
    std::vector<Card*> cards;

    void print(std::ostream& out) const {
        if (!cards.empty()) {
            out << cards.front()->getName() << " Chain: ";
            for (Card* card : cards) {
                card->print(out);
                out << " ";
            }
        }
    }
};

#endif // CHAIN_H
