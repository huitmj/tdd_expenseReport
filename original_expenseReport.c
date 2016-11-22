#include <stdio.h>

#define max_no_of_items 10
#define max_char_on_report 200

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

void printReport() {
  int total=0;
  int mealExpenses=0;
  char text[max_char_on_report];
  int text_char_number;
  text_char_number = sprintf(text, "%s %s %s", "Expenses",getDate(),"\n");
  
  int loop;
  for (loop=0; loop<number_of_expenses;loop++) {
    if (expenses[loop].type==BREAKFAST || expenses[loop].type==DINNER)
      mealExpenses += expenses[loop].amount;
    char* item_type;
    switch (expenses[loop].type) {
      case DINNER:     item_type = "Dinner    "; break;
      case BREAKFAST:  item_type = "Breakfast "; break;
      case CAR_RENTAL: item_type = "Car Rental"; break;
    }
    text_char_number += sprintf(text+text_char_number, 
                        "%s\t%s\t$%.02f\n", 
                        ( (expenses[loop].type==DINNER && 
                           expenses[loop].amount > 5000)
                        || expenses[loop].type==BREAKFAST && 
                           expenses[loop].amount > 1000) ? "x":" ",
                        item_type, expenses[loop].amount/100.0);
    total += expenses[loop].amount; 
  }

  text_char_number += sprintf(text+text_char_number, 
                      "\nMeal expenses $%.02f", 
                      mealExpenses / 100.0);
  text_char_number += sprintf(text+text_char_number, 
                      "\nTotal $%.02f\n", 
                      total / 100.0);
  
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
}
