#include "Player.h"
#include <stdexcept>
#include <sstream>

Player::Player(const std::string &playerName)
    : name(playerName)
{
    // Start with two empty chains
    chains.reserve(3); // Reserve space for potential third chain
}

Player::Player(std::istream &in, const CardFactory *factory)
{
    // Implementation will be completed when CardFactory is implemented
    // This constructor will read the player state from a file and reconstruct it
    chains.reserve(3);
}

Player &Player::operator+=(int additionalCoins)
{
    if (additionalCoins < 0)
    {
        throw std::invalid_argument("Cannot add negative coins");
    }
    coins += additionalCoins;
    return *this;
}

int Player::getNumChains() const
{
    int count = 0;
    for (const auto &chain : chains)
    {
        // Need to implement a way to check if chain is empty
        if (chain && chain->size() > 0)
        {
            count++;
        }
    }
    return count;
}

void Player::validateChainIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(chains.size()))
    {
        std::ostringstream oss;
        oss << "Chain index " << index << " is out of range. Player has "
            << chains.size() << " chains";
        throw std::out_of_range(oss.str());
    }
}

Chain_Base &Player::operator[](int i)
{
    validateChainIndex(i);
    return *chains[i];
}

const Chain_Base &Player::operator[](int i) const
{
    validateChainIndex(i);
    return *chains[i];
}

void Player::buyThirdChain()
{
    if (chains.size() >= 3)
    {
        throw std::runtime_error("Already has maximum number of chains");
    }

    if (coins < 3)
    {
        throw NotEnoughCoins();
    }

    coins -= 3;
    // Note: The actual chain type will be determined when cards are added
    chains.push_back(nullptr); // Reserve space for the third chain
}

void Player::printHand(std::ostream &out, bool all) const
{
    if (all)
    {
        // Print entire hand
        out << hand;
    }
    else
    {
        // Print only top card
        if (!hand.empty())
        {
            out << "Top card: ";
            hand.top()->print(out);
            out << "\n";
        }
        else
        {
            out << "Hand is empty\n";
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << player.name << " " << player.coins << " coins\n";

    // Print each chain
    for (size_t i = 0; i < player.chains.size(); ++i)
    {
        if (player.chains[i])
        {
            out << "Chain " << i + 1 << ": ";
            player.chains[i]->print(out);
            out << "\n";
        }
        else
        {
            out << "Chain " << i + 1 << ": empty\n";
        }
    }

    return out;
}

void Player::serialize(std::ostream &out) const
{
    // Store player name and coins
    out << name << "\n";
    out << coins << "\n";

    // Write player name
    out << name << "\n";

    // Write number of coins
    out << getNumCoins() << "\n";

    // Write number of chains
    out << chains.size() << "\n";

    // Write each chain
    for (const auto &chain : chains)
    {
        if (chain)
        {
            chain->serialize(out);
        }
    }

    // Write hand using its serialize method
    hand.serialize(out); // Add this line to save the player's hand
}