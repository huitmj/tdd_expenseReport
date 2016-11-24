#include <iostream>
#include <cstdio>
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
		//cout << printedText;
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
	virtual bool isOverage();
	virtual bool isMeal();
};

class CarRentalExpense: public Expense {
public:
  CarRentalExpense(int amount): Expense(amount) {};
	bool isOverage() { return false; }
	bool isMeal() {	return false; }
};
class DinnerExpense: public Expense {
public:
  DinnerExpense(int amount): Expense(amount) {};
	bool isOverage() { getAmount()>5000 ? true:false; }
	bool isMeal() {	return true; }
};
class BreakfastExpense: public Expense {
public:
  BreakfastExpense(int amount): Expense(amount) {};
	bool isOverage() { getAmount()>1000 ? true:false; }
	bool isMeal() {	return true; }
};

class ExpenseReport {
    //List<Expense> expenses = new ArrayList<Expense>();
private:
    int total;
    int mealExpenses;

public:
	ExpenseReport() {
		total = 0;
		mealExpenses = 0;			
	}

    void totalUpExpenses() {
//        for (Expense expense : expenses) addTotals(expense);
    }

	void addTotals(Expense expense) {
		if (expense.isMeal()) mealExpenses += expense.getAmount();
			total += expense.getAmount();
	}

    void addExpense(Expense expense) {
//        expenses.add(expense);
    }
		
	int getTotals() { return total;	}
	int getMealExpenses() { return mealExpenses;	}
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

  void printReport(MockReportPrinter printer) {
		this->printer = printer;
		expenseReport.totalUpExpenses();
		printExpensesAndTotals();
  	cout << this->printer.getText();
	}

  void addExpense(Expense expense) {
    expenseReport.addExpense(expense);
  }	
	
};

int main(void) {
	MockReportPrinter printer;
	ExpenseReporter report;
	
	report.printReport(printer);

	
  return 0;
}
