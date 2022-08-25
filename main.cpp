#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

class Metrics {
	public:
		std::string mathsproblem;
		std::string function = "NULLFn";
		std::string value;
		std::vector<double> nVEC;
	private:

		Metrics(std::string& mp) {
			mathsproblem = mp;
		}
		//                      0      1	  2	     3	    4	   5	  6
		std::string funcs[15] = { "sin", "cos", "tan", "sec", "cot", "log", "ln",
			//					   7		 8		   9	  10	   11		12
								"cosec", "antilog", "ln-1", "sin-1", "cos-1", "tan-1",
			//					13      14
								"!", "NULLFn" };
		int start_pos;
		int NULLFn = 14;

		bool containOperator(const char& SOP = 'a') {
			if (SOP == 'a') {
				for (char i : {'+', '-', '*', '/', '^'}) {
					return mathsproblem.find(i) != std::string::npos;
				}
			}
			else {
				return mathsproblem.find(SOP) != std::string::npos;
			}
		}

		void functionFinder() {
			int func = 14;
			for (int i = 0; i < NULLFn; i++) {
				if (mathsproblem.find(funcs[i]) != std::string::npos) func = i;

			}
			function = funcs[func];
		}

		void functionValueSplitter() {
			int pos;
			if (NULLFn != 14) {
				if ((pos = mathsproblem.find('(')) != std::string::npos) {
					value = mathsproblem.substr(pos + 1, mathsproblem.find(')') - pos - 1);
				}

				else {
					value = mathsproblem.substr(function.length(), mathsproblem.length());
				}
			}

			if ((pos = function.find('!')) != std::string::npos) {
				value = function.substr(0, function.length() - 1);
			}
		}

		bool isFunction() {
			// A function needs its name or symbol in it
			// A function must have a value
			// Eg. sin40, cos(90), log 2
			if (!(value.find_first_not_of("0123456789.") == std::string::npos) &&
				function == "NULLFn") {
				return false;
			}
			return true;
		}

		double functions(const int function, double value, ) {


			switch (function)
			{
			case 0: return sin((value * M_PI) / 180);
			case 1: return cos((value * M_PI) / 180);
			case 2: return tan((value * M_PI) / 180);
			case 3: return 1 / cos((value * M_PI) / 180);
			case 4: return 1 / tan((value * M_PI) / 180);
			case 5: return log10(value);
			case 6: return log(value);
			case 7: return 1 / sin((value * M_PI) / 180);
			case 8: return pow(10, value);
			case 9: return exp(value);
			case 10: return (asin(value) * 180) / M_PI;
			case 11: return (acos(value) * 180) / M_PI;
			case 12: return (atan(value) * 180) / M_PI;
			case 13: return factorial(value);

			}
		}

		void numSplitter() {
			double n;
			Metrics MathProb = mathsproblem;
			while (MathProb.containOperator()) {
				while ((start_pos = MathProb.mathsproblem.find('+', start_pos)) != std::string::npos ||
					(start_pos = MathProb.mathsproblem.find('*', start_pos)) != std::string::npos ||
					(start_pos = MathProb.mathsproblem.find('/', start_pos)) != std::string::npos ||
					(start_pos = MathProb.mathsproblem.find('^', start_pos)) != std::string::npos || ) {
					Metrics MATHSPROBLEM = MathProb.mathsproblem.substr(0, start_pos);
					if (MATHSPROBLEM.isFunction()) {
						MATHSPROBLEM.functionFinder();
						MATHSPROBLEM.functionValueSplitter();
						if (std::trunc(std::stod(MATHSPROBLEM.value)) == std::stod(MATHSPROBLEM.value))
							n = MATHSPROBLEM.functions(std::find(funcs, funcs + 15, function) - funcs, stoi(MATHSPROBLEM.value));
						else
							n = MATHSPROBLEM.functions(std::find(funcs, funcs + 15, function) - funcs, stod(MATHSPROBLEM.value));
					}
					else {
						n = stod(MathProb.mathsproblem.substr(0, start_pos));
					}
					mathsproblem = MathProb.mathsproblem.substr(start_pos + 1);

				}
				Metrics::nVEC.push_back(n);

			}

			if (MathProb.isFunction()) {
				MathProb.functionFinder();
				MathProb.functionValueSplitter();
				if (std::trunc(std::stod(MathProb.value)) == std::stod(MathProb.value))
					n = MathProb.functions(std::find(funcs, funcs + 15, function) - funcs, stoi(MathProb.value));
				else
					n = MathProb.functions(std::find(funcs, funcs + 15, function) - funcs, stod(MathProb.value));
				Metrics::nVEC.push_back(n);
			}
			else {
				Metrics::nVEC.push_back(stod(MathProb.mathsproblem))
			}

		}

		void reduction() {
			// removing all whitespaces
			std::string::iterator end_pos;
			end_pos = std::remove(mathsproblem.begin(), mathsproblem.end(), ' ');
			mathsproblem.erase(end_pos, mathsproblem.end());
		}

		void parenModCalc() {
			size_t end_pos, j;
			while ((start_pos = mathsproblem.find("|", start_pos)) != std::string::npos &&
				   (start_pos = mathsproblem.find(')')) != std::string::npos) {
				if (mathsproblem[start_pos] == '|') {
					end_pos = mathsproblem.find("|", start_pos + 1);
					if (end_pos - start_pos > 2) {
						Metrics::rearranger(mathsproblem.substr(start_pos + 2, end_pos - start_pos - 2));
						std::vector<double> numarray = getNums(mathsproblem);
						std::vector<char> oparray = getOPS(mathsproblem);
						mathsproblem = mathsproblem.substr(0, start_pos) +
							std::to_string(abs(numarray[0])) +
							mathsproblem.substr(end_pos + 1, mathsproblem.length());
					}
					else {
						mathsproblem.erase(mathsproblem.begin() + end_pos);
						mathsproblem.erase(mathsproblem.begin() + start_pos);
					}
				}
				else {
					auto substr = mathsproblem.substr(0, start_pos);
					std::reverse(substr.begin(), substr.end());
					j = substr.find('(');
					auto numarray = getNums(mathsproblem.substr(start_pos - j, j));
					auto oparray = getOPS(mathsproblem.substr(start_pos - j, j));
					arithmetics(numarray, oparray);
					mathsproblem = mathsproblem.substr(0, start_pos - j - 1) + 
								   std::to_string(numarray[0]) + 
								   mathsproblem.substr(start_pos + 1, mathsproblem.length());
				}

			}
		}

		void MIN2MINX() {
			//changing - into +-1*
			std::vector<std::string> expfuncs = { "sin-1", "cos-1", "tan-1" };
			while ((start_pos = mathsproblem.find('-', start_pos)) != std::string::npos) {
				// not letting it to replace - if - is on the first number's sign
				// Eg. -1 + 1
				if (start_pos != 0) {
					// avoiding cases where - is the sign of number
					// Eg. 5 * -1
					if (mathsproblem[start_pos - 1] != '+' && mathsproblem[start_pos - 1] != '*' &&
						mathsproblem[start_pos - 1] != '/' && mathsproblem[start_pos - 1] != '^') {
						
						// most of the functions which has - in it[indicates inverse(sin-1)] have
						// lenght greater than 3.
						if (start_pos >= 3) {
							if ((std::find(expfuncs.begin(), expfuncs.end(), 
								mathsproblem.substr(start_pos - 3, 5)) == expfuncs.end())) {
								mathsproblem.replace(start_pos, 1, "+-1*");
							}
						}
						// when - is located at an index less than 3, mostly normal numbers not fns
						else {
							mathsproblem.replace(start_pos, 1, "+-1*");
						}

					}
				}

				start_pos += 2;

			}

			while ((start_pos = mathsproblem.find("ln+-1")) != std::string::npos) {
				mathsproblem.erase(mathsproblem.begin() + start_pos + 3);
			}
		}

		void rearranger() {

		}

};

unsigned int factorial(unsigned int n)
{
	return ((n == 1 || n == 0) ? 1 : n * factorial(n - 1));
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

int main() {
	while (true)
	{
		std::cout << "ENTER : ";
		std::string problem;
		std::getline(std::cin, problem);

		problem = rearranger(problem);
		if (!is_number(problem)) {
			std::vector<double> numarray = getNums(problem);
			std::vector<char> oparray = getOPS(problem);

			arithmetics(numarray, oparray);
			for (double i : numarray) { std::cout << "        " << i << std::endl; }
		}
		else if (problem == "Exit")
		{
			return 0;
		}
		else std::cout << "        " << problem << std::endl;
	}
}
