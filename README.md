# KMC Budget Tracker and Analyzer

## A. Project Introduction

KMC Budget Tracker and Analyzer is a console-based application developed in the C programming language for viewing and analyzing Karachi Municipal Corporation (KMC) budget information for 2026-27. The program allows users to view all saved budget categories, search categories and departments, view department-wise budget information, calculate total budget figures, view expenditure details, calculate the remaining budget, and generate a budget summary report. Users can also add new budget categories and update saved category amounts. File handling is used to save user-entered records in `file.txt` so that the records can be loaded again when the program is started.

## B. Features & Test Cases (Execution Scenarios)

### Case 1: View All Budget Categories

- **Description:** Displays all saved budget categories, including official records and categories added by the user.
- **Inputs:** Select menu option `1`.
- **Expected Output:** The program displays the saved categories, their departments, allocated amounts, spent amounts, and the total number of records.
- **Screenshot:** ![Case 1](screenshots/case1_view_categories.png)

### Case 2: Search Budget Category

- **Description:** Searches saved categories, departments, and expenditure heads using a keyword.
- **Inputs:** Select menu option `2` and enter a keyword such as `road`, `pension`, or `health`.
- **Expected Output:** Matching saved categories, departments, and expenditure heads are displayed. A no-match message is displayed where no result is found.
- **Screenshot:** ![Case 2](screenshots/case2_search_category.png)

### Case 3: View Department-Wise Budget

- **Description:** Displays budget information for the six selected KMC departments and compares their budget amounts.
- **Inputs:** Select menu option `3`.
- **Expected Output:** The program displays department-wise amounts and comparison information, including the highest and lowest budget details.
- **Screenshot:** ![Case 3](screenshots/case3_department_budget.png)

### Case 4: Calculate Total Budget

- **Description:** Calculates the total receipts and total expenditure and displays expenditure by head, the six-department subtotal, and saved category totals.
- **Inputs:** Select menu option `4`.
- **Expected Output:** The program displays the budget calculations and explains that saved category amounts are parts of the budget, not additional money to add to the overall totals.
- **Screenshot:** ![Case 4](screenshots/case4_total_budget.png)

### Case 5: View Budget Expenditure

- **Description:** Displays expenditure information for the official expenditure heads, selected departments, and saved categories that have a spent amount.
- **Inputs:** Select menu option `5`.
- **Expected Output:** The program displays the budget estimates, revised estimates, percentages, and available saved-category spending details.
- **Screenshot:** ![Case 5](screenshots/case5_budget_expenditure.png)

### Case 6: Calculate Remaining Budget

- **Description:** Calculates the overall remaining budget and the remaining amount for saved categories with a spent amount.
- **Inputs:** Select menu option `6`.
- **Expected Output:** The program displays total receipts, total expenditure, the calculated surplus, and saved-category allocated, spent, and remaining amounts where available.
- **Screenshot:** ![Case 6](screenshots/case6_remaining_budget.png)

### Case 7: Generate Budget Summary Report

- **Description:** Generates a summary of the overall budget, expenditure heads, department figures, and saved category information.
- **Inputs:** Select menu option `7`.
- **Expected Output:** The program displays the budget summary report and its relevant calculations.
- **Screenshot:** ![Case 7](screenshots/case7_summary_report.png)

### Case 8: Exit Program

- **Description:** Tests the program's exit option.
- **Inputs:** Select menu option `8`.
- **Expected Output:** The program displays a thank-you message and terminates.
- **Screenshot:** ![Case 8](screenshots/case8_exit.png)

### Case 9: Add New Budget Category

- **Description:** Allows the user to add a new category with a department, allocated amount, and spent amount. The program checks for an empty or duplicate category name.
- **Inputs:** Select menu option `9` and enter the requested category details.
- **Expected Output:** The new category is added to the records and saved in `file.txt`. A confirmation message is displayed.
- **Screenshot:** ![Case 9](screenshots/case9_add_category.png)

### Case 10: Update a Saved Category

- **Description:** Allows the user to select a saved category and update its spent amount. The allocated amount can be changed for user-added records only.
- **Inputs:** Select menu option `10`, enter a record number, and select the required update option.
- **Expected Output:** The selected record is updated and the changes are saved in `file.txt`. Official allocated amounts cannot be changed.
- **Screenshot:** ![Case 10](screenshots/case10_update_category.png)

### Case 11: Invalid Input Handling

- **Description:** Tests how the program handles an invalid menu selection.
- **Inputs:** Enter a menu option outside the valid range, for example `15`.
- **Expected Output:** The program displays an invalid-choice message and asks the user to select a valid menu option.
- **Screenshot:** ![Case 11](screenshots/case11_invalid_input.png)

## C. Instructions to Clone and Execute

### Step 1: Clone the Repository

Open a terminal and execute the following command. Replace `YOUR_USERNAME` with your GitHub username.

```bash
git clone https://github.com/YOUR_USERNAME/kmc_budget_tracker.git
```

Move into the project folder:

```bash
cd kmc_budget_tracker
```

### Step 2: Compile the Code

Make sure GCC is installed, then compile the source file:

```bash
gcc main.c -o kmc_budget_tracker.exe
```

### Step 3: Run the Program

On Windows Command Prompt, execute:

```bash
kmc_budget_tracker.exe
```

The program displays the main menu. Enter a menu number to use a feature. The program creates `file.txt` with the default official records if the data file is not present. User-added and updated records are saved in this file.
