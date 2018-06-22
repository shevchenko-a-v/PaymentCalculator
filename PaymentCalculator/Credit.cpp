#include "stdafx.h"
#include <math.h>
#include "Credit.h"
#include "Constants.h"

namespace PaymentCalculator
{
	Credit::Credit(double amount, double interest, double downpayment, double term)
	{
		if (downpayment >= amount)
			throw std::invalid_argument("Downpayment must be less than amount of credit.");
		if (downpayment < 0 || amount < 0 || interest < 0 || term < 0)
			throw std::invalid_argument("All credit parameters must be non-negative.");

		this->_amount = amount;
		this->_interest = interest;
		this->_downpayment = downpayment;
		this->_term = term;
		InitializeCalculatedFields();
	}

	Json::Value Credit::ToJSON() const
	{
		Json::Value value;
		value[Constants::MONTHLY_PAYMENT_KEY] = _monthlyPayment;
		value[Constants::TOTAL_INTEREST_KEY] = _totalInterest;
		value[Constants::TOTAL_PAYMENT_KEY] = _totalPayment;
		return value;
	}

	void Credit::InitializeCalculatedFields()
	{
		const int monthsInYear = 12;
		double termInMonths = _term * monthsInYear;
		double creditAmount = _amount - _downpayment;

		double decimalInterestPerMonth = _interest / 100 / monthsInYear;
		double coeff = decimalInterestPerMonth / (1 - 1 / pow(1 + decimalInterestPerMonth, termInMonths)); // calculate part of credit which must be paid every month

		_monthlyPayment = creditAmount * coeff;
		_totalPayment = _monthlyPayment * termInMonths;
		_totalInterest = _totalPayment - creditAmount;
	}

}