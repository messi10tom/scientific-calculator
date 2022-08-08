#define _USE_MATH_DEFINES

#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
int j = 0;
struct funcy
{
	std::string Mprob;
	int function;
	double value;
	bool isfunc;
};
std::string vecTstr(std::vector<char>& str) {
	std::string i(str.begin(), str.end());
	return i;
}

bool containOperator(std::string Mprob, char SOP = 'a') {
	for (int i = 0; i < Mprob.length(); i++) {
		if (SOP == 'a') {
			if (Mprob[i] == '+' || Mprob[i] == '*' ||
				Mprob[i] == '/' || Mprob[i] == '^') {
				return true;
			}
		}
		else {
			if (Mprob[i] == SOP) {
				return true;
			}
		}
	}
	return false;
}

funcy isFunc(std::string function) {
	//must contain any keyword from [funcs]
	//should have any real number in it
	//dont contain any other characters except '(', ')' and ' ' currently
	std::string funcs[15] = { "sin", "cos", "tan", "sec", "cot", 
				 "log", "ln", "cosec", "antilog", "ln-1", 
				 "sin-1", "cos-1", "tan-1", "fact", "nullfn" };
	int func = 14, pos;
	std::string expfunc;
	funcy FUNCY;
	double value;
	for (int i = 0; i < 13; i++) {
		if (function.find(funcs[i]) != std::string::npos) {
			func = i;
		}
	}
	if (func != 14) {
		if ((pos = function.find('(')) != std::string::npos) {
			value = stoi(function.substr(pos + 1, function.find(')') - pos - 1));
			expfunc = funcs[func] + "(" + std::to_string(value) + ")";
		}
		else {
			value = std::stod(function.substr(funcs[func].length(), function.length()));
			expfunc = funcs[func] + std::to_string(value);
		}
	}

	//spl fns
	if ((pos = function.find('!')) != std::string::npos) {
		value = stoi(function.substr(0, function.length() - 1));
		expfunc = std::to_string(value) + "!";
	}

	if (func != 14) {
		FUNCY.value = value;
		FUNCY.function = func;
		FUNCY.Mprob = function;
		pos = function.find(expfunc);
		if (function.length() == expfunc.length()) { FUNCY.isfunc = true; }
		return FUNCY;
	}
	FUNCY.isfunc = false;
	return FUNCY;
}

unsigned int factorial(unsigned int n)
{
	return ((n == 1 || n == 0) ? 1 : n * factorial(n - 1));
}

double functions(funcy f) {


	switch(f.function) 
	{
		case 0 : return sin((f.value * M_PI) / 180);
		case 1 : return cos((f.value * M_PI) / 180);
		case 2 : return tan((f.value * M_PI) / 180);
		case 3 : return 1 / cos((f.value * M_PI) / 180);
		case 4 : return 1 / tan((f.value * M_PI) / 180);
		case 5 : return log10(f.value);
		case 6 : return log(f.value);
		case 7 : return 1 / sin((f.value * M_PI) / 180);
		case 8 : return pow(10, f.value);
		case 9 : return exp(f.value);
		case 10: return (asin(f.value) * 180) / M_PI;
		case 11: return (acos(f.value) * 180) / M_PI;
		case 12: return (atan(f.value) * 180) / M_PI;
		case 13: return factorial(f.value);
		default: return 0000000; 

	}
}

double getNum(std::string Mprob, std::string& Mptr) {
	double n;
	for (int i = 0; i < Mprob.length(); i++) {
		if (Mprob[i] == '+' || Mprob[i] == '*' ||
			Mprob[i] == '/' || Mprob[i] == '^') {
			//sin(9)-4+56
			funcy func = isFunc(Mprob.substr(0, i));
			if (func.isfunc) {
				n = functions(func);
			}
			else {
				n = stoi(Mprob.substr(0, i));
			}
			Mptr = Mprob.substr(i + 1);
			//std::cout << Mprob << '\n';
			return n;
		}

	}
}


std::vector<double> getNums(std::string Mprob) {
	std::string Mref;
	std::vector<double> nums;
	double num;
	int i = 0;

	while (containOperator(Mprob)) {
		num = getNum(Mprob, Mref);
		//std::cout << Mprob << '\n';
		nums.push_back(num);
		Mprob = Mref;
		i++;

	}
	//std::cout << Mprob << "M" << '\n';
	nums.push_back(stoi(Mprob));
	//for (double nu : nums) { std::cout << nu<< "N" <<'\n'; }
	return nums;

}

void arithmetics(std::vector<double>& Nvec, std::vector<char>& OPvec) {
	int i = 0;
	std::vector<double>::iterator it1;
	std::vector<char>::iterator it2;

	while (containOperator(vecTstr(OPvec), '^')) {
		if (OPvec[i] == '^') {
			Nvec[i] = pow(Nvec[i], Nvec[i + 1]);

			it1 = Nvec.begin() + i + 1;
			Nvec.erase(it1);

			it2 = OPvec.begin() + i;
			OPvec.erase(it2);

			i = -1;
		}

		i++;
	}

	i = 0;

	while (containOperator(vecTstr(OPvec), '*')) {
		if (OPvec[i] == '*') {
			Nvec[i] = Nvec[i] * Nvec[i + 1];

			it1 = Nvec.begin() + i + 1;
			Nvec.erase(it1);

			it2 = OPvec.begin() + i;
			OPvec.erase(it2);

			i = -1;
		}

		i++;
	}

	i = 0;

	while (containOperator(vecTstr(OPvec), '/')) {
		if (OPvec[i] == '/') {
			Nvec[i] = Nvec[i] / Nvec[i + 1];

			it1 = Nvec.begin() + i + 1;
			Nvec.erase(it1);

			it2 = OPvec.begin() + i;
			OPvec.erase(it2);

			i = -1;
		}

		i++;
	}

	i = 0;

	while (containOperator(vecTstr(OPvec), '+')) {

		if (OPvec[i] == '+') {
			Nvec[i] = Nvec[i] + Nvec[i + 1];

			it1 = Nvec.begin() + i + 1;
			Nvec.erase(it1);

			it2 = OPvec.begin() + i;
			OPvec.erase(it2);

			i = -1;
			
		}
		
		i++;
	}

}

std::vector<char> getOPS(std::string Mprob) {
	std::vector<char> x;
	for (int i = 0; i < Mprob.length(); i++) {
		if (Mprob[i] == '+' || Mprob[i] == '*' || 
			Mprob[i] == '/' || Mprob[i] == '^') {
			x.push_back(Mprob[i]);
		}
	}

	return x;
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'

	}
	return str;
}


std::string rearranger(std::string Mprob) {
	// removing all whitespaces
	std::string::iterator end_pos = std::remove(Mprob.begin(), Mprob.end(), ' ');
	Mprob.erase(end_pos, Mprob.end());

	// if its just a function that contain no operations
	funcy func = isFunc(Mprob);
	if (func.isfunc) {
		return std::to_string(functions(func));
	}
	//placing + infront of - if infront of - is not an operator
	size_t start_pos = 0;
	std::vector<std::string> expfuncs = { "sin-1", "cos-1", "tan-1" };
	while ((start_pos = Mprob.find('-', start_pos)) != std::string::npos) {
		//sin-1 0.5 * |-5|
		if (start_pos != 0) {
			if (Mprob[start_pos - 1] != '+' && Mprob[start_pos - 1] != '*' &&
				Mprob[start_pos - 1] != '/' && Mprob[start_pos - 1] != '^') {
				//std::cout << Mprob.substr(start_pos - 2, 4) << '\n';

				if (start_pos >= 3) {
					if ((std::find(expfuncs.begin(), expfuncs.end(), Mprob.substr(start_pos - 3, 5)) == expfuncs.end())) {
						Mprob.replace(start_pos, 1, "+-");
					}
				}
				else {
					Mprob.replace(start_pos, 1, "+-");
				}

			}
		}

		start_pos += 2;

	}

	start_pos = 0;
	while ((start_pos = Mprob.find("|", start_pos)) != std::string::npos) {
		size_t end_pos;
		end_pos = Mprob.find("|", start_pos + 1);
		if (end_pos - start_pos > 2) {
			std::string x = rearranger(Mprob.substr(start_pos + 2, end_pos - start_pos - 2));
			std::vector<double> numarray = getNums(x);
			std::vector<char> oparray = getOPS(x);
			Mprob = Mprob.substr(0, start_pos) + std::to_string(abs(numarray[0])) + Mprob.substr(end_pos + 1, Mprob.length());
		}
		else {
			Mprob.erase(Mprob.begin() + end_pos);
			Mprob.erase(Mprob.begin() + start_pos);
		}

	}

	while ((start_pos = Mprob.find("ln+-1")) != std::string::npos) {
		Mprob.erase(Mprob.begin() + start_pos + 3);
	}
	if (Mprob[0] == '+') { Mprob = Mprob.substr(1, Mprob.length()); }

	// finding first ) and then closest ( in the left side.

	size_t j;
	start_pos = 0;
	while ((start_pos = Mprob.find(')')) != std::string::npos) {
		auto substr = Mprob.substr(0, start_pos);
		std::reverse(substr.begin(), substr.end());
		j = substr.find('(');
		auto numarray = getNums(Mprob.substr(start_pos - j, j));
		auto oparray = getOPS(Mprob.substr(start_pos - j, j));
		arithmetics(numarray, oparray);
		Mprob = Mprob.substr(0, start_pos - j - 1) + std::to_string(numarray[0]) + Mprob.substr(start_pos + 1, Mprob.length());
	}


	return Mprob;
}

int main()
{
	while(true)
	{
		std::cout << "ENTER : ";
		std::string problem;
		std::getline(std::cin, problem);
		
		problem = rearranger(problem);
		if (paraOPS) {
			std::vector<double> numarray = getNums(problem);
			std::vector<char> oparray = getOPS(problem);

			arithmetics(numarray, oparray);
			for (double i : numarray) { std::cout << "        " << i << std::endl; }
		}

		if (problem == "Exit") 
		{
			return 0;
		}
	}

	// std::string problem;
	// problem = "sin-1 0.5 * |-5|";
	// problem = rearranger(problem);
	// bool paraOPS = containOperator(problem);

	// if (paraOPS) {
	// 	std::vector<double> numarray = getNums(problem);
	// 	std::vector<char> oparray = getOPS(problem);

	// 	arithmetics(numarray, oparray);
	// 	for (double i : numarray) { std::cout << "        " << i; }
	// }

}


