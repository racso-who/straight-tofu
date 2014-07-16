#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include <iostream>

View::View(Controller *c, Model *m) : model_(m), controller_(c), mainBox(false, 1), playerBox(true, 1), table("Cards on the table"), p1("Player 1"), p2("Player 2"), p3("Player 3"), p4("Player 4"), p1Box(true, 5), p2Box(true, 10), p3Box(true, 10), p4Box(true, 10), hand("Your hand"), panels(true,10), handBox(true, 1), butBox(false, 1), start_button( "Start new game with seed:" ), end_button( "End current game" ), p1Rage("Human"), p2Rage("Human"), p3Rage("Human"), p4Rage("Human"), p1Point("0 points"), p1Discard("0 discards"), p2Point("0 points"), p2Discard("0discards"), p3Point("0 points"), p3Discard("0 discards"), p4Point("0 points"), p4Discard("0 discards"),tableBox(true,5){

	blankCard.set(deck.null());
	// Sets some properties of the window.
    set_title( "Straights" );
	set_border_width( 10 );
	add(mainBox);
	mainBox.add(butBox);
	butBox.add(start_button);

	seedEntry.set_max_length(10);
	seedEntry.select_region(0, seedEntry.get_text_length());
	butBox.add(seedEntry);
	butBox.add(end_button);

	// middle table
	mainBox.add(table);
	for(int j=0;j<4;j++){
		for(int i=0;i<13;i++){
		rows[j].add(tableCards[j][i]);
		tableCards[j][i].set(deck.null());
		}
	}
	for(int z=0;z<4;z++){
	tableBox.add(rows[z]);
	}
	table.add(tableBox);
	// player section
	mainBox.add(playerBox);
	playerBox.add(p1);
	p1.add(p1Box);
	p1Box.add(p1Rage);
	p1Box.add(p1Point);
	p1Box.add(p1Discard);
	playerBox.add(p2);
	p2.add(p2Box);
	p2Box.add(p2Rage);
	p2Box.add(p2Point);
	p2Box.add(p2Discard);
	playerBox.add(p3);
	p3.add(p3Box);
	p3Box.add(p3Rage);
	p3Box.add(p3Point);
	p3Box.add(p3Discard);
	playerBox.add(p4);
	p4.add(p4Box);
	p4Box.add(p4Rage);
	p4Box.add(p4Point);
	p4Box.add(p4Discard);

	// area for your hand
	mainBox.add(hand);
	hand.add(handBox);
	for(int l=0;l<13;l++)
	{
		handBox.add(handButtons[l]);
		handButtons[l].set_image(handCards[l]);
		handCards[l].set(deck.null());
	}
	// Associate button "clicked" events with local onButtonClicked() method defined below.
	start_button.signal_clicked().connect( sigc::mem_fun( *this, &View::startButtonClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &View::endButtonClicked ) );
	p1Rage.signal_clicked().connect( sigc::mem_fun( *this, &View::p1RageButtonClicked ) );
	p2Rage.signal_clicked().connect( sigc::mem_fun( *this, &View::p2RageButtonClicked ) );
	p3Rage.signal_clicked().connect( sigc::mem_fun( *this, &View::p3RageButtonClicked ) );
	p4Rage.signal_clicked().connect( sigc::mem_fun( *this, &View::p4RageButtonClicked ) );
	handButtons[0].signal_clicked().connect( sigc::mem_fun( *this, &View::hand1ButtonClicked ) );
	handButtons[1].signal_clicked().connect( sigc::mem_fun( *this, &View::hand2ButtonClicked ) );
	handButtons[2].signal_clicked().connect( sigc::mem_fun( *this, &View::hand3ButtonClicked ) );
	handButtons[3].signal_clicked().connect( sigc::mem_fun( *this, &View::hand4ButtonClicked ) );
	handButtons[4].signal_clicked().connect( sigc::mem_fun( *this, &View::hand5ButtonClicked ) );
	handButtons[5].signal_clicked().connect( sigc::mem_fun( *this, &View::hand6ButtonClicked ) );
	handButtons[6].signal_clicked().connect( sigc::mem_fun( *this, &View::hand7ButtonClicked ) );
	handButtons[7].signal_clicked().connect( sigc::mem_fun( *this, &View::hand8ButtonClicked ) );
	handButtons[8].signal_clicked().connect( sigc::mem_fun( *this, &View::hand9ButtonClicked ) );
	handButtons[9].signal_clicked().connect( sigc::mem_fun( *this, &View::hand10ButtonClicked ) );
	handButtons[10].signal_clicked().connect( sigc::mem_fun( *this, &View::hand11ButtonClicked ) );
	handButtons[11].signal_clicked().connect( sigc::mem_fun( *this, &View::hand12ButtonClicked ) );
	handButtons[12].signal_clicked().connect( sigc::mem_fun( *this, &View::hand13ButtonClicked ) );
	
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update() {
	vector<Card> hand=model_->getActivePlayerHand();
	for(int i=0;i<hand.size();i++)
	{
		handCards[i].set(deck.image(hand[i].getRank(),hand[i].getSuit()));	
	}
}

void View::startButtonClicked() {
	p1Rage.set_label("Rage!");
	p1Rage.set_sensitive(false);
	p2Rage.set_label("Rage!");
	p2Rage.set_sensitive(false);
	p3Rage.set_label("Rage!");
	p3Rage.set_sensitive(false);
	p4Rage.set_label("Rage!");
	p4Rage.set_sensitive(false);
	char playerType[4];
	playerType[0]=(p1Rage.get_label()=="Human"?'h':'c');
	playerType[1]=(p2Rage.get_label()=="Human"?'h':'c');
	playerType[2]=(p3Rage.get_label()=="Human"?'h':'c');
	playerType[3]=(p4Rage.get_label()=="Human"?'h':'c');
	start_button.set_sensitive(false);
  controller_->startButtonClicked(playerType);
} // View::startButtonClicked
void View::endButtonClicked() {
	start_button.set_sensitive(true);
  controller_->endButtonClicked();
} // View::endButtonClicked

void View::p1RageButtonClicked() {
	if(p1Rage.get_label()=="Human")
		p1Rage.set_label("Computer");
	else if(p1Rage.get_label()=="Computer")
		p1Rage.set_label("Human");
    controller_->rageButtonClicked();
	
}
void View::p2RageButtonClicked() {
	if(p2Rage.get_label()=="Human")
		p2Rage.set_label("Computer");
	else if(p2Rage.get_label()=="Computer")
		p2Rage.set_label("Human");
	else
	    controller_->rageButtonClicked();
}
void View::p3RageButtonClicked() {
	if(p3Rage.get_label()=="Human")
		p3Rage.set_label("Computer");
	else if(p3Rage.get_label()=="Computer")
		p3Rage.set_label("Human");
	else
	    controller_->rageButtonClicked();
}
void View::p4RageButtonClicked() {
	if(p4Rage.get_label()=="Human")
		p4Rage.set_label("Computer");
	else if(p4Rage.get_label()=="Computer")
		p4Rage.set_label("Human");
	else
	    controller_->rageButtonClicked();
}
void View::hand1ButtonClicked() {
    controller_->hand1ButtonClicked();
}
void View::hand2ButtonClicked() {
    controller_->hand2ButtonClicked();
}
void View::hand3ButtonClicked() {
    controller_->hand3ButtonClicked();
}
void View::hand4ButtonClicked() {
    controller_->hand4ButtonClicked();
}
void View::hand5ButtonClicked() {
    controller_->hand5ButtonClicked();
}
void View::hand6ButtonClicked() {
    controller_->hand6ButtonClicked();
}
void View::hand7ButtonClicked() {
    controller_->hand7ButtonClicked();
}
void View::hand8ButtonClicked() {
    controller_->hand8ButtonClicked();
}
void View::hand9ButtonClicked() {
    controller_->hand9ButtonClicked();
}
void View::hand10ButtonClicked() {
    controller_->hand10ButtonClicked();
}
void View::hand11ButtonClicked() {
    controller_->hand11ButtonClicked();
}
void View::hand12ButtonClicked() {
    controller_->hand12ButtonClicked();
}
void View::hand13ButtonClicked() {
    controller_->hand13ButtonClicked();
}
