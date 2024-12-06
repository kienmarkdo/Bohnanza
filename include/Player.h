#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Hand.h"
#include "Chain.h"

/**
 * @brief Exception thrown when a player cannot afford to buy a third chain
 */
class NotEnoughCoins : public std::exception
{
public:
    /**
     * @brief Returns the error message
     * @return Const char pointer to the error message
     * @note This method is noexcept as required by std::exception
     */
    const char *what() const noexcept override
    {
        return "Not enough coins to buy third chain";
    }
};

/**
 * @brief Represents a player in the bean trading card game
 * @details The Player class manages a player's hand, chains of cards, and coins.
 *          It handles all player-specific operations including chain management,
 *          card playing, and coin transactions.
 */
class Player
{
public:
    /**
     * @brief Constructs a new player with the given name
     * @param name The player's name
     */
    Player(const std::string &name);

    /**
     * @brief Constructs a player from a saved game state
     * @param in Input stream containing the saved state
     * @param factory Pointer to the card factory for card creation
     */
    Player(std::istream &in, const CardFactory *factory);

    /** @brief Gets the player's name */
    std::string getName() const { return name; }

    /** @brief Gets the number of coins the player has */
    int getNumCoins() const { return coins; }

    /**
     * @brief Gets the maximum number of chains the player can have
     * @return 3 if player has bought third chain, otherwise 2
     */
    int getMaxNumChains() const { return (chains.size() >= 3) ? 3 : 2; }

    /** @brief Gets the current number of active chains */
    int getNumChains() const;

    /**
     * @brief Accesses a chain by index
     * @param i Index of the chain to access
     * @return Reference to the chain at the given index
     * @throws std::out_of_range if index is invalid
     */
    Chain_Base &operator[](int i);
    const Chain_Base &operator[](int i) const;

    /**
     * @brief Purchases a third chain for the player
     * @throws NotEnoughCoins if player cannot afford the third chain
     */
    void buyThirdChain();

    /**
     * @brief Adds a card to the player's hand
     * @param card Unique pointer to the card to add
     */
    void addToHand(std::unique_ptr<Card> card) { hand += std::move(card); }

    /** @brief Plays the top card from the player's hand */
    std::unique_ptr<Card> playFromHand() { return hand.play(); }

    /**
     * @brief Gets a card from the player's hand at specified index
     * @param index Index of the card to retrieve
     * @return Unique pointer to the card
     */
    std::unique_ptr<Card> getCardFromHand(int index) { return hand[index]; }

    /** @brief Gets the top card from the player's hand without removing it */
    const Card *getTopCardFromHand() const { return hand.top(); }

    /** @brief Checks if the player's hand is empty */
    bool isHandEmpty() const { return hand.empty(); }

    /**
     * @brief Adds a card to the front of the player's hand
     * @param card Unique pointer to the card to add
     */
    void addToFrontOfHand(std::unique_ptr<Card> card);

    /**
     * @brief Adds coins to the player's total
     * @param additionalCoins Number of coins to add
     * @return Reference to this player
     */
    Player &operator+=(int additionalCoins);

    /**
     * @brief Harvests a chain of specific card type
     * @tparam T Type of card in the chain
     * @return Number of coins earned from harvesting
     */
    /**
     * @brief Harvests a chain of specific card type
     * @tparam T Type of card in the chain
     * @return Number of coins earned from harvesting
     */
    template <typename T>
    int harvestChain()
    {
        for (size_t i = 0; i < chains.size(); i++)
        {
            if (auto *chain = dynamic_cast<Chain<T> *>(chains[i].get()))
            {
                int harvestedCoins = chain->sell();
                *this += harvestedCoins;
                chains[i] = nullptr; // Reset the chain
                return harvestedCoins;
            }
        }
        return 0;
    }

    /**
     * @brief Finds a chain of specific card type
     * @tparam T Type of card to find chain for
     * @return Pointer to the found chain, nullptr if not found
     */
    template <typename T>
    Chain<T> *findChainOfType()
    {
        for (auto &chain : chains)
        {
            if (chain)
            {
                if (auto typedChain = dynamic_cast<Chain<T> *>(chain.get()))
                {
                    return typedChain;
                }
            }
        }
        return nullptr;
    }

    /**
     * @brief Determines if a chain should be harvested
     * @tparam T Type of card in the chain
     * @return true if chain should be harvested, false otherwise
     */
    template <typename T>
    bool shouldHarvestChain()
    {
        if (auto chain = findChainOfType<T>())
        {
            if (const Card *firstCard = chain->getFirstCard())
            {
                if (const T *typedCard = dynamic_cast<const T *>(firstCard))
                {
                    // Get maximum cards per coin value for this type
                    int maxCards = 0;
                    for (int coins = 4; coins > 0; --coins)
                    {
                        int cardsNeeded = typedCard->getCardsPerCoin(coins);
                        if (cardsNeeded > 0)
                        {
                            maxCards = cardsNeeded;
                            break;
                        }
                    }
                    return (maxCards > 0 && chain->size() >= maxCards);
                }
            }
        }
        return false;
    }

    /**
     * @brief Adds a card to a chain of matching type
     * @tparam T Type of card to add
     * @param card Unique pointer to the card to add
     * @return Reference to the chain the card was added to
     * @throws std::runtime_error if no available chain slots
     */
    template <typename T>
    Chain<T> &addCardToChain(std::unique_ptr<Card> card)
    {
        // Check if current chain should be harvested
        if (shouldHarvestChain<T>())
        {
            harvestChain<T>();
        }

        // Try to find existing chain or create new one
        if (auto existingChain = findChainOfType<T>())
        {
            *existingChain += std::move(card);
            return *existingChain;
        }

        // Look for empty slot
        for (auto &chain : chains)
        {
            if (!chain)
            {
                chain = std::make_unique<Chain<T>>();
                *chain += std::move(card);
                return *dynamic_cast<Chain<T> *>(chain.get());
            }
        }
        throw std::runtime_error("No available chain slots");
    }

    /**
     * @brief Prints the player's hand
     * @param out Output stream to print to
     * @param all If true, prints all cards; if false, prints only top card
     */
    void printHand(std::ostream &out, bool all) const;

    /**
     * @brief Serializes the player's state
     * @param out Output stream to serialize to
     */
    void serialize(std::ostream &out) const;

    /**
     * @brief Outputs the player's state to a stream
     * @param out Output stream
     * @param player Player to output
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Player &player);

    /** @brief Default destructor */
    ~Player() = default;

private:
    std::string name;                                ///< Player's name
    int coins = 0;                                   ///< Number of coins the player has
    Hand hand;                                       ///< Player's hand of cards
    std::vector<std::unique_ptr<Chain_Base>> chains; ///< Player's card chains

    /**
     * @brief Validates a chain index
     * @param index Index to validate
     * @throws std::out_of_range if index is invalid
     */
    void validateChainIndex(int index) const;
};

#endif // PLAYER_H