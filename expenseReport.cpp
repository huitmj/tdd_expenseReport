#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class ReportPrinter {
public:
	void print(string text) {};
};

class MockReportPrinter{
private:
  string printedText;
public: 
  void print(string text) {
		printedText += text;
	}
	string getText() {
		return printedText;
	}
};

class Expense {
private:
	int amount;
public:
	Expense(int amount) {
		this->amount = amount;
	}
  int getAmount() { return amount; }
	virtual bool isOverage(){ return false; };
	virtual bool isMeal(){ return false; };
};

class CarRentalExpense: public Expense {
public:
  CarRentalExpense(int amount): Expense(amount) {}
	bool isOverage() { return false; }
	bool isMeal() {	return false; }
};
class DinnerExpense: public Expense {
public:
  DinnerExpense(int amount): Expense(amount) {}
	bool isOverage() { return (getAmount()>5000) ? true:false; }
	bool isMeal() {	return true; }
};
class BreakfastExpense: public Expense {
public:
  BreakfastExpense(int amount): Expense(amount) {}
	bool isOverage() { return (getAmount()>1000) ? true:false; }
	bool isMeal() {	return true; }
};

class ExpenseReport {
private:
  int total;
  int mealExpenses;
	vector<Expense> expenses;
	
public:
	ExpenseReport() {
		total = 0;
		mealExpenses = 0;			
	}

    void totalUpExpenses() {
			for (int loop=0; loop<expenses.size();loop++) 
				addTotals(expenses[expenses.size()-1]);
    }

	void addTotals(Expense expense) {
		if (expense.isMeal()) mealExpenses += expense.getAmount();
		total += expense.getAmount();
	}

	void addExpense(Expense expense) {
		expenses.push_back(expense);
		cout << expenses.size() <<endl;
		cout << expenses[expenses.size()-1].getAmount()<<endl;
	}
		
	int getTotals() { return total;	}
	int getMealExpenses() { return mealExpenses; }
};

class ExpenseReporter {
private:
	ExpenseReport expenseReport;
//    private final ExpenseNamer expenseNamer = new ExpenseReportNamer();
  MockReportPrinter printer;
  void printExpensesAndTotals() {
		printHeader();
		printExpenses();
		printTotals();
	}

	void printExpenses() {
//		for (Expense expense : expenseReport.expenses)	printExpense(expense);
/* 		for (Expense n: expenseReport.expenses)
			printExpense(n);
 */		
/* 		for (vector<Expense>::iterator it expenseReport.expenses.begin(); it!= expenseReport.expenses.end; ++it)
			cout << *it.getTotals(); */
		
	}

	void printExpense(Expense expense) {
//		printer.print(string.format("%s\t%s\t$%.02f\n",
//						expense.isOverage() ? "X" : " ",
//						expenseNamer.getName(expense), penniesToDollars(expense.amount)));
	}

	void printTotals() {
 		char buffer[50];
		sprintf(buffer,"\nMeal expenses $%.02f", penniesToDollars(expenseReport.getMealExpenses()));
		printer.print(buffer);
		sprintf(buffer,"\nTotal $%.02f", penniesToDollars(expenseReport.getTotals()));
		printer.print(buffer);
 	}

	void printHeader() {
		printer.print("Expenses " + getDate() + "\n");
	}

	double penniesToDollars(int amount) {
		return amount / 100.0;
	}

  string getDate() {
		return "9/12/2002";
  }

public:
  ExpenseReporter() {

	}

  string printReport(MockReportPrinter printer) {
		this->printer = printer;
		expenseReport.totalUpExpenses();
		printExpensesAndTotals();
  	//cout << this->printer.getText();
		return this->printer.getText();
	}

  void addExpense(Expense expense) {
    expenseReport.addExpense(expense);
  }	
	
};

int main(void) {
	MockReportPrinter printer;
	ExpenseReporter report;
	
	string expected_empty_expenses ("Expenses 9/12/2002\n\nMeal expenses $0.00\nTotal $0.00");
	cout << (report.printReport(printer).compare(expected_empty_expenses)==0? "Pass": "Fail");

	report.addExpense(DinnerExpense(1678));
	report.addExpense(DinnerExpense(199));	
  return 0;
}
