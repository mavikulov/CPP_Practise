#pragma once

#include <array>
#include <stdexcept>
#include <vector>
#include <deque>

enum class Winner { kFirst, kSecond, kNone };

struct GameResult {
    Winner winner;
    int turn;
};

int CompareCards(int card1, int card2) {
    if (card1 == 0 && card2 == 11) {
        return 1;
    } else if (card1 == 11 && card2 == 0) {
        return 2;
    } else if (card1 > card2) {
        return 1;
    } else {
        return 2;
    }
}

GameResult SimulateWarGame(const std::array<int, 6>& first_deck,
                           const std::array<int, 6>& second_deck) {
    GameResult result;
    int rounds = 0;
    std::deque<int> deck1, deck2;
    for (const auto& elem : first_deck) {
        deck1.push_back(elem);
    }
    for (const auto& elem : second_deck) {
        deck2.push_back(elem);
    }
    while (!deck1.empty() && !deck2.empty() && rounds != 1000000) {
        int card1 = deck1.front();
        int card2 = deck2.front();
        deck1.pop_front();
        deck2.pop_front();
        int winner = CompareCards(card1, card2);
        if (winner == 1) {
            deck1.push_back(card1);
            deck1.push_back(card2);
        } else {
            deck2.push_back(card1);
            deck2.push_back(card2);
        }
        rounds++;
    }
    if (deck1.empty()) {
        result.winner = Winner::kSecond;
        result.turn = rounds;
        return result;
    } else if (deck2.empty()) {
        result.winner = Winner::kFirst;
        result.turn = rounds;
        return result;
    } else {
        result.winner = Winner::kNone;
        result.turn = rounds;
        return result;
    }
}
