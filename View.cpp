#include <wx/wx.h>
#include "View.h"
#include "data_controller.hpp"
#include <string>

// Initiation de la fenetre View
IMPLEMENT_APP(View)


bool View::OnInit() {

    // Cr\xc3\xa9er la fenêtre principale.
    // Elle a un nom, un point de d\xc3\xa9part (x,y),
    // une largeur et une hauteur

    const wxString Titre("TP3");

    TexteFrame *frame = new TexteFrame(Titre, 50, 50, 500, 400);

	frame->Center();
	frame->SetBackgroundColour(wxColor(34, 44, 51));
    frame->Show(TRUE);

    SetTopWindow(frame);

    return true;

}

//Constructeur de la classe
TexteFrame::TexteFrame
                (const wxString titre,
                    int xpos, int ypos,
                    int width, int height)
                : wxFrame
                ( (wxFrame *) NULL,
                     -1,
                    titre,
                    wxPoint(xpos, ypos),
                    wxSize(width, height)
                ){



    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    // Initialisation du pointeur \xc3\xa0 la valeur "NULL cast\xc3\xa9e"
    leTexte = (wxStaticText *) NULL;
    menuBar = (wxMenuBar *) NULL;
    fichierMenu = (wxMenu *) NULL;
    infoMenu =  (wxMenu *) NULL;
    panel_title = (wxPanel *) NULL;
	sizer = (wxBoxSizer *) NULL;
	panel_body = (wxPanel *) NULL;
	panel_footer = (wxPanel *) NULL;
	leTexte1 = (wxTextCtrl *) NULL;
	choice = (wxChoice *) NULL;

	// Configuration du layout
	panel_title = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 450));
	panel_title->SetBackgroundColour(wxColor(62, 156, 171));

	wxFont myFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	panel_title->SetFont(myFont);

	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(panel_title, 1, wxEXPAND| wxALL, 5);
	this->SetSizerAndFit(sizer);

	// Message d'initiation
    wxString unechaine =  wxString::FromUTF8("Veuillez ouvrir le fichier diabetes.tab.txt...\n\n");
	leTexte = new wxStaticText(panel_title,wxID_ANY, unechaine, wxDefaultPosition, wxSize(-1, -1));
	leTexte->Center();
	leTexte->SetForegroundColour(wxColor(*wxWHITE));

    //Nous avons cr\xc3\xa9e une instance de wxMenu pour " Fichier "
    fichierMenu = new wxMenu;

    // Nous utilisons les m\xc3\xa9thodes Append() et AppendSeparator()
    // pour ajouter des items et des s\xc3\xa9parateurs d'items au menu
    // " fichierMenu "
    fichierMenu->Append(ID_OUVRIR,  "&Ouvrir fichier");
    fichierMenu->Append(ID_SAUVEGARDER_SOUS, "&Sauvegarder sous (a, b et 𝑅2)");
    fichierMenu->AppendSeparator();
    fichierMenu->Append(ID_QUITTER,  "&Quitter");

    // Place \xc3\xa0 la cr\xc3\xa9ation du menu " Apropos "
    infoMenu = new wxMenu();
	infoMenu->Append(ID_AIDE, "&Aide");
    infoMenu->Append(ID_APROPOS, "&Apropos");

    menuBar = new wxMenuBar;
    menuBar->Append(fichierMenu, "&Fichier");
    menuBar->Append(infoMenu, "&Info");

    SetMenuBar(menuBar);

    // Nous allons ajouter une barre d'\xc3\xa9tat contenant 3 champs \xc3\xa0 notre cadre.
    CreateStatusBar();
}


// Destructeur

TexteFrame::~TexteFrame(){}

//Tableau pour gerer des \xc3\xa9v\xc3\xa9nements
BEGIN_EVENT_TABLE(TexteFrame, wxFrame)
    EVT_MENU(ID_OUVRIR, TexteFrame::OnFichierOuvrir)
    EVT_MENU(ID_SAUVEGARDER_SOUS, TexteFrame::OnFichierSauvegarderSous)
    EVT_MENU(ID_QUITTER, TexteFrame::OnFichierQuitter)
    EVT_MENU(ID_APROPOS, TexteFrame::OnInfoApropos)
	EVT_MENU(ID_AIDE, TexteFrame::OnAide)
	EVT_CHOICE(ID_CHOICES, TexteFrame::OnChoix)
END_EVENT_TABLE()

// Fonction pour ouvrir le fichier
void TexteFrame::OnFichierOuvrir(wxCommandEvent &event){
    wxFileDialog *dlg = new wxFileDialog(this, "Ouvrir un fichier texte", "", "",
        "Fichiers textes(*.txt)|*.txt", wxFD_OPEN, wxDefaultPosition);

    if ( dlg->ShowModal() == wxID_OK ){
        wxString fileName = dlg->GetFilename();
		if (fileName.ToStdString() == "diabetes.tab.txt"){
			if(!controller.init){
				panel_title->Destroy();

				panel_title = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 50));
				panel_title->SetBackgroundColour(wxColor(62, 156, 171));

				wxFont myFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
				panel_title->SetFont(myFont);

				panel_body = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 330));
				panel_body->SetBackgroundColour(wxColor(150, 230, 242));

				panel_footer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 30));
				panel_footer->SetBackgroundColour(wxColor(62, 156, 171));

				sizer = new wxBoxSizer(wxVERTICAL);
				sizer->Add(panel_title, 0, wxEXPAND| wxLEFT | wxTOP | wxRIGHT, 5);
				sizer->Add(panel_body, 1, wxEXPAND| wxLEFT | wxTOP | wxRIGHT, 5);
				sizer->Add(panel_footer, 0, wxEXPAND| wxALL, 5);
				this->SetSizerAndFit(sizer);

				wxStaticText* staticText2 = new wxStaticText(panel_title, wxID_ANY, "Veuillez choisir l'une des options suivantes", wxPoint(20, 20), wxSize(360, 20), wxALIGN_CENTRE);
				staticText2->CenterOnParent();
				staticText2->SetForegroundColour(wxColor(*wxWHITE));

				wxStaticText* textBody1 = new wxStaticText(panel_body, wxID_ANY, "[1] Description de l’ensemble de donnees", wxPoint(20, 20), wxSize(460, 30));
				wxStaticText* textBody2 = new wxStaticText(panel_body, wxID_ANY,  "[2] L’entête des donnees", wxPoint(20, 50), wxSize(460, 20));
				wxStaticText* textBody3 = new wxStaticText(panel_body, wxID_ANY,  "[3] Queue des donnees", wxPoint(20, 80), wxSize(460, 20));
				wxStaticText* textBody4 = new wxStaticText(panel_body, wxID_ANY,  "[4] Propriete des donnees", wxPoint(20, 110), wxSize(460, 20));
				wxStaticText* textBody5 = new wxStaticText(panel_body, wxID_ANY,  "[5] L’ensemble des donnees", wxPoint(20, 140), wxSize(460, 20));
				wxStaticText* textBody6 = new wxStaticText(panel_body, wxID_ANY,  "[6] Coefficients de la droite de regression", wxPoint(20, 170), wxSize(460, 20));
				wxStaticText* textBody7 = new wxStaticText(panel_body, wxID_ANY,  "[7] Coefficient de determination", wxPoint(20, 200), wxSize(460, 20));
				wxStaticText* textBody8 = new wxStaticText(panel_body, wxID_ANY,  "[8] Prediction", wxPoint(20, 230), wxSize(460, 20));
				wxStaticText* textBody9 = new wxStaticText(panel_body, wxID_ANY, "[9] Quitter le programme", wxPoint(20, 260), wxSize(460, 20));
				wxStaticText* textBody10 = new wxStaticText(panel_footer, wxID_ANY,  "Universite de Montreaal", wxPoint(-1, -1), wxSize(460, 15), wxALIGN_CENTRE);
				textBody10->SetForegroundColour(wxColor(*wxWHITE));
				textBody10->CenterOnParent();


				wxArrayString choices;
				choices.Add("Veuillez choisir une option");
				choices.Add("[1] Description de l’ensemble de donnees");
				choices.Add("[2] L’entete des donnees");
				choices.Add("[3] Queue des donnees");
				choices.Add("[4] Proprietes des donnees");
				choices.Add("[5] L’ensemble des donnees");
				choices.Add("[6] Coefficients de la droite de regression");
				choices.Add("[7] Coefficient de determination");
				choices.Add("[8] Prediction");
				choices.Add("[9] Quitter le programme");

				choice = new wxChoice(panel_body, ID_CHOICES, wxPoint(20, 290), wxSize(460, 30), choices);
				choice->Select(0);
			}
			if(controller.init){
				wxLogMessage("Le fichier "+ fileName +  " a ete deja charge.");
				SetStatusText("Le fichier "+ fileName + " a ete deja charge.");

			}else if(!controller.init){
				controller.load(fileName.ToStdString());
				SetStatusText("Le fichier "+ fileName +  " a ete ouvert avec succes.");
			}
		}else{
		    // Si le fichier n'est pas le diab\xc3\xa8te, la gestion de l'\xc3\xa9cran sera diff\xc3\xa9rente
			if(controller.init){
				controller.init =false;
				panel_body->Destroy();
				panel_footer->Destroy();
				panel_title = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 450));
				panel_title->SetBackgroundColour(wxColor(62, 156, 171));

				wxFont myFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
				panel_title->SetFont(myFont);

				sizer = new wxBoxSizer(wxVERTICAL);
				sizer->Add(panel_title, 1, wxEXPAND| wxALL, 5);
				this->SetSizerAndFit(sizer);
			}
			leTexte1 = new wxTextCtrl(panel_title, wxID_ANY, "", wxDefaultPosition, wxSize(500, 450),  wxTE_MULTILINE|wxTE_RICH2);
			leTexte1->LoadFile(dlg->GetPath());
			wxFont myFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
			panel_title->SetFont(myFont);
			SetStatusText("Mauvais fichier");
			wxLogError("Vous avez ouvert le fichier " + fileName +".\nVeuillez ouvrir le fichier diabetes.tab.txt");
		}
    }

    dlg->Destroy();
}

// Fonction pour savegarder l'info a, b R2
void TexteFrame::OnFichierSauvegarderSous(wxCommandEvent &event){
    if(controller.init){
		wxFileDialog *dlg = new wxFileDialog(this, "Sauvegarder sous", "", "",
			"Fichiers textes(*.txt)|*.txt", wxFD_SAVE, wxDefaultPosition);
		if ( dlg->ShowModal() == wxID_OK ){
			wxString fileName = dlg->GetPath();
			wxString dimensions = "", s;
			s.Printf( "\tAGE      SEX      BMI      BP       S1       S2       S3       S4       S5       S6       Y\n");
			dimensions.append(s);
			s.Printf( "mean:\t%s", controller.mean().getString2());
			dimensions.append(s);
			s.Printf( "std :\t%s", controller.stddeviation().getString2());
			dimensions.append(s);
			s.Printf("R2  :   %.2f\n", controller.r_square_data());
			dimensions.append(s);
			wxTextCtrl *m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, dimensions, wxDefaultPosition, wxDefaultSize, 0 );
			m_textCtrl1->SaveFile(fileName);
			m_textCtrl1->Destroy();
			SetStatusText("Le fichier "+ dlg->GetFilename() +  " a ete enregistre avec succes.");
		}
		dlg->Destroy();
	}else{
		wxLogMessage("Veuillez charger le fichier avant d'enregistrer les donnees");
	}
}

// Fonction pour terminer le programme
void TexteFrame::OnFichierQuitter(wxCommandEvent &event){
    Close(FALSE);
}

// fonction pour apropos
void TexteFrame::OnInfoApropos(wxCommandEvent &event){
	wxString mystring(controller.getInfoApp());
	wxLogInfo(mystring);
}

// Fonctione pour l'aide
void TexteFrame::OnAide(wxCommandEvent &event){
	wxString mystring(controller.getUsage());
	wxLogInfo(mystring);

}

// Fonction pour gerer le choix du client
void TexteFrame::OnChoix(wxCommandEvent &event){

	if(event.GetSelection() == 1){
		wxString lachaine = wxString::FromUTF8("[1] Description de l’ensemble de donnees");

		wxString dimensions {controller.getDescription()};

			TestDialogue
			descriptionDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(800,700),
				dimensions
			);

			descriptionDialog.ShowModal();

	}else if(event.GetSelection() == 2){
		wxString lachaine = wxString::FromUTF8("[2] L’entête des donnees");
		wxString dimensions = "", s;
		s.Printf( "\tAGE    SEX    BMI        BP           S1        S2          S3           S4          S5           S6       Y\n");
		dimensions.append(s);
		for(int i = 0; i < 5; ++i){
			s.Printf( "%d\t%s", i, controller.list_head()[i]->getString());
			dimensions.append(s);
		}
		TestDialogue
			headDataDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(800,230),
				dimensions
			);

			headDataDialog.ShowModal();
	}else if(event.GetSelection() == 3){
		wxString lachaine = wxString::FromUTF8("[3] Queue des donnees");
		wxString dimensions = "", s;
		s.Printf( "\tAGE    SEX    BMI        BP           S1        S2          S3           S4          S5           S6       Y\n");
		dimensions.append(s);
		for(int i = 437; i < 442; ++i){
			s.Printf( "%d\t%s", i, controller.list_all_data()[i]->getString());
			dimensions.append(s);
		}
		TestDialogue
			tailDataDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(800,230),
				dimensions
			);

			tailDataDialog.ShowModal();
	}else if(event.GetSelection() == 4){
		wxString lachaine = wxString::FromUTF8("[4] Proprietes des donnees");
		wxString dimensions = "", s;
		s.Printf( "\tAGE        SEX       BMI         BP          S1           S2             S3           S4          S5          S6          Y\n");
		dimensions.append(s);
		s.Printf( "mean:\t%s", controller.mean().getString2());
		dimensions.append(s);
		s.Printf( "std :\t%s", controller.stddeviation().getString2());
		dimensions.append(s);
		TestDialogue
			stdDeviationDataDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(800,200),
				dimensions
			);

			stdDeviationDataDialog.ShowModal();
	}else if(event.GetSelection() == 5){
		wxString lachaine = wxString::FromUTF8("[5] L’ensemble des donnees");
		wxString dimensions = "", s;
		s.Printf( "\tAGE    SEX    BMI        BP           S1        S2          S3           S4          S5           S6       Y\n");
		dimensions.append(s);
		for(int i = 0; i < 442; ++i){
			s.Printf("%d\t%s", i, controller.list_all_data()[i]->getString());
			dimensions.append(s);
		}
		TestDialogue
			allDataDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(800,800),
				dimensions
			);

			allDataDialog.ShowModal();

	}else if(event.GetSelection() == 6){
		wxString lachaine = wxString::FromUTF8("[6] Coefficients de la droite de r\xc3\xa9gression");
		wxString dimensions = "", s;

		s.Printf("a: %.2f\n", controller.coefficients_droite_data_a());
		dimensions.append(s);
		s.Printf("b: %.2f\n", controller.coefficients_droite_data_b());
		dimensions.append(s);

		TestDialogue
			coefficientsDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(300,300),
				dimensions
			);

		coefficientsDialog.ShowModal();
	}else if(event.GetSelection() == 7){
		wxString lachaine = wxString::FromUTF8("[7] Coefficient de d\xc3\xa9termination");
		wxString dimensions = "", s;

		s.Printf("R2: %.2f\n", controller.r_square_data());
		dimensions.append(s);


		TestDialogue
			squareDialog ( this,
				-1,
				lachaine,
				wxPoint(100,100),
				wxSize(200,200),
				dimensions
			);

		squareDialog.ShowModal();
	}else if(event.GetSelection() == 8){
		wxString lachaine = wxString::FromUTF8("[8] Prediction");
		wxDialog *dlg = new wxDialog(this, -1, lachaine, wxDefaultPosition, wxDefaultSize);
		wxBoxSizer *dialogSizer = new wxBoxSizer(wxVERTICAL);

		massa = new wxTextCtrl(dlg,  wxID_ANY, "", wxPoint(30, -1), wxSize(300, 30));


		// Adding button control
		button3 = new wxButton(dlg, wxID_OK, "OK", wxDefaultPosition, wxSize(200, 30));
		dialogSizer->Add(new wxStaticText(dlg, -1, "Veuillez saisir le numero de la massa corporelle que vous souhaitez predire"),
			0, // make vertically stretchable
			wxEXPAND | wxALL, 10); // make horizontally stretchable
		dialogSizer->Add(massa, 0, wxEXPAND | wxALL, 10);
		dialogSizer->Add(button3,
			0, // make vertically unstretchable
			wxALIGN_CENTER | wxALL, 15); // centre horizontally and set border width to 10

		dlg->SetSizerAndFit(dialogSizer); // Use dialog sizer for layout

		 if (dlg->ShowModal() == wxID_OK){
				dlg->Destroy();
				double n = std::stod(massa->GetValue().ToStdString());
			
				wxString text (this->controller.prediction_data_final(n));

				wxMessageDialog *dlg2 = new wxMessageDialog(this, text,
					"Prediction", wxOK | wxCENTRE | wxICON_INFORMATION, wxDefaultPosition);
				dlg2->ShowModal();
		 }

	}else if(event.GetSelection() == 9){
		 Close(TRUE);
	}
}

// Fenetre avec les informations que le client a choisies
TestDialogue::TestDialogue
    ( wxWindow *parent, wxWindowID id,
        const wxString &title,
        const wxPoint &position, const wxSize& size,
        const wxString &dimensions,
		long style

    ) :
        wxDialog( parent, id, title, position, size, style){



    wxPoint p;
    wxSize  sz;

    sz.SetWidth(size.GetWidth() - 20);    //set size of text control
    sz.SetHeight(size.GetHeight() - 90);

    p.x = 6; p.y = 2; 					//set x y position for text control

  dialogTexte = new wxTextCtrl
  		( this,
  		  -1,
  		  dimensions,
  		  p,
  		  sz,
  		  wxTE_MULTILINE | wxTE_READONLY
  		);
  dialogTexte->Center();
  p.y += sz.GetHeight() + 30; //set y position for the OK button
  p.x += sz.GetWidth() - 80; //set x position for the OK button
  wxButton * b = new wxButton( this, wxID_OK, "OK", p, wxDefaultSize);



}

BEGIN_EVENT_TABLE(TestDialogue, wxDialog)
    EVT_BUTTON( wxID_OK, TestDialogue::OnOk )
END_EVENT_TABLE()

void TestDialogue::OnOk(wxCommandEvent &event)
{
    event.Skip();
}

wxString TestDialogue::GetText()
{
	return dialogTexte->GetValue();
}



