#include "Player.h"
#include "Card.h"
#include "CardFactory.h"
#include <limits>
#include "Chain_Base.h"

std::ostream& operator<<(std::ostream& out, const Player& p) {
    out << p.name << "\n" << p.coins << "\n" << p.maxChains << "\n";
    out << p.chains.size() << "\n";
    for (auto c : p.chains) {
        out << *c << "\n";
    }
    out << p.hand << "\n";
    return out;
}

Player::Player(std::istream& in, CardFactory* factory) {
    in >> name >> coins >> maxChains;
    int cCount; in >> cCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i=0; i<cCount; i++) {
        std::string line;
        std::getline(in,line);
        chains.push_back(Chain_Base::load(line, factory));
    }
    hand = Hand(in, factory);
}

Chain_Base& Player::operator[](int i) { return *chains[i]; }
Player& Player::operator+=(Card* c) { hand+=c; return *this; }
Card* Player::playCard() { return hand.play(); }
Card* Player::topCard() const { return hand.top(); }
bool Player::buyThirdChain() {
    if (maxChains>=3) return false;
    if (coins>=2) { coins-=2; maxChains=3;return true;}
    return false;
}
void Player::addCoins(int c) { coins+=c; }
