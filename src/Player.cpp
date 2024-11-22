#include "Player.h"

// Constructor: Creates a Player with a given name
Player::Player(const std::string &playerName)
    : name(playerName), coins(0), maxChains(2) {}

// Constructor: Reconstructs a Player from a file
Player::Player(std::istream &in, const CardFactory *factory)
{
    std::getline(in, name); // Read the player's name
    in >> coins;            // Read the player's coins
    in >> maxChains;        // Read the maximum number of chains
    int numChains;
    in >> numChains; // Read the number of existing chains
    chains.resize(numChains, nullptr);

    for (int i = 0; i < numChains; ++i)
    {
        std::string chainType;
        in >> chainType;
        if (chainType == "Red")
        {
            chains[i] = new Chain<Red>(in, factory);
        }
        else if (chainType == "Blue")
        {
            chains[i] = new Chain<Blue>(in, factory);
        } // Add more types as needed
    }

    hand = Hand(in, factory); // Reconstruct the player's hand
}

// Get the name of the player
std::string Player::getName() const
{
    return name;
}

// Get the number of coins
int Player::getNumCoins() const
{
    return coins;
}

// Add coins to the player
Player &Player::operator+=(int numCoins)
{
    coins += numCoins;
    return *this;
}

// Get the maximum number of chains
int Player::getMaxNumChains() const
{
    return maxChains;
}

// Get the number of non-empty chains
int Player::getNumChains() const
{
    int count = 0;
    for (const auto &chain : chains)
    {
        if (chain && chain->sell() > 0)
        { // Check if the chain has any cards
            ++count;
        }
    }
    return count;
}

// Access the chain at position i
Chain_Base &Player::operator[](int i)
{
    if (i < 0 || i >= chains.size())
    {
        throw std::out_of_range("Invalid chain index");
    }
    return *chains[i];
}

// Buy a third chain (reduces coins, throws exception if not enough coins)
void Player::buyThirdChain()
{
    if (maxChains == 3)
    {
        throw std::logic_error("Player already has three chains");
    }
    if (coins < 3)
    {
        throw std::logic_error("NotEnoughCoins: Player does not have enough coins");
    }
    coins -= 3;
    maxChains = 3; // Update the maximum chains to 3
}

// Print the player's hand
void Player::printHand(std::ostream &out, bool showAll) const
{
    if (showAll)
    {
        // Use the stream insertion operator of Hand to print all cards
        out << hand;
    }
    else
    {
        // Manually print only the top card
        Card *topCard = hand.top();
        if (topCard)
        {
            topCard->print(out);
        }
        else
        {
            out << "Hand is empty.";
        }
    }
}

// Stream insertion operator to print a Player
std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << player.name << "\t" << player.coins << " coins" << std::endl;
    for (const auto &chain : player.chains)
    {
        if (chain)
        {
            out << *chain; // Print each chain
        }
        else
        {
            out << "Empty chain" << std::endl;
        }
    }
    return out;
}