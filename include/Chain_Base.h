#ifndef CHAIN_BASE_H
#define CHAIN_BASE_H

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

class Chain_Base {
public:
    virtual ~Chain_Base() = default;

    // Add a card to the chain (must match the chain’s bean type)
    virtual Chain_Base& operator+=(Card* card) = 0;

    // Sell the entire chain: returns number of coins earned
    virtual int sell() const = 0;

    // Returns the bean type name of the chain (e.g. "Blue")
    virtual std::string getBeanName() const = 0;

    // Print the chain: print the bean type name followed by all card characters
    virtual void print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Chain_Base& chain) {
        chain.print(out);
        return out;
    }
};

#endif
