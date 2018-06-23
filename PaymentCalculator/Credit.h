#pragma once

namespace PaymentCalculator
{
	class Credit
	{
	public:
		// Initializes CreditInfo instance with credit parameters:
		// amount [$]
		// interest [%]
		// downpayment [$]
		// term [years]
		Credit(double amount, double interest, double downpayment, double term);
		
		Json::Value GetCalculatedParametersAsJSON() const;

	private:
		// Calculates MounthlyPayment, TotalInterest and TotalPayment
		void InitializeCalculatedFields();

	private:
		double _amount;
		double _interest;
		double _downpayment;
		double _term;
		// calculated fields
		double _monthlyPayment;
		double _totalInterest;
		double _totalPayment;
	};
}