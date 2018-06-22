#pragma once

namespace PaymentCalculator
{
	class CreditInfo
	{
	public:
		// Initializes CreditInfo instance with credit parameters:
		// amount [$]
		// interest [%]
		// downpayment [$]
		// term [years]
		CreditInfo(double amount, double interest, double downpayment, double term);

		inline double GetMounthlyPayment() { return mounthlyPayment; }
		inline double GetTotalInterest() { return totalInterest; }
		inline double GetTotalPayment() { return totalPayment; }

		Json::Value ToJSON();

	private:
		void InitializeCalculatedFields();

	private:
		double amount;
		double interest;
		double downpayment;
		double term;
		// calculable fields
		double mounthlyPayment;
		double totalInterest;
		double totalPayment;
	};
}