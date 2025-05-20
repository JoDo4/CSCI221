#ifndef HAND_H
#define HAND_H
#include "card.hpp"
#include <vector>

using namespace std;

class Hand {
    private:
      Card * head;
      Card * left_b;
      Card * right_b;
    
    public:
      Hand();

      ~Hand();

      bool isEmpty();

      void push(Card * new_card);

      int size();

      Card * delete_node(std::string name, std::string suit);

      Card * pop();

      void print();

      void sort();

      bool checkSuit(std::string led, std::string suit, string trump, vector<Card*> &list, string name);

};

#endif