#include "Hand.h"
#include <stdexcept>
#include "CardFactory.h"
#include <sstream>

Hand::Hand(std::istream &in, const CardFactory *factory)
{
    cards.clear();
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_HAND")
        {
            break;
        }

        try
        {
            Card *card = factory->getFactory()->createCard(cardName);
            if (card)
            {
                *this += card; // Use operator+= to maintain sorting
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading hand card: " << e.what() << std::endl;
        }
    }
}

Hand &Hand::operator+=(Card *card)
{
    if (card == nullptr)
    {
        throw std::invalid_argument("Cannot add null card to hand");
    }

    // Add card to back of list (rear of hand)
    cards.push_back(card);
    return *this;
}

Card *Hand::play()
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot play from empty hand");
    }

    // Remove and return first card (front of hand)
    Card *topCard = cards.front();
    cards.pop_front();
    return topCard;
}

Card *Hand::top() const
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot get top card from empty hand");
    }

    return cards.front();
}

void Hand::validateIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(cards.size()))
    {
        std::ostringstream oss;
        oss << "Index " << index << " is out of range. Hand size is " << cards.size();
        throw std::out_of_range(oss.str());
    }
}

Card *Hand::operator[](int index)
{
    validateIndex(index);

    // Find the card at the specified index
    auto it = cards.begin();
    std::advance(it, index);

    // Remove and return the card
    Card *card = *it;
    cards.erase(it);
    return card;
}

std::ostream &operator<<(std::ostream &out, const Hand &hand)
{
    out << "Hand: ";
    for (const auto &card : hand.cards)
    {
        card->print(out);
        out << " ";
    }
    return out;
}

Hand::~Hand()
{

    std::cout << "Hand destructor start\n";
    try
    {
        std::cout << "Starting to clear cards...\n";
        if (!cards.empty())
        {
            cards.clear(); // Just clear the list, don't delete the cards
        }
        std::cout << "Cards cleared successfully\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error clearing hand: " << e.what() << "\n";
    }
    std::cout << "Hand destructor end\n";
}

Hand::Hand(Hand &&other) noexcept
    : cards(std::move(other.cards))
{
    other.cards.clear();
}

Hand &Hand::operator=(Hand &&other) noexcept
{
    if (this != &other)
    {
        // Clean up existing cards
        for (Card *card : cards)
        {
            delete card;
        }
        cards = std::move(other.cards);
        other.cards.clear();
    }
    return *this;
}

void Hand::serialize(std::ostream &out) const
{
    // Write number of cards
    for (const Card *card : cards)
    {
        if (card)
        {
            out << card->getName() << "\n";
        }
    }
    out << "END_HAND\n";
}