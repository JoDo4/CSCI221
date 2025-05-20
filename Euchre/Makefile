CC = g++
CFLAGS = -Wall -std=c++14

# All the driver programs
card_hand_test : card_hand_test.o card.o hand.o
	$(CC) $(CFLAGS) card_hand_test.o card.o hand.o -o card_hand_test

card_hand_test.o : card_hand_test.cpp card.hpp hand.hpp
	$(CC) $(CFLAGS) -c card_hand_test.cpp

deal_hand : deal_hand.o card.o hand.o
	$(CC) $(CFLAGS) deal_hand.o card.o hand.o -o deal_hand
	
deal_hand.o : deal_hand.cpp card.hpp hand.hpp
	$(CC) $(CFLAGS) -c deal_hand.cpp

bid_driver : bid_driver.o card.o hand.o deal.o
	$(CC) $(CFLAGS) bid_driver.o card.o hand.o deal.o -o bid_driver
	
bid_driver.o : bid_driver.cpp card.hpp hand.hpp deal.hpp
	$(CC) $(CFLAGS) -c bid_driver.cpp

play : play.o card.o hand.o deal.o
	$(CC) $(CFLAGS) play.o card.o hand.o deal.o -o play
play.o : play.cpp card.hpp hand.hpp deal.hpp
	$(CC) $(CFLAGS) -c play.cpp

# All the hpp files
deal.o : deal.cpp card.hpp hand.hpp deal.hpp
	$(CC) $(CFLAGS) -c deal.cpp

card.o : card.cpp card.hpp
	$(CC) $(CFLAGS) -c card.cpp

hand.o : hand.cpp hand.hpp card.hpp 
	$(CC) $(CFLAGS) -c hand.cpp

clean:
	rm *.o card_hand_test