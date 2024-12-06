#include "Player.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <limits>
#include "CardFactory.h"
#include "Chain.h"

/**
 * @brief Constructs a new Player with the given name
 *
 * @param playerName The name of the player
 *
 * Initializes a player with two empty chains and no coins.
 */
Player::Player(const std::string &playerName)
    : name(playerName)
{
    // Reserve space for maximum possible chains
    chains.reserve(3);
    chains.push_back(nullptr);
    chains.push_back(nullptr);
}

/**
 * @brief Constructs a Player from a saved game state
 *
 * @param in Input stream containing serialized player data
 * @param factory Pointer to the CardFactory used to create cards
 *
 * Reads and reconstructs:
 * - Player name
 * - Coin count
 * - Chains and their contents
 * - Hand of cards
 */
Player::Player(std::istream &in, const CardFactory *factory)
{
    // Read player name
    std::getline(in, name);

    // Read coins
    in >> coins;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read number of chains
    int chainCount;
    in >> chainCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    chains.reserve(3);

    // Reconstruct each chain based on its type
    for (int i = 0; i < chainCount; ++i)
    {
        std::string line;
        std::getline(in, line);

        if (line == "EMPTY_CHAIN")
        {
            chains.push_back(nullptr);
            continue;
        }

        // Create appropriate chain type based on card name
        std::string chainType = line;
        try
        {
            if (chainType == "Blue")
            {
                chains.push_back(std::make_unique<Chain<Blue>>(in, factory));
            }
            else if (chainType == "Chili")
            {
                chains.push_back(std::make_unique<Chain<Chili>>(in, factory));
            }
            else if (chainType == "Stink")
            {
                chains.push_back(std::make_unique<Chain<Stink>>(in, factory));
            }
            else if (chainType == "Green")
            {
                chains.push_back(std::make_unique<Chain<Green>>(in, factory));
            }
            else if (chainType == "Soy")
            {
                chains.push_back(std::make_unique<Chain<Soy>>(in, factory));
            }
            else if (chainType == "Black")
            {
                chains.push_back(std::make_unique<Chain<Black>>(in, factory));
            }
            else if (chainType == "Red")
            {
                chains.push_back(std::make_unique<Chain<Red>>(in, factory));
            }
            else if (chainType == "Garden")
            {
                chains.push_back(std::make_unique<Chain<Garden>>(in, factory));
            }
            else
            {
                throw std::runtime_error("Unknown chain type encountered while loading player: " + chainType);
            }
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error creating chain of type " + chainType + ": " + e.what());
        }
    }

    // Load the player's hand
    Hand loadedHand(in, factory);
    hand = std::move(loadedHand);
}

/**
 * @brief Adds coins to the player's total
 *
 * @param additionalCoins Number of coins to add
 * @return Reference to the modified Player
 * @throws std::invalid_argument if additionalCoins is negative
 */
Player &Player::operator+=(int additionalCoins)
{
    if (additionalCoins < 0)
    {
        throw std::invalid_argument("Cannot add negative coins");
    }
    coins += additionalCoins;
    return *this;
}

/**
 * @brief Gets the number of non-empty chains the player has
 *
 * @return Number of chains containing at least one card
 */
int Player::getNumChains() const
{
    return std::count_if(chains.begin(), chains.end(),
                         [](const auto &chain)
                         {
                             return chain && chain->size() > 0;
                         });
}

/**
 * @brief Validates if a chain index is within bounds
 *
 * @param index Index to validate
 * @throws std::out_of_range if index is invalid
 */
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

/**
 * @brief Accesses a chain by index
 *
 * @param i Index of the chain to access
 * @return Reference to the chain
 * @throws std::out_of_range if index is invalid
 */
Chain_Base &Player::operator[](int i)
{
    validateChainIndex(i);
    return *chains[i];
}

/**
 * @brief Accesses a chain by index (const version)
 *
 * @param i Index of the chain to access
 * @return Const reference to the chain
 * @throws std::out_of_range if index is invalid
 */
const Chain_Base &Player::operator[](int i) const
{
    validateChainIndex(i);
    return *chains[i];
}

/**
 * @brief Purchases a third chain for the player
 *
 * @throws std::runtime_error if player already has maximum chains
 * @throws NotEnoughCoins if player has fewer than 3 coins
 */
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
    chains.push_back(nullptr);
}

/**
 * @brief Prints the player's hand
 *
 * @param out Output stream to print to
 * @param all If true, prints all cards; if false, only prints top card
 */
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

/**
 * @brief Serializes the player's state to an output stream
 *
 * @param out Output stream to write to
 *
 * Writes:
 * - Player name
 * - Coin count
 * - Number of chains
 * - Chain contents
 * - Hand contents
 */
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

/**
 * @brief Stream insertion operator for Player
 *
 * @param out Output stream
 * @param player Player to output
 * @return Reference to the output stream
 *
 * Prints player name, coins, and chains in a formatted layout.
 */
std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << std::left << player.name << "\t" << player.coins << " coins\n";

    for (const auto &chain : player.chains)
    {
        if (chain)
        {
            out << chain->getType() << "\t";
            chain->print(out);
            out << "\n";
        }
        else
        {
            out << "empty\t\n";
        }
    }

    return out;
}

/**
 * @brief Adds a card to the front of the player's hand
 *
 * @param card Unique pointer to the card to add
 * @throws std::runtime_error if card is null
 */
void Player::addToFrontOfHand(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::runtime_error("Cannot add null card to hand");
    }
    hand.addToFront(std::move(card));
}