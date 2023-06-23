#include "data_controller.hpp"

#ifndef EDITEURTXTAPP_H
#define EDITEURTXTAPP_H

class View : public wxApp {
public:
    virtual bool OnInit();
};

// Classe avec l'écran principal
class TexteFrame : public wxFrame {
public:
    // constructeur
    TexteFrame( const wxString titre, int xpos, int ypos,
               int width, int height);

    // destructeur
    ~TexteFrame();

    // Menu Fichier | Ouvrir
    void OnFichierOuvrir(wxCommandEvent &event);
    // Menu Fichier | Sauvegarder
    void OnFichierSauvegarderSous(wxCommandEvent &event);
    // Menu Fichier | Quitter
    void OnFichierQuitter(wxCommandEvent &event);
    // Menu Info | Apropos
    void OnInfoApropos(wxCommandEvent &event);
	// Menu Info | Aide
	void OnAide(wxCommandEvent &event);
	// Choices
	void OnChoix(wxCommandEvent &event);

// Déclaration de table d'événements
protected:
    DECLARE_EVENT_TABLE();

private:
	wxBoxSizer *sizer;
	wxPanel *panel_title;
	wxPanel *panel_body;
	wxPanel *panel_footer;
    wxStaticText *leTexte;
	wxTextCtrl *leTexte1;
	wxChoice* choice;
    wxMenuBar *menuBar;
    wxMenu *fichierMenu;
    wxMenu *infoMenu;
	wxTextCtrl *massa;
	wxButton *button3;
	data_controller controller;

// ID pour les événements
    enum {
        ID_QUITTER = 100,
        ID_OUVRIR,
        ID_SAUVEGARDER_SOUS,
        ID_APROPOS,
		ID_AIDE,
		ID_MENU,
		ID_CHOICES
    };

};

// Classe pour les boîtes de dialogue de chaque option
class TestDialogue: public wxDialog{
public:
    TestDialogue(
        wxWindow *parent,
        wxWindowID id,
        const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
		const wxString &dimensions = "",
        long style = wxDEFAULT_DIALOG_STYLE

    );
    wxString GetText();
protected:
    DECLARE_EVENT_TABLE();
private:
    wxTextCtrl * dialogTexte;
    void OnOk( wxCommandEvent &event );
};

#endif
