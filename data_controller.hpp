#ifndef DATA_CONTROLLER_HPP
#define DATA_CONTROLLER_HPP

#include "data.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>  // std::for_each
#include <vector>
#include <cmath>

class data_controller {

	public :
		~data_controller();
		void load(std::string file_name);
		std::vector<data*> list_all_data();
		data mean();
		data stddeviation();
		std::string getHeader();
		std::string getUsage();
		std::string getInfoApp();
		std::string getDescription();
		std::vector<data*> list_head();
		double coefficients_droite_data_a();
		double coefficients_droite_data_b();
		double r_square_data();
		double prediction_data(int);
		std::string prediction_data_final(double);
		bool init = false;

	private :
		std::vector<data*> all_data ;
		data meanRes;
		data stdRes;
		std::string header;
		std::vector<data*> head;
		double a;
		double b;
		double r;

};

#endif
