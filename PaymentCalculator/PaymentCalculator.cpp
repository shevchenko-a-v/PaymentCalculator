// PaymentCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <regex>
#include <list>

#include "Constants.h"
#include "Credit.h"

using namespace std;
using namespace PaymentCalculator;


double ExtractValueFromLine(const string& line, const string &startsWith)
{
	regex r(R"(^\s*)" + startsWith + R"(\s*:\s*([\d]+([\.,][\d]+)?)%?\s*$)", regex_constants::icase); // case insensitive
	smatch m;
	regex_search(line, m, r);
	if (m.empty())
		throw invalid_argument("Line \"" + line + "\" has invalid format.\nExpected format is: \"" + startsWith + ": [value]\", where [value] is a positive value with floating point allowed.");
	string foundValue = m[1].str(); // take second group since the first one refers to entire source string
	replace(foundValue.begin(), foundValue.end(), ',', '.'); // replace all ',' with '.' in order to support both formats for floating point numbers
	try
	{
		return stod(foundValue);
	}
	catch (invalid_argument)
	{
		// rethrow with clear message
		throw invalid_argument("Specified " + startsWith + " value (" + foundValue + ") is not a valid digital number.");
	}
}

int main()
{
	try
	{
		cout << "Enter credit parameters in following order:" << endl 
			<< Constants::AMOUNT_LINE_START << endl 
			<< Constants::INTEREST_LINE_START << endl 
			<< Constants::DOWNPAYMENT_LINE_START << endl 
			<< Constants::TERM_LINE_START << endl
			<< "Press enter after the last parameter of the last credit has been entered." << endl << endl;
		list<Credit> credits;
		string inputLine;
		// read credit info starting from "amount"
		while (getline(cin, inputLine) && inputLine.size() > 0)
		{
			double amount = ExtractValueFromLine(inputLine, Constants::AMOUNT_LINE_START);
			getline(cin, inputLine);
			double interest = ExtractValueFromLine(inputLine, Constants::INTEREST_LINE_START);
			getline(cin, inputLine);
			double downpayment = ExtractValueFromLine(inputLine, Constants::DOWNPAYMENT_LINE_START);
			getline(cin, inputLine);
			double term = ExtractValueFromLine(inputLine, Constants::TERM_LINE_START);

			credits.push_back(Credit(amount, interest, downpayment, term));
		}

		// print JSON representation of credit calculated parameters
		for (auto credit : credits)
		{
			cout << credit.GetCalculatedParametersAsJSON() << endl;
		}
	}
	catch (exception e)
	{
		cout << "Error occured:" << endl;
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Undefined error occured!" << endl;
	}
	getchar(); // don't close application immediately so that user could see the result
	return 0;
}
