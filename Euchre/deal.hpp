#ifndef DEAL_H
#define DEAL_H
#include "card.hpp"
#include "hand.hpp"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool get_deck(string deck_name,vector<Card *> &deck);

void stow_deck(string deck_name, vector<Card *> &deck);

void shuffle(vector<Card *> &deck);

void sort_hands(Hand hands[], int size);

void deal_hand(vector<Card *> &deck, Hand hands[], int size);

void collect(Hand hands[], vector<Card *> &deck, int size);

void print_for_bidding(Hand hands[], int size, vector<Card *> &deck, int dealer);

string bid(Hand hands[], int size, vector<Card *> &deck, int dealer, int &ordered);

#endif