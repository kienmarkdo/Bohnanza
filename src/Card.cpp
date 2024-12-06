#include "Card.h"

/**
 * @brief Overload of the stream insertion operator for Card objects.
 *        Prints the card using its print method.
 * @param out The output stream.
 * @param card The card to print.
 * @return Reference to the output stream for chaining.
 */
std::ostream &operator<<(std::ostream &out, const Card &card)
{
    card.print(out);
    return out;
}

// The following implementations define how many cards are needed per coin for each bean type.

// Blue Bean implementation
int Blue::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 4;
    case 2: return 6;
    case 3: return 8;
    case 4: return 10;
    default: return 0;
    }
}

// Chili Bean implementation
int Chili::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 3;
    case 2: return 6;
    case 3: return 8;
    case 4: return 9;
    default: return 0;
    }
}

// Stink Bean implementation
int Stink::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 3;
    case 2: return 5;
    case 3: return 7;
    case 4: return 8;
    default: return 0;
    }
}

// Green Bean implementation
int Green::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 3;
    case 2: return 5;
    case 3: return 6;
    case 4: return 7;
    default: return 0;
    }
}

// Soy Bean implementation
int Soy::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 2;
    case 2: return 4;
    case 3: return 6;
    case 4: return 7;
    default: return 0;
    }
}

// Black Bean implementation
int Black::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 2;
    case 2: return 4;
    case 3: return 5;
    case 4: return 6;
    default: return 0;
    }
}

// Red Bean implementation
int Red::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 1: return 2;
    case 2: return 3;
    case 3: return 4;
    case 4: return 5;
    default: return 0;
    }
}

// Garden Bean implementation
int Garden::getCardsPerCoin(int coins) const
{
    switch (coins)
    {
    case 2: return 2;
    case 3: return 3;
    default: return 0;
    }
}
