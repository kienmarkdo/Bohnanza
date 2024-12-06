#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Chain.h"
#include "CardFactory.h"

class Player {
public:
    Player(const std::string& name);
    Player(std::istream& in, const CardFactory* factory);
    std::string getName() const;
    int getNumCoins() const;
    Player& operator+=(int coins);
    void addChain(Chain<Card*> chain);
    void print(std::ostream& out) const;
    void drawCard(Card* card);
    Card* playTopCard();
    int getNumChains() const;
    int getMaxNumChains() const;
    Chain<Card*>& operator[](int index);

    friend std::ostream& operator<<(std::ostream& out, const Player& player);
    friend std::istream& operator>>(std::istream& in, Player& player);

private:
    std::string name;
    int coins;
    std::vector<Chain<Card*>> chains;
};

#endif // PLAYER_H
