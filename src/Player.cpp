#include "Player.h"

// Constructor with player name
Player::Player(const std::string& name) 
    : name(name), coins(0) {}

// Constructor to load player state from input stream
Player::Player(std::istream& in, const CardFactory* factory) {
    // Load player's name, coins, and chains from the input stream
}

// Get the player's name
std::string Player::getName() const {
    return name;
}

// Get the number of coins the player has
int Player::getNumCoins() const {
    return coins;
}

// Add coins to the player's total
Player& Player::operator+=(int coinsToAdd) {
    coins += coinsToAdd;
    return *this;
}

// Add a chain to the player's chains
void Player::addChain(Chain<Card*> chain) {
    chains.push_back(chain);
}

// Print the player's details
std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "Player: " << player.name << ", Coins: " << player.coins << "\nChains: ";
    for (const auto& chain : player.chains) {
        out << chain << " ";
    }
    return out;
}

