#include <iostream>
#include <fstream>
#include <sstream>
#include "deal.hpp"
#include "hand.hpp"
#include "card.hpp"

using namespace std;

#define MAX_SIZE 4

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Not enough arguments." << endl;
        exit(1);
    }
    string file = argv[1];
    vector<Card *> deck;
    deck.reserve(24);

    get_deck(file, deck);

    shuffle(deck);

    Hand players[MAX_SIZE];
    int ordered = 0;

    deal_hand(deck, players, MAX_SIZE);
    sort_hands(players, MAX_SIZE);

    for (int i = 0; i < MAX_SIZE; i++) {
        players[i].print();
    }

    cout << bid(players, MAX_SIZE, deck, 0, ordered) << endl;

    for (int i = 0; i < MAX_SIZE; i++) {
        players[i].print();
    }

    for (int i = 0; i < (int)deck.size(); i++) {
        deck[i]->display();
    }
    cout << endl;

    collect(players, deck, MAX_SIZE);

    stow_deck(file, deck);
}