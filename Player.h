#ifndef __straight_tofu__Player__
#define __straight_tofu__Player__

#include <vector>
#include <string>
#include "Card.h"
#include <iostream>
using namespace std;

class Player{
public:
	Player(int);
    int getScore() const;                   // accessor
	vector<Card> getHand() const;           // accessor
    bool hasCard(Card) const;
	void addCard(Card);                     // mutator
    void discard(Card);                     // mutator
    void addHand(vector<Card>);             // mutator
	vector<Card> getPlays(vector<Card>);	// return valid plays
	void addScore(int);                     // mutator
	void reset();
	virtual void turn(vector<Card> &) = 0;
	void play(Card&, vector<Card> &);
protected:
	vector<Card> hand_;
	vector<Card> discardPile_;
	int score_ = 0;
	int playerNumber_;
private:
    int cardPos(Card) const;                // helper to find position of card
};
class ragequit_exception :exception
{
public:
	ragequit_exception(vector<Card> hand, vector<Card> discard, int score){
		hand_ = hand;
		discard_ = discard;
		score_ = score;
	}
	vector<Card> hand_;
	vector<Card> discard_;
	int score_;
};
#endif /* defined(__straight_tofu__Player__) */
