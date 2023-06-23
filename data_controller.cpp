#include "data_controller.hpp"
#include <fmt/format.h>

// Cela D\xc3\xa9truit le vecteur pointeur des type data
data_controller::~data_controller(){
	std::for_each(all_data.begin(), all_data.end(), [&](data *i){ delete i;});
}

// Cette m\xc3\xa9thode charge le fichier et effectue les op\xc3\xa9rations de moyenne, deviation standard et de pr\xc3\xa9dictions.
void data_controller::load(std::string file_name){

	std::ifstream myFile;
	std::string line;
	double sexe, bmi, bp, s1, s2, s3, s4, s5, s6, y;
	std::string sta, sts, stbmi, stbp, st1, st2, st3, st4, st5, st6, sty;
	myFile.open(file_name);

	if (!myFile.is_open()){
        std::cerr << "Erreur lors de l'ouverture du fichier. \nIl faudrait le nom du fichier en ligne de commandes" << std::endl;
        exit(1);
    }

    getline(myFile >> std::ws, line, '\t');
	if (myFile >> sts >>stbmi>> stbp >>st1>> st2>> st3>> st4>> st5>> st6>> sty){
			header = "    \t" +line + "      " + sts + "      " + stbmi + "      " + stbp + "       " + st1 + "       " + st2 + "       " + st3 + "       " + st4 + "       " + st5 + "       " + st6 + "       " + sty + "\n";
     }


    while (getline(myFile >> std::ws, line, '\t')){

        if (myFile >> sexe >>bmi>> bp >>s1>> s2>> s3>> s4>> s5>> s6>> y){
			all_data.push_back(new data(std::stod(line), sexe, bmi, bp, s1, s2, s3, s4, s5, s6, y));
        }

	}

	std::for_each(all_data.begin(), all_data.end(), [&](data *i){ this->meanRes += *i;}); // Addition avec la surcharge de la classe data
	this->meanRes = this->meanRes / all_data.size();

	data sum;
	std::for_each(all_data.begin(), all_data.end(), [&](data *i){
		sum = *i;
		this->stdRes += (sum - this->meanRes) ^ 2 ; // Operations avec la surcharge de la classe data
	});

	this->stdRes = this->stdRes(this->stdRes, all_data.size());

	double sum_XY = 0.0, sum_X = 0.0;
	double squareSum_X = 0.0;
    double x, y2;
	double x_mean = this->meanRes.get_bmi();
	double y_mean = this->meanRes.get_y();

	std::for_each(all_data.begin(), all_data.end(), [&](data *i){
		x = i->get_bmi();
		y2 = i->get_y();
		sum_X += x;
		sum_XY += x * y2;
		squareSum_X += x * x;
	});

	this->a = (sum_XY - y_mean * sum_X) / (squareSum_X - x_mean * sum_X); //Formule a
	this->b = (y_mean * squareSum_X - x_mean * sum_XY) / (squareSum_X - x_mean * sum_X); // Formule b
	this->init = true;
}

// Retour de toutes les informations du vecteur
std::vector<data*> data_controller::list_all_data(){
	return all_data;
}

// Retour de la moyenne
data data_controller::mean(){
	return this->meanRes;
}

// Retour de la deviation standard
data data_controller::stddeviation(){
	return this->stdRes;

}

// Retour du titre header
std::string data_controller::getHeader(){
	return header;
}

// Retour de l'usage
std::string data_controller::getUsage(){
	return "\nUsage: \n\nPour executer le programme, vous devez ouvrir le fichier diabetes.tab.txt."
						"\n\nOptions:\n\n"
						 "1 - Description de l’ensemble de donnees:\n"
						 "--> Les details de chacun des attributs et leurs valeurs \n\n"
						 "2 - L’entete des donnees:\n"
						 "--> Les cinq premieres lignes du fichier avec chacun de ses attributs et valeurs \n\n"
						 "3 - Queue des donnees:\n"
						 "--> Les cinq dernieres lignes du fichier avec chacun de ses attributs et valeurs\n\n"
						 "4 - Proprietes des donnees:\n"
						 "--> Le calcul de la moyenne et la deviation standard de chaque caractaristique\n\n"
						 "5 - L’ensemble des donnees:\n"
						 "--> Tous les 442 attributs avec leurs valeurs\n\n"
						 "6 - Les coefficients de la droite de regression:\n"
						 "--> Le calcule des parametres « a » et « b » de la droite de regression lineaire entre « bmi » et « Y »\n\n"
						 "7 - Les coefficient de determination:\n"
						 "--> Le calcule de coefficient de determination 𝑅2.\n\n"
						 "8 - La prediction:\n"
						 "--> Une prediction calculee a partir d’une valeur fournie en entree\n\n"
						 "9 - Quitter le programme: --> La fin du programme\n\n";
}


// Retour de l'aide
std::string data_controller::getInfoApp(){
	return "\nNom du concepteur: Jorge Olivera\n"
			 "\nDate: \tDecembre 12, 2022\n"
			 "\nVersion: \t1.0\n";
}
// // Retour de la description
std::string data_controller::getDescription(){
	return "Ensemble de donnees sur le Diabete\n"
		    "------------------------------------------------------------------------------------------------------------------------------------------------------\n\n"
					   	"Dix caracteristique, âge, sexe, indice de masse corporelle, pression arterielle\n"
						"moyenne, et six mesures de serum sanguin ont ete obtenues pour chacun de n = 442\n"
						"patients diabetiques, ainsi que la cible, une mesure quantitative de la progression\n"
						"de la maladie une annee par rapport a une mesure refrentielle.\n\n"
						"**Caracteristiques de l'ensemble de donnees :**\n\n"
						"\t :Nombre d'instances : 442\n\n"
						"\t :Nombre d'attributs : les 10 premieres colonnes sont des valeurs predictives numeriques\n\n"
						"\t :Cible : la colonne 11 est une mesure quantitative de la progression de la maladie une annee par rapport a une mesure refrentielle\n\n"
						"\t :Informations sur les attributs :\n\n"
						"\t\t - âge : l'âge du malade en annees\n\n"
						"\t\t - Sexe : le sexe du malade, 1 pour les hommes, 2 pour les femmes.\n\n"
						"\t\t - bmi : l'indice de la masse corporelle (poids en kg / (taille en m)^2)\n\n"
						"\t\t - bp : pression arterielle moyenne\n\n"
						"\t\t - s1 : tc, cholesterol total dans le serum\n\n"
						"\t\t - s2 : ldl, lipoproteines a faible densite\n\n"
						"\t\t - s3 : hdl, lipoproteines a haute densite\n\n"
						"\t\t - s4 : tch, cholesterol total dans HDL\n\n"
						"\t\t - s5 : ltg, le log du niveau de triglycerides dans le serum\n\n"
						"\t\t - s6 : glu, le taux de sucre\n";
}

// Retour d'un vecteur avec le 5 premiers elements
std::vector<data*> data_controller::list_head(){
	for(int i = 0; i < 5; ++i){
		head.push_back(all_data[i]);
	}
	return head;
}

// Retour de coefficient droite de la formule a
double data_controller::coefficients_droite_data_a(){
	return this->a;
}

// Retour de ceofficient droite de la formule b
double data_controller::coefficients_droite_data_b(){
	return this->b;
}

// Retour de R carre
double data_controller::r_square_data(){
	double y, squareSum_Y_numerator = 0.0, squareSum_Y_denominator = 0.0;
	double y_mean = this->meanRes.get_y();
	double y_prediction = 0.0;

	for (unsigned i = 0; i < all_data.size(); ++i){
		y = all_data[i]->get_y();
		y_prediction = prediction_data(i);
		squareSum_Y_numerator += pow(y - y_prediction, 2);
		squareSum_Y_denominator +=  pow(y - y_mean, 2);
	}

	this->r = 1 - (squareSum_Y_numerator / squareSum_Y_denominator) ;

	return this->r;
}

// Retour de la prediction interne
double data_controller::prediction_data(int i){
	return this->a * all_data[i]->get_bmi() + this->b;
}

// Retour de la prediction externe
std::string data_controller::prediction_data_final(double i){
	 return fmt::format("{:.2f}", this->a * i + this->b);
}
