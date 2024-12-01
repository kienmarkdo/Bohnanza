#include "Player.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

Player::Player(const std::string &playerName)
    : name(playerName)
{
    chains.reserve(3);
    // Start with 2 empty chains (nullptr represents an empty chain)
    chains.push_back(nullptr);
    chains.push_back(nullptr);
}

Player::Player(std::istream &in, const CardFactory *factory)
{
    chains.reserve(3);
    // Implementation for loading from file will be updated when needed
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
    return std::count_if(chains.begin(), chains.end(),
                         [](const auto &chain)
                         { return chain && chain->size() > 0; });
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
    chains.push_back(nullptr); // Reserve space for the third chain
}

void Player::printHand(std::ostream &out, bool all) const
{
    if (all)
    {
        out << hand;
    }
    else
    {
        if (!hand.empty())
        {
            out << "Top card: ";
            if (const Card *top = hand.top())
            {
                top->print(out);
                out << "\n";
            }
        }
        else
        {
            out << "Hand is empty\n";
        }
    }
}

void Player::serialize(std::ostream &out) const
{
    out << name << "\n";
    out << coins << "\n";
    out << chains.size() << "\n";

    for (const auto &chain : chains)
    {
        if (chain)
        {
            chain->serialize(out);
        }
        else
        {
            out << "EMPTY_CHAIN\n";
        }
    }

    hand.serialize(out);
}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    // Print player name and coins line with proper spacing
    out << std::left << player.name << "\t" << player.coins << " coins\n";

    // Print each chain with proper spacing
    for (const auto &chain : player.chains)
    {
        if (chain) // if chain exists
        {
            // Print chain type with same tab alignment as name
            out << chain->getType() << "\t";
            // Print the chain contents
            chain->print(out);
            out << "\n";
        }
        else // empty chain
        {
            out << "empty\t\n";
        }
    }

    return out;
}

void Player::addToFrontOfHand(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::runtime_error("Cannot add null card to hand");
    }
    hand.addToFront(std::move(card)); // Assuming 'hand' is a deque
}