#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include "Hand.h"
#include "Chain_Base.h"
#include "Chain.h"

class Card;
class CardFactory;

class Player {
private:
    std::string name;
    int coins;
    std::vector<Chain_Base*> chains;
    Hand hand;
    int maxChains;

public:
    Player(const std::string& n) : name(n), coins(0), maxChains(2) {}
    Player(std::istream& in, CardFactory* factory);

    std::string getName() const { return name; }
    int getNumCoins() const { return coins; }
    int getNumChains() const { return (int)chains.size(); }
    int getMaxNumChains() const { return maxChains; }
    Chain_Base& operator[](int i);
    Player& operator+=(Card* c);
    Card* playCard();
    Card* topCard() const;
    bool buyThirdChain();
    void addCoins(int c);

    template<class T>
    void createChain() {
        if ((int)chains.size() < maxChains) {
            chains.push_back(new Chain<T>());
        } else {
            throw std::runtime_error("No more chains allowed.");
        }
    }

    const Hand& getHand() const { return hand; }

    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};

#endif
