#ifndef CHAIN_BASE_H
#define CHAIN_BASE_H

#include <iostream>
#include <string>
#include "Card.h"
#include "DiscardPile.h"

class CardFactory;

class Chain_Base {
public:
    virtual ~Chain_Base() {}
    virtual Chain_Base& operator+=(Card* c)=0;
    virtual int sell() const=0;
    virtual std::string getBeanName() const=0;
    virtual void print(std::ostream& out) const=0;
    virtual void clear()=0;
    virtual void moveCardsToDiscardPile(DiscardPile& dp)=0;
    virtual int size() const=0;
    virtual Card* frontCard() const=0;
    virtual void removeFrontCards(int n, DiscardPile& dp)=0;
    static Chain_Base* load(const std::string& line, CardFactory* f) {
        // Stub, returns nullptr. Could parse line to reconstruct chain.
        return nullptr;
    }
    friend std::ostream& operator<<(std::ostream& out,const Chain_Base& cb) {
        cb.print(out);
        return out;
    }
};

#endif
