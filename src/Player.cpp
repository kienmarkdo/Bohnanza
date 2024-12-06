#include "Player.h"
#include <stdexcept>

Player::Player(const std::string& playerName) : name(playerName), coins(0), maxChains(2) {
    // start with no chains
}

std::string Player::getName() const {
    return name;
}

int Player::getNumCoins() const {
    return coins;
}

void Player::addCoins(int c) {
    if (c < 0) throw std::invalid_argument("Cannot add negative coins");
    coins += c;
}

bool Player::buyThirdChain() {
    if (maxChains >= 3) return false; // already have the third chain
    if (coins >= 2) {
        coins -= 2;
        maxChains = 3;
        return true;
    }
    return false;
}

int Player::getMaxNumChains() const {
    return maxChains;
}

int Player::getNumChains() const {
    return (int)chains.size();
}

Chain_Base& Player::operator[](int i) {
    if (i < 0 || i >= (int)chains.size()) {
        throw std::out_of_range("Invalid chain index");
    }
    return *chains[i];
}

Player& Player::operator+=(Card* card) {
    hand += card;
    return *this;
}

Card* Player::playCard() {
    return hand.play();
}

Card* Player::topCard() const {
    return hand.top();
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << player.name << " " << player.coins << " coins" << std::endl;
    // Print chains
    for (size_t i = 0; i < player.chains.size(); ++i) {
        out << "Chain " << (i+1) << ": " << *player.chains[i] << std::endl;
    }
    // Print hand (hidden?), the specification does not say to print the hand for other players.
    // If the specification requires showing the hand, print here:
    // out << "Hand: " << player.hand << std::endl;
    return out;
}

Player::~Player() {
    // Delete all chains
    for (auto c : chains) {
        delete c;
    }
}
