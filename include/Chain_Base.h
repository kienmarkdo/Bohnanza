#ifndef CHAIN_BASE_H
#define CHAIN_BASE_H

#include <iostream>
#include <string>
#include "Card.h"
#include "DiscardPile.h"

class Chain_Base {
public:
    virtual ~Chain_Base() = default;
    virtual Chain_Base& operator+=(Card* card) = 0;
    virtual int sell() const = 0;
    virtual std::string getBeanName() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void clear() = 0;
    virtual void moveCardsToDiscardPile(DiscardPile& dp) = 0;
    // Added for partial selling
    virtual int size() const = 0;  
    virtual Card* frontCard() const = 0;  
    virtual void removeFrontCards(int n, DiscardPile& dp) = 0;  
    friend std::ostream& operator<<(std::ostream& out, const Chain_Base& chain) {
        chain.print(out);
        return out;
    }
};

#endif
