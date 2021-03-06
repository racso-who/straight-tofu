#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "observer.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
    View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method
	void reset();
    
private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;
    
	// Card Images
	DeckGUI deck;
    
	// Member widgets:
	
	Gtk::Frame table, p1, p2, p3, p4, hand;
	Gtk::VBox panels, mainBox, p1Box, p2Box, p3Box, p4Box,tableBox;      // Main window divided into two vertical panels
	Gtk::HBox rows[4];
	Gtk::HBox handBox, butBox, playerBox;      // Vertical boxes for stacking buttons horizontally
	Gtk::Button handButtons[13];				//buttons for active player hand
	Gtk::Image handCards[13];					//images for each hand button
	Gtk::Button start_button;					//start game button
	Gtk::Button end_button;						//end game button
	Gtk::Button pRage[4];						//ragequit/playertype buttons
	Gtk::Image tableCards[4][13];				//images for cards in play
	Gtk::Image blankCard;
	Gtk::Entry seedEntry;						//entry box for random seed
	Gtk::Label pPoint[4];						//player point labels
    Gtk::Label pDiscard[4];						//player discard labels
    
    // Signal handlers:
	void startButtonClicked();
	void endButtonClicked();
    void p1RageButtonClicked();
    void p2RageButtonClicked();
    void p3RageButtonClicked();
    void p4RageButtonClicked();
    void hand1ButtonClicked();
    void hand2ButtonClicked();
    void hand3ButtonClicked();
    void hand4ButtonClicked();
    void hand5ButtonClicked();
    void hand6ButtonClicked();
    void hand7ButtonClicked();
    void hand8ButtonClicked();
    void hand9ButtonClicked();
    void hand10ButtonClicked();
    void hand11ButtonClicked();
    void hand12ButtonClicked();
    void hand13ButtonClicked();
	void resetTable();
	void resetHand();
    
}; // View

#endif
