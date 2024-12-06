#include "Hand.h"
#include <stdexcept>
#include "CardFactory.h"
#include <sstream>

/**
 * @brief Constructs a Hand from a saved game state
 *
 * @param in Input stream containing serialized hand data
 * @param factory Pointer to the CardFactory used to create cards
 *
 * Reads card names from the input stream until "END_HAND" is encountered.
 * Each card is recreated using the provided CardFactory.
 */
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
            // Create card from saved name using factory
            auto card = factory->getFactory()->createCard(cardName);
            if (card)
            {
                *this += std::move(card);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading hand card: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Adds a card to the back of the hand
 *
 * @param card Unique pointer to the card being added
 * @return Reference to the modified Hand
 * @throws std::invalid_argument if card pointer is null
 */
Hand &Hand::operator+=(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to hand");
    }

    // Add card to back of list (rear of hand)
    cards.push_back(std::move(card));
    return *this;
}

/**
 * @brief Plays and removes the first card from the hand
 *
 * @return Unique pointer to the played card
 * @throws std::runtime_error if the hand is empty
 */
std::unique_ptr<Card> Hand::play()
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot play from empty hand");
    }

    // Remove and return first card (front of hand)
    std::unique_ptr<Card> topCard = std::move(cards.front());
    cards.pop_front();
    return topCard;
}

/**
 * @brief Adds a card to the front of the hand
 *
 * @param card Unique pointer to the card being added
 */
void Hand::addToFront(std::unique_ptr<Card> card)
{
    cards.push_front(std::move(card));
}

/**
 * @brief Returns a pointer to the first card without removing it
 *
 * @return Raw pointer to the first card
 * @throws std::runtime_error if the hand is empty
 */
const Card *Hand::top() const
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot get top card from empty hand");
    }

    return cards.front().get();
}

/**
 * @brief Validates if an index is within the bounds of the hand
 *
 * @param index Index to validate
 * @throws std::out_of_range if index is invalid
 */
void Hand::validateIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(cards.size()))
    {
        std::ostringstream oss;
        oss << "Index " << index << " is out of range. Hand size is " << cards.size();
        throw std::out_of_range(oss.str());
    }
}

/**
 * @brief Removes and returns the card at the specified index
 *
 * @param index Position of the card to remove (0-based)
 * @return Unique pointer to the removed card
 * @throws std::out_of_range if index is invalid
 */
std::unique_ptr<Card> Hand::operator[](int index)
{
    validateIndex(index);

    // Find the card at the specified index
    auto it = std::next(cards.begin(), index);

    // Move ownership of the card and remove it from the list
    std::unique_ptr<Card> card = std::move(*it);
    cards.erase(it);
    return card;
}

/**
 * @brief Stream insertion operator for Hand
 *
 * @param out Output stream
 * @param hand Hand to output
 * @return Reference to the output stream
 *
 * Prints all cards in the hand with spaces between them.
 */
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

/**
 * @brief Serializes the hand to an output stream
 *
 * @param out Output stream to write to
 *
 * Writes each card's name followed by a newline.
 * Ends with "END_HAND" marker.
 */
void Hand::serialize(std::ostream &out) const
{
    for (const auto &card : cards)
    {
        if (card)
        {
            out << card->getName() << "\n";
        }
    }
    out << "END_HAND\n";
}