#include "stdafx.h"
#include <math.h>
#include "CreditInfo.h"

namespace PaymentCalculator
{
	CreditInfo::CreditInfo(double amount, double interest, double downpayment, double term)
	{
		if (downpayment >= amount)
			throw std::invalid_argument("Downpayment must be less than amount of credit.");
		if (downpayment < 0 || amount < 0 || interest < 0 || term < 0)
			throw std::invalid_argument("All credit parameters must be non-negative.");

		this->amount = amount;
		this->interest = interest;
		this->downpayment = downpayment;
		this->term = term;
		InitializeCalculatedFields();
	}

	void CreditInfo::InitializeCalculatedFields()
	{
		const int mounthInYear = 12;
		double termInMounths = term * mounthInYear;
		double creditAmount = amount - downpayment;

		double interestPerMounth = interest / 100 / mounthInYear;
		double coeff = interestPerMounth / (1 - 1 / pow(1 + interestPerMounth, termInMounths));

		mounthlyPayment = creditAmount * coeff;
		totalPayment = mounthlyPayment * termInMounths;
		totalInterest = totalPayment - creditAmount;
	}

}