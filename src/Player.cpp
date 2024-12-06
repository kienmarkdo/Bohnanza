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

void Player::drawCard(Card* card) {
    hand += card; // Use the overloaded operator+= for Hand to add the card
}

Card* Player::playTopCard() {
    return hand.play(); // Use the play() function from Hand to play the top card
}

int Player::getNumChains() const {
    return chains.size();
}

int Player::getMaxNumChains() const {
    return maxChains; // Assume maxChains is a member variable initialized to 2, and can be increased to 3 if bought
}

Chain<Card*>& Player::operator[](int index) {
    return chains[index];
}

// Print the player's details
std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "Player: " << player.name << ", Coins: " << player.coins << "\nChains: ";
    for (const auto& chain : player.chains) {
        out << chain << " ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Player& player) {
    // Deserialize player's name
    in >> player.name;

    // Deserialize player's coins
    in >> player.coins;

    // Deserialize player's chains
    int numChains;
    in >> numChains;
    player.chains.clear();
    for (int i = 0; i < numChains; ++i) {
        Chain<Card*> chain;
        in >> chain;  // Assuming Chain has the >> operator implemented
        player.chains.push_back(chain);
    }

    return in;
}


void Player::print(std::ostream& out) const {
    out << "Player: " << name << ", Coins: " << coins << "\n";
    for (const auto& chain : chains) {
        out << chain << "\n"; // Print each chain
    }
    out << "------------------------" << std::endl; // Add separator for readability
}