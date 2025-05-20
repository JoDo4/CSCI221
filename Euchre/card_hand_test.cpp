#include <iostream>
#include <fstream>
#include "card.hpp"
#include "hand.hpp"

using namespace std;



int main() {
    Hand my_hand;
    Card * card1 = new Card("9", "Hearts", 1);
    Card * card2 = new Card("Jack", "Diamond", 3);
    Card * card3 = new Card("10", "Spades", 2);
    Card * card4 = new Card("10", "Clubs", 2);
    Card * card5 = new Card("Queen", "Clubs", 4);

    my_hand.push(card1);
    my_hand.push(card5);
    my_hand.push(card2);
    my_hand.push(card4);
    my_hand.push(card3);

    my_hand.print();

    my_hand.sort();

    my_hand.print();

    my_hand.delete_node("10", "Spades");
    my_hand.delete_node("9", "Hearts");
    my_hand.delete_node("Jack", "Diamond");
    my_hand.delete_node("10", "Spades");
    my_hand.delete_node("10", "Clubs");
    my_hand.delete_node("Queen", "Clubs");
    my_hand.print();

}