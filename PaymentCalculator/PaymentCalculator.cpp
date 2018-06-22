// PaymentCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <regex>
#include <list>
#include <iomanip>

#include "Constants.h"
#include "CreditInfo.h"

using namespace std;
using namespace PaymentCalculator;
/*
bool GetLineInLowerCase(istream &stream, string &line)
{
	if (getline(cin, line))
	{
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		return line.size() > 0;
	}
	return false;
}
*/
double ExtractValueFromLine(const string& line, const string &startsWith)
{
	regex r(R"(^)" + startsWith + R"(:\s*([\d]+([\.,][\d]+)?)%?$)", regex_constants::icase); // case insensitive
	smatch m;
	regex_search(line, m, r);
	if (m.empty())
		throw invalid_argument("Line \"" + line + "\" has invalid format.\nExpected format is: \"" + startsWith + ": [value]\", where [value] is a positive value with floating point allowed.");
	string foundValue = m[1].str();
	replace(foundValue.begin(), foundValue.end(), ',', '.'); // replace all , with . in order to support both formats for floating point numbers
	try
	{
		return stod(foundValue);
	}
	catch (invalid_argument e)
	{
		throw invalid_argument("Specified " + startsWith + " value (" + foundValue + ") is not a valid digital number.");
	}
}

int main()
{
	try
	{
		list<CreditInfo> credits;
		string inputLine;
		while (getline(cin, inputLine) && inputLine.size() > 0)
		{
			double amount = ExtractValueFromLine(inputLine, Constants::AMOUNT_LINE_START);
			getline(cin, inputLine);
			double interest = ExtractValueFromLine(inputLine, Constants::INTEREST_LINE_START);
			getline(cin, inputLine);
			double downpayment = ExtractValueFromLine(inputLine, Constants::DOWNPAYMENT_LINE_START);
			getline(cin, inputLine);
			double term = ExtractValueFromLine(inputLine, Constants::TERM_LINE_START);

			credits.push_back(CreditInfo(amount, interest, downpayment, term));
		}

		cout << fixed << setprecision(2);
		for (auto credit : credits)
		{
			cout << "Mounthly: " << credit.GetMounthlyPayment() << endl;
			cout << "TotalInterest: " << credit.GetTotalInterest() << endl;
			cout << "Total: " << credit.GetTotalPayment() << endl;
		}
	}
	catch (exception e)
	{
		cout << endl << "Error occured!" << endl;
		cout << e.what() << endl;
		cin.get();
	}
    return 0;
}

