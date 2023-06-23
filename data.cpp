#ifndef DATA_HPP
#define DATA_HPP
#include <iostream>
#include <cmath>
#include <fmt/format.h>
#include <string>  

class data {
	
	public :
		
		data(double _age = 0.0, double _sexe = 0.0, double _bmi = 0.0, double _bp = 0.0, double _s1 = 0.0, 
		double _s2 = 0.0, double _s3 = 0.0, double _s4 = 0.0, double _s5 = 0.0, double _s6 = 0.0, double _y = 0.0) 
		: age(_age), sexe(_sexe), bmi(_bmi), bp(_bp), s1(_s1), s2(_s2),
		s3(_s3), s4(_s4), s5(_s5), s6(_s6), y(_y) {}

        data(const data& copy): age(copy.age), sexe(copy.sexe), bmi(copy.bmi), bp(copy.bp), s1(copy.s1), s2(copy.s2),
									s3(copy.s3), s4(copy.s4), s5(copy.s5), s6(copy.s6), y(copy.y) {}

		// Surcharge de la soustraction	
		data& operator-(data const &obj){
			
			age -= obj.age;
			sexe -= obj.sexe;
			bmi -= obj.bmi;
			bp -= obj.bp;
			s1 -= obj.s1;
			s2 -= obj.s2;
			s3 -= obj.s3;
			s4 -= obj.s4;
			s5 -= obj.s5;
			s6 -= obj.s6;
			y -= obj.y;
			return *this;
		}

		// Surcharge de la'addition
		data& operator+=(data const &obj){
			
			age += obj.age;
			sexe += obj.sexe;
			bmi += obj.bmi;
			bp += obj.bp;
			s1 += obj.s1;
			s2 += obj.s2;
			s3 += obj.s3;
			s4 += obj.s4;
			s5 += obj.s5;
			s6 += obj.s6;
			y += obj.y;
			return *this;
		}

		// Surcharge de la division
		data& operator/(double i){
			
			age /= i;
			sexe /= i;
			bmi /= i;
			bp /= i;
			s1 /= i;
			s2 /= i;
			s3 /= i;
			s4 /= i;
			s5 /= i;
			s6 /= i;
			y /= i;
			return *this;
		}

		// Surcharge de la puissance
		data& operator^(int power){
			
			age = pow(age, power);
			sexe = pow(sexe, power);
			bmi =  pow(bmi, power);
			bp = pow(bp, power);
			s1 = pow(s1, power);
			s2 = pow(s2, power);
			s3 = pow(s3, power);
			s4 = pow(s4, power);
			s5 = pow(s5, power);
			s6 = pow(s6, power);
			y = pow(y, power);
			return *this;
		}

        // Surcharge du carre
	    data& operator()(data const &obj, int reg){
			
			age =  sqrt(obj.age / reg);
			sexe =  sqrt(obj.sexe / reg);
			bmi =  sqrt(obj.bmi / reg);
			bp = sqrt(obj.bp / reg);
			s1 = sqrt(obj.s1 / reg);
			s2 =  sqrt(obj.s2 / reg);
			s3 =  sqrt(obj.s3 / reg);
			s4 =  sqrt(obj.s4 / reg);
			s5 =  sqrt(obj.s5 / reg);
			s6 =  sqrt(obj.s6 / reg);
			y = sqrt(obj.y / reg);
			return *this;
		}

		// Retour  du BMI
		double get_bmi(){
			return bmi;
		}

		// Retour du Y
		double get_y(){
			return y;
		}
		//Affichage des donnees
		std::string getString(){
			return fmt::format("{:<8} {:<8} {:<8.4f} {:<8.4f} {:<8} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8} {:<8}\n", this->age, this->sexe, this->bmi, this->bp, this->s1,
				this->s2, this->s3, this->s4, this->s5, this->s6, this->y);
		}
		
		//Affichage des donnees pour la deviation
		std::string getString2(){
			return fmt::format("{:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f}\n", this->age, this->sexe, this->bmi, this->bp, this->s1,
				this->s2, this->s3, this->s4, this->s5, this->s6, this->y);
		}
		
		// Surcharge de l'operateur de sortie
		friend std::ostream& operator<<(std::ostream& out, const data& this_data){
			std::cout << fmt::format("{:<8} {:<8} {:<8.4f} {:<8.4f} {:<8} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8} {:<8}\n", this_data.age, this_data.sexe, this_data.bmi, this_data.bp, this_data.s1,
				this_data.s2, this_data.s3, this_data.s4, this_data.s5, this_data.s6, this_data.y);
			return out;
		}

		// Surcharge de l'operateur d'entree
		friend std::ostream& operator>>(std::ostream& out, const data& this_data){
			
			std::cout << fmt::format("{:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f} {:<8.4f}\n", this_data.age, this_data.sexe, this_data.bmi, this_data.bp, this_data.s1,
				this_data.s2, this_data.s3, this_data.s4, this_data.s5, this_data.s6, this_data.y);
			return out;
		}
	
	private :
		double age, sexe, bmi, bp, s1, s2, s3, s4, s5, s6, y;
};
#endif