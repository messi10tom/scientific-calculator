#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>

class Numbermetrics {
	public:
		std::string Mathsproblem;
	private:
		int start_pos;

		bool containOperator(const char& SOP = 'a') {
			if (SOP == 'a') {
				for (char i : {'+', '-', '*', '/', '^'}) {
					return Mathsproblem.find(i) != std::string::npos;
				}
			}
			else {
				return Mathsproblem.find(SOP) != std::string::npos;
			}
		}

		//double getnum(std::string mprob, std::string& mptr) {
		//	double n;
		//	for (int i = 0; i < mprob.length(); i++) {
		//		if (mprob[i] == '+' || mprob[i] == '*' ||
		//			mprob[i] == '/' || mprob[i] == '^') {
		//			funcy func = isfunc(mprob.substr(0, i));
		//			if (func.isfunc) {
		//				n = functions(func);
		//			}
		//			else {
		//				n = stoi(mprob.substr(0, i));
		//			}
		//			mptr = mprob.substr(i + 1);
		//			return n;
		//		}

		//	}
		//}

		double getNum() {
			while ((start_pos = Mathsproblem.find('+')) != std::string::npos ||
				   (start_pos = Mathsproblem.find('-')) != std::string::npos ||
				   (start_pos = Mathsproblem.find('*')) != std::string::npos || 
				   (start_pos = Mathsproblem.find('/')) != std::string::npos ||
				   (start_pos = Mathsproblem.find('^')) != std::string::npos ){
				

			}
		}
};

class Functionmetrics {
	public:
		std::string mathsFunction;
		std::string function;
		std::string value;

	private:
		int NULLFn = 14;

		void functionFinder() {
			int func = 14;
			    //                      0      1	  2	     3	    4	   5	  6
			std::string funcs[15] = { "sin", "cos", "tan", "sec", "cot", "log", "ln",
				//					   7		 8		   9	  10	   11		12
									"cosec", "antilog", "ln-1", "sin-1", "cos-1", "tan-1",
				//					13      14
									"!", "nullfn" };
			for (int i = 0; i < NULLFn; i++) {
				if (mathsFunction.find(funcs[i]) != std::string::npos) func = i;
				
			}
			function = funcs[func];
		}

		void functionValueSplitter() {
			int pos;
			if (NULLFn != 14) {
				if ((pos = mathsFunction.find('(')) != std::string::npos) {
					value = mathsFunction.substr(pos + 1, mathsFunction.find(')') - pos - 1);
				}

				else {
					value = mathsFunction.substr(function.length(), mathsFunction.length());
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
			if (!(value.find_first_not_of("0123456789.") == std::string::npos)) {
				return false;
			}
			return true;
		}
};
