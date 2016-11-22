#include <stdio.h>
#include <stdbool.h>

#define max_no_of_items 10
#define max_char_on_report 200
#define max_no_of_type 3

const char* typeName[max_no_of_type] = {"Dinner    ", "Breakfast ", "Car Rental"};

typedef enum {DINNER, BREAKFAST, CAR_RENTAL} Type;

typedef struct {
  Type type;
  int amount;
} Expense;

Expense expenses[max_no_of_items];
char number_of_expenses = 0;

void addExpense(Expense expense) {
  expenses[number_of_expenses].amount = expense.amount;
  expenses[number_of_expenses].type = expense.type;
  number_of_expenses++;
}

void printer(char* text) {
  printf("%s",text);
}

static char* getDate() {
  return "9/12/2002";
}

float centsToDollar(int cents) {
  return cents/100.0;
}

int printReportHeader(char* text){
  return sprintf(text, "%s %s %s", "Expenses",getDate(),"\n");
}

bool isMealExpense(Expense expense) {
  return (expense.type==BREAKFAST || expense.type==DINNER)? true:false;
}

bool isOverages(Expense expense) {
 return (expense.type==DINNER && expense.amount > 5000) || 
        (expense.type==BREAKFAST && expense.amount > 1000);
}
int printReportItems(char* text, Expense expense) {
  return sprintf(text, "%s\t%s\t$%.02f\n", isOverages(expense) ? "x":" ",
    typeName[expense.type], centsToDollar(expense.amount));
}

int printReportMealExpenses(char* text, int mealExpenses) {
  return sprintf(text,"\nMeal expenses $%.02f", centsToDollar(mealExpenses));
}

int printReportTotal(char* text, int total) {
  return sprintf(text, "\nTotal $%.02f\n", centsToDollar(total));
}

void printReport() {
  int total=0;
  int mealExpenses=0;
  char text[max_char_on_report];
  int text_char_number;

  text_char_number = printReportHeader(text);

  int loop;
  for (loop=0; loop<number_of_expenses;loop++) {
    if (isMealExpense(expenses[loop])) mealExpenses += expenses[loop].amount;

    text_char_number += printReportItems(text+text_char_number, expenses[loop]);

    total += expenses[loop].amount; 
  }
  
  text_char_number += printReportMealExpenses(text+text_char_number, mealExpenses);
  text_char_number += printReportTotal(text+text_char_number, total);

  printer(text);
}

void test_Empty() {
  number_of_expenses = 0;
  printReport();
}

void test_OneDinner() {
  number_of_expenses = 0;
  addExpense((Expense){DINNER,1678});
  printReport();
}

void test_TwoMeals() {
  number_of_expenses = 0;
  addExpense((Expense){DINNER,1000});
  addExpense((Expense){BREAKFAST,500});
  printReport();
}

void test_TwoMealsAndCarRental() {
  number_of_expenses = 0;
  addExpense((Expense){DINNER,1000});
  addExpense((Expense){BREAKFAST,500});
  addExpense((Expense){CAR_RENTAL,50000});
  printReport();
}

void test_Overages() {
  number_of_expenses = 0;
  addExpense((Expense){BREAKFAST,1000});
  addExpense((Expense){BREAKFAST,1001});
  addExpense((Expense){DINNER,5000});
  addExpense((Expense){DINNER,5001});
  printReport();
}

int main(void) {
  printf("> Test Empty List\n");
  test_Empty();
  printf("> Test One Dinner\n");
  test_OneDinner();
  printf("> Test Two Meals\n");
  test_TwoMeals();
  printf("> Test Two Meals and Car Rental\n");
  test_TwoMealsAndCarRental();
  printf("> Test Overages\n");
  test_Overages();
	
	return 0;
}
