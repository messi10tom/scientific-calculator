#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

class Metrics {
public:
	std::string mathsproblem;
	std::string value;
	std::vector<double> nVEC;
	std::vector<char> opsVEC;

	Metrics() {

	}

	Metrics(std::string mp) :
		mathsproblem(mp) {}

	bool operator== (const char* mp) {
		return this->mathsproblem.c_str() == mp;
	}

	Metrics operator= (Metrics mp) {
		return mp;
	}

private:

	//                      0      1	  2	     3	    4	   5	  6
	std::string funcs[15] = { "sin", "cos", "tan", "sec", "cot", "log", "ln",
		//					   7		 8		   9	  10	   11		12
							"cosec", "antilog", "ln-1", "sin-1", "cos-1", "tan-1",
		//					13      14
							"!", "NULLFn" };
	std::string function = "NULLFn";
	int start_pos = 0;
	int NULLFn = 14;

	unsigned int factorial(unsigned int n)
	{
		return ((n == 1 || n == 0) ? 1 : n * factorial(n - 1));
	}

public:

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

	int functionFinder() {
		int func = 14;
		for (int i = 0; i < NULLFn; i++) {
			if (mathsproblem.find(funcs[i]) != std::string::npos) func = i;

		}
		function = funcs[func];

		return func;
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
		if (!(value.find_first_not_of("0123456789.-") == std::string::npos) ||
			function == "NULLFn" || value == "") {
			return false;
		}
		return true;
	}

	double functions(const int function, double value) {


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
		start_pos = 0;
		Metrics MathProb = mathsproblem;
		while (MathProb.containOperator()) {

			for (; start_pos < MathProb.mathsproblem.length(); start_pos++) {
				if (MathProb.mathsproblem[start_pos] == '+' ||
					MathProb.mathsproblem[start_pos] == '*' ||
					MathProb.mathsproblem[start_pos] == '/' ||
					MathProb.mathsproblem[start_pos] == '^') {
					Metrics MATHSPROBLEM = MathProb.mathsproblem.substr(0, start_pos);
					if (MATHSPROBLEM.isFunction()) {
						MATHSPROBLEM.functionFinder();
						MATHSPROBLEM.functionValueSplitter();
						n = MATHSPROBLEM.functions(std::find(funcs, funcs + 15, function) - funcs, stod(MATHSPROBLEM.value));
					}
					else {
						n = stod(MathProb.mathsproblem.substr(0, start_pos));
					}
					mathsproblem = MathProb.mathsproblem.substr(start_pos + 1);

				}
			}

			Metrics::nVEC.push_back(n);

		}

		if (MathProb.isFunction()) {
			MathProb.functionFinder();
			MathProb.functionValueSplitter();
			n = MathProb.functions(std::find(funcs, funcs + 15, function) - funcs, stod(MathProb.value));
			Metrics::nVEC.push_back(n);
		}
		else {
			Metrics::nVEC.push_back(stod(MathProb.mathsproblem));
		}

	}

	void OPSsplitter() {
		while ((start_pos = Metrics::mathsproblem.find('+', start_pos)) != std::string::npos ||
			(start_pos = Metrics::mathsproblem.find('*', start_pos)) != std::string::npos ||
			(start_pos = Metrics::mathsproblem.find('/', start_pos)) != std::string::npos ||
			(start_pos = Metrics::mathsproblem.find('^', start_pos)) != std::string::npos) {
			Metrics::opsVEC.push_back(Metrics::mathsproblem[start_pos]);
		}

	}

	bool is_number()
	{
		char* end = nullptr;
		double val = strtod(Metrics::mathsproblem.c_str(), &end);
		return end != Metrics::mathsproblem.c_str() && *end == '\0' && val != HUGE_VAL;
	}

	void reduction() {
		// removing all whitespaces
		std::string::iterator end_pos;
		end_pos = std::remove(mathsproblem.begin(), mathsproblem.end(), ' ');
		mathsproblem.erase(end_pos, mathsproblem.end());
	}

	void modulus() {
		size_t end_pos;
		while ((start_pos = Metrics::mathsproblem.find("|", start_pos)) != std::string::npos) {

			end_pos = Metrics::mathsproblem.find("|", start_pos + 1);

			if (end_pos - start_pos > 2) {
				Metrics MathProb = Metrics::mathsproblem.substr(start_pos + 1, end_pos - start_pos - 1);
				MathProb.reduction();
				if (MathProb.isFunction()) {

					MathProb.functionFinder();
					MathProb.functionValueSplitter();
					Metrics::mathsproblem = std::to_string(
						MathProb.functions(std::find(funcs, funcs + 15, Metrics::function) - funcs, stod(MathProb.value))
					);
					return;
				}

				MathProb.MIN2MINX();
				MathProb.parenthesis();
				MathProb.modulus();
				MathProb.numSplitter();
				MathProb.OPSsplitter();

				mathsproblem = mathsproblem.substr(0, start_pos) +
					std::to_string(abs(MathProb.arithmetics())) +
					mathsproblem.substr(end_pos + 1, mathsproblem.length());
			}
			else {
				mathsproblem.erase(mathsproblem.begin() + end_pos);
				mathsproblem.erase(mathsproblem.begin() + start_pos);
			}
		}
	}

	void parenthesis() {
		size_t end_pos;
		while ((start_pos = Metrics::mathsproblem.find(')')) != std::string::npos) {
			std::string substr = Metrics::mathsproblem.substr(0, start_pos);
			std::reverse(substr.begin(), substr.end());
			end_pos = substr.find('(');

			Metrics MathProb = Metrics::mathsproblem.substr(start_pos - end_pos, end_pos);

			// rearranger!

			MathProb.numSplitter();
			MathProb.OPSsplitter();

			Metrics::mathsproblem = MathProb.mathsproblem.substr(0, start_pos - end_pos - 1) +
				std::to_string(MathProb.arithmetics()) +
				MathProb.mathsproblem.substr(start_pos + 1, MathProb.mathsproblem.length());
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

	double arithmetics() {
		static int position = 0;
		double value = Metrics::nVEC[position];
		for (char OPERATOR : Metrics::opsVEC) {
			switch (OPERATOR)
			{
			case '^': {
				position = position + 1;
				value = pow(value, nVEC[position]);
			}
			case '*': {
				position = position + 1;
				value = value * nVEC[position];
			}
			case '/': {
				position = position + 1;
				value = value / nVEC[position];
			}
			case '+': {
				position = position + 1;
				value = value + nVEC[position];
			}
			default:
				break;
			}
		}
		return value;

	}

};


int main() {
	while (true)
	{
		std::cout << "ENTER : ";
		Metrics problem;
		std::getline(std::cin, problem.mathsproblem);

		problem.reduction();
		if (problem.isFunction()) {
			problem.functionValueSplitter();
			std::cout << "        "
				<< problem.functions(problem.functionFinder(), stod(problem.value))
				<< std::endl;
			continue;
		}
		else if (!problem.is_number()) {

			problem.MIN2MINX();
			problem.parenthesis();
			problem.modulus();
			problem.numSplitter();
			problem.OPSsplitter();

			std::cout << "        " << problem.arithmetics() << std::endl;
		}
		else if (problem == "Exit") return 0;
		else std::cout << "        " << problem.mathsproblem << std::endl;
	}
}
