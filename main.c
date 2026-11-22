#include <stdio.h> 
#include <string.h>
/* Limits and file name */
#define NAME_LEN 60
#define DEPT_LEN 30
#define SOURCE_LEN 10
#define LABEL_LEN 100
#define LINE_LEN 200
#define MAX_RECORDS 100
#define OFFICIAL_COUNT 24
#define DEPT_COUNT 6
#define HEAD_COUNT 6
#define DATA_FILE "file.txt" /* Budget figures used in the reports (Rs. million) */
const char headNames[HEAD_COUNT][NAME_LEN] = {
"Establishment (Salary+Pension)", "Contingent", "Repair and Maintenance", "Major Development Works", "Capital (Revenue Component)", "District ADP Funds" };
const double headAmounts[HEAD_COUNT][4] = {
{37292.203, 21375.137, 31591.494, 21066.136}, { 4243.565, 3515.805, 3048.015, 1608.951}, { 476.830, 297.260, 414.610, 194.102}, { 8595.262, 7962.438, 10447.200, 1066.948}, { 798.665, 470.092, 636.015, 454.132}, { 9000.000, 5269.010, 9000.000, 6705.212}
};
const double currentReceipts = 58103.540;
const double capitalReceipts = 2347.890;
const double officialSurplus = 44.905;
/* Six KMC departments */
const char deptNames[DEPT_COUNT][NAME_LEN] = {
"Secretariat Group", "Finance & Accounts", "Parks & Horticulture", "Law", "Revenue Departments", "Recreation, Culture & Sports", };
const double deptAmounts[DEPT_COUNT][3] = {
{ 1452.297, 982.457, 1396.944}, { 760.924, 502.034, 602.243}, { 2650.702, 1339.945, 1773.377}, { 261.990, 132.700, 254.645}, { 2231.804, 1548.059, 2101.327}, { 1441.095, 831.435, 1284.042}, };
/* Existing development schemes and their allocations */
const char officialNames[OFFICIAL_COUNT][NAME_LEN] = {
"Special Development Projects / Works", "Payment of Medical Insurance Bills", "Automation of Various Departments", "Development and Improvement of Roads", "Dedicated Development Grant for Minority Community", "Annual Maintenance of Roads, Footpaths, Bridges", "Development Work for Union Committees (UCs)", "Development Work for Parks of Union Committees",
"Lungs of Karachi (Urban Forest)", "Solarization Initiatives for all UCs", "Block Allocation for New Development Schemes", "Payment to Others for Service Rendered", "National Celebrations Campaign", "Grant for Medical Institutions", "Govt. Grant for TMC Pensioners (Court Order)", "Cleaning and Desilting of Storm Water Drains", "ADP: Infrastructure (Roads, Flyovers, Bridges)", "ADP: Municipal Services", "ADP: Health", "ADP: Culture and Tourism (Culture and Sports)", "ADP: Culture and Tourism (Zoo and Safari)", "ADP: Parks and Horticulture", "ADP: Information Technology", "ADP: Block Allocation for New Schemes" };
const char officialDepts[OFFICIAL_COUNT][DEPT_LEN] = {
"Engineering", "M&HS", "I.T", "Engineering", "Engineering", "Engineering", "Engineering", "P&H", "P&H", "Engineering", "Engineering", "Various Departments", "C&S", "M&HS", "F&P", "Municipal Services", "District ADP", "District ADP", "District ADP", "District ADP", "District ADP", "District ADP", "District ADP", "District ADP" };
const double officialAmounts[OFFICIAL_COUNT] = {
100.000, 215.000, 100.000, 400.000, 100.000, 480.000, 1200.000, 300.000, 100.000, 500.000, 500.000, 100.000, 100.000, 62.500, 4800.000, 800.000, 2170.865, 55.215, 60.000, 379.001, 219.008, 906.208, 35.752, 5173.950
};
/* Records loaded from the text file, including newly added entries */
char recordNames[MAX_RECORDS][NAME_LEN];
char recordDepts[MAX_RECORDS][DEPT_LEN];
char recordSource[MAX_RECORDS][SOURCE_LEN];
double recordAmounts[MAX_RECORDS][2];
int recordCount = 0;
/* Function declarations */
int readLine(char text[], int size);
int getMenuChoice(void);
double getAmountInput(const char prompt[]);
int getNumberInRange(const char prompt[], int low, int high);
int isBlank(const char text[]);
void toLowerCase(char text[]);
void spacesToUnderscores(char text[]);
void underscoresToSpaces(char text[]);
double absoluteValue(double number);
double calculatePercentage(double part, double whole);
double calculateHeadTotal(int column);
double calculateDepartmentTotal(int column);
double calculateRecordTotal(int column);
double calculateUserTotal(int column);
void findHighestAndLowest(const double values[], int count, int *highIndex, int *lowIndex);
void makeLabel(char label[], const char name[], const char dept[]);
int containsText(const char text[], const char keywordLower[]);
void printLine(char symbol, int length);
void pauseScreen(void);
void printRecord(int index);
void displayRecordNames(void);
void saveAllRecords(void);
void appendRecordToFile(int index);
void createDefaultRecords(void);
void loadRecords(void);
void displayMenu(void);
void displayBudgetCategories(void);
void searchBudget(void);
void viewDepartmentWiseBudget(void);
void calculateTotalBudget(void);
void viewBudgetExpenditure(void);
void calculateRemainingBudget(void);
void displayBudgetReport(void);
void addNewCategory(void);
void updateCategory(void);
/* Read a complete line without leaving extra characters in input. */
int readLine(char text[], int size) {
int length;
int ch;
if (fgets(text, size, stdin) == NULL) {
text[0] = '\0';
return 0;
}
length = strlen(text);
if (length > 0 && text[length - 1] == '\n') {
text[length - 1] = '\0';
} else {
while ((ch = getchar()) != '\n' && ch != EOF) {
}
}
return 1;
}
int getMenuChoice(void) {
char line[LINE_LEN];
int choice;
printf("Enter your choice (1-10): ");
if (!readLine(line, LINE_LEN)) {
return 8;
}
if (sscanf(line, "%d", &choice) != 1) {
return 0;
}
return choice;
}
double getAmountInput(const char prompt[]) {
char line[LINE_LEN];
double value;
while (1) {
printf("%s", prompt);
if (!readLine(line, LINE_LEN)) {
return -1.0;
}
if (sscanf(line, "%lf", &value) == 1 && value >= 0.0) {
return value;
}
printf(" Invalid amount. Please enter a number that is 0 or more.\n");
}
}
int getNumberInRange(const char prompt[], int low, int high) {
char line[LINE_LEN];
int value;
while (1) {
printf("%s", prompt);
if (!readLine(line, LINE_LEN)) {
return -1;
}
if (sscanf(line, "%d", &value) == 1 && value >= low && value <= high) {
return value;
}
printf(" Please enter a whole number from %d to %d.\n", low, high);
}
}
int isBlank(const char text[]) {
int i;
for (i = 0; text[i] != '\0'; i++) {
if (text[i] != ' ') {
return 0;
}
}
return 1;
}
void toLowerCase(char text[]) {
int i;
for (i = 0; text[i] != '\0'; i++) {
if (text[i] >= 'A' && text[i] <= 'Z') {
text[i] = text[i] + 32;
}
}
}
void spacesToUnderscores(char text[]) {
int i;
for (i = 0; text[i] != '\0'; i++) {
if (text[i] == ' ') {
text[i] = '_';
}
}
}
void underscoresToSpaces(char text[]) {
int i;
for (i = 0; text[i] != '\0'; i++) {
if (text[i] == '_') {
text[i] = ' ';
}
}
}
void makeLabel(char label[], const char name[], const char dept[]) {
strcpy(label, name);
strcat(label, " (");
strcat(label, dept);
strcat(label, ")");
}
int containsText(const char text[], const char keywordLower[]) {
char copy[NAME_LEN];
strcpy(copy, text);
toLowerCase(copy);
return strstr(copy, keywordLower) != NULL;
}
double absoluteValue(double number) {
if (number < 0.0) {
return -number;
}
return number;
}
double calculatePercentage(double part, double whole) {
if (whole == 0.0) {
return 0.0;
}
return part / whole * 100.0;
}
static double sumHeadsRec(int column, int index) {
if (index == HEAD_COUNT) return 0.0;
return headAmounts[index][column] + sumHeadsRec(column, index + 1);
}
static double sumDepartmentsRec(int column, int index) {
if (index == DEPT_COUNT) return 0.0;
return deptAmounts[index][column] + sumDepartmentsRec(column, index + 1);
}
static double sumRecordsRec(int column, int index) {
if (index == recordCount) return 0.0;
return recordAmounts[index][column] + sumRecordsRec(column, index + 1);
}
static double sumUserRecordsRec(int column, int index) {
if (index == recordCount) return 0.0;
return (strcmp(recordSource[index], "USER") == 0 ? recordAmounts[index][column] : 0.0)
+ sumUserRecordsRec(column, index + 1);
}
double calculateHeadTotal(int column) { return sumHeadsRec(column, 0); }
double calculateDepartmentTotal(int column) { return sumDepartmentsRec(column, 0); }
double calculateRecordTotal(int column) { return sumRecordsRec(column, 0); }
double calculateUserTotal(int column) { return sumUserRecordsRec(column, 0); }
static void findHighLowRec(const double values[], int count, int i, int *high, int *low) {
if (i == count) return;
if (values[i] > 0.0) {
if (*high == -1 || values[i] > values[*high]) *high = i;
if (*low == -1 || values[i] < values[*low]) *low = i;
}
findHighLowRec(values, count, i + 1, high, low);
}
void findHighestAndLowest(const double values[], int count, int *highIndex, int *lowIndex) {
*highIndex = *lowIndex = -1;
findHighLowRec(values, count, 0, highIndex, lowIndex);
}
void printLine(char symbol, int length) {
int i;
for (i = 0; i < length; i++) {
putchar(symbol);
}
putchar('\n');
}
void pauseScreen(void) {
char line[LINE_LEN];
printf("\nPress Enter to return to the menu...");
readLine(line, LINE_LEN);
}
void printRecord(int index) {
printf("%3d. %s\n", index + 1, recordNames[index]);
printf(" Department: %s | Allocated: %.3f | Source: %s\n", recordDepts[index], recordAmounts[index][0], recordSource[index]);
}
void displayRecordNames(void) {
int i;
printLine('-', 70);
for (i = 0; i < recordCount; i++) {
if (strcmp(recordSource[i], "USER") == 0) {
printf("%3d. %s [USER]\n", i + 1, recordNames[i]);
} else {
printf("%3d. %s\n", i + 1, recordNames[i]);
}
}
printLine('-', 70);
}
void saveAllRecords(void) {
FILE *fp;
int i;
char name[NAME_LEN];
char dept[DEPT_LEN];
fp = fopen(DATA_FILE, "w");
if (fp == NULL) {
printf("Error: could not open %s for writing.\n", DATA_FILE);
return;
}
for (i = 0; i < recordCount; i++) {
strcpy(name, recordNames[i]);
strcpy(dept, recordDepts[i]);
spacesToUnderscores(name);
spacesToUnderscores(dept);
fprintf(fp, "%s %s %s %.3f %.3f\n", recordSource[i], name, dept, recordAmounts[i][0], recordAmounts[i][1]);
}
fclose(fp);
}
void appendRecordToFile(int index) {
FILE *fp;
char name[NAME_LEN];
char dept[DEPT_LEN];
fp = fopen(DATA_FILE, "a");
if (fp == NULL) {
printf("Error: could not open %s for appending.\n", DATA_FILE);
return;
}
strcpy(name, recordNames[index]);
strcpy(dept, recordDepts[index]);
spacesToUnderscores(name);
spacesToUnderscores(dept);
fprintf(fp, "%s %s %s %.3f %.3f\n", recordSource[index], name, dept, recordAmounts[index][0], recordAmounts[index][1]);
fclose(fp);
}
void createDefaultRecords(void) {
int i;
for (i = 0; i < OFFICIAL_COUNT; i++) {
strcpy(recordNames[i], officialNames[i]);
strcpy(recordDepts[i], officialDepts[i]);
strcpy(recordSource[i], "OFFICIAL");
recordAmounts[i][0] = officialAmounts[i];
recordAmounts[i][1] = 0.0;
}
recordCount = OFFICIAL_COUNT;
saveAllRecords();
}
/* Load saved entries or create the initial records. */
void loadRecords(void) {
FILE *fp;
char source[SOURCE_LEN];
char name[NAME_LEN];
char dept[DEPT_LEN];
double allocated;
double spent;
recordCount = 0;
fp = fopen(DATA_FILE, "r");
if (fp == NULL) {
printf("%s was not found. Creating it with the official KMC categories...\n", DATA_FILE);
createDefaultRecords();
return;
}
while (recordCount < MAX_RECORDS &&
fscanf(fp, "%9s %59s %29s %lf %lf", source, name, dept, &allocated, &spent) == 5)
{
underscoresToSpaces(name);
underscoresToSpaces(dept);
strcpy(recordSource[recordCount], source);
strcpy(recordNames[recordCount], name);
strcpy(recordDepts[recordCount], dept);
recordAmounts[recordCount][0] = allocated;
recordAmounts[recordCount][1] = spent;
recordCount++;
}
fclose(fp);
if (recordCount == 0) {
printf("%s is empty. Creating the official KMC categories...\n", DATA_FILE);
createDefaultRecords();
} else {
printf("Loaded %d saved records from %s.\n", recordCount, DATA_FILE);
}
}
/* Main options shown to the user. */
void displayMenu(void) {
printf("\n");
printLine('=', 60);
printf(" KARACHI MUNICIPAL BUDGET TRACKER AND ANALYZER\n");
printf(" KMC Budget 2026-27 (amounts in Rs. million)\n");
printLine('=', 60);
printf(" 1. View All Budget Categories\n");
printf(" 2. Search Budget Category\n");
printf(" 3. View Department-Wise Budget\n");
printf(" 4. Calculate Total Budget\n");
printf(" 5. View Budget Expenditure\n");
printf(" 6. Calculate Remaining Budget\n");
printf(" 7. Generate Budget Summary Report\n");
printf(" 8. Exit\n");
printf(" 9. Add New Budget Category (saved in file.txt)\n");
printf(" 10. Update a Saved Category (saved in file.txt)\n");
printLine('-', 60);
}
void displayBudgetCategories(void) {
int i;
int userCount = 0;
printf("\nALL SAVED BUDGET CATEGORIES 2026-27 (Rs. million)\n");
printLine('-', 70);
for (i = 0; i < recordCount; i++) {
printRecord(i);
if (strcmp(recordSource[i], "USER") == 0) {
userCount++;
}
}
printLine('-', 70);
printf("Total records: %d (official: %d, entered by user: %d)\n", recordCount, recordCount - userCount, userCount);
}
/* Find matching budget entries. */
void searchBudget(void) {
char keyword[NAME_LEN];
int i;
int found;
printf("\nSEARCH BUDGET CATEGORY\n");
printf("Enter a word to search (for example road, pension, health): ");
if (!readLine(keyword, NAME_LEN) || isBlank(keyword)) {
printf("No search word was entered.\n");
return;
}
toLowerCase(keyword);
found = 0;
printf("\nA) Saved categories:\n");
for (i = 0; i < recordCount; i++) {
if (containsText(recordNames[i], keyword) || containsText(recordDepts[i], keyword)) {
printRecord(i);
found++;
}
}
if (found == 0) {
printf(" No match.\n");
}
printf("\nB) Departments (Budget 2026-27):\n");
found = 0;
for (i = 0; i < DEPT_COUNT; i++) {
if (containsText(deptNames[i], keyword)) {
printf(" %s: %.3f\n", deptNames[i], deptAmounts[i][0]);
found++;
}
}
if (found == 0) {
printf(" No match.\n");
}
printf("\nC) Expenditure heads (Budget 2026-27):\n");
found = 0;
for (i = 0; i < HEAD_COUNT; i++) {
if (containsText(headNames[i], keyword)) {
printf(" %s: %.3f\n", headNames[i], headAmounts[i][0]);
found++;
}
}
if (found == 0) {
printf(" No match.\n");
}
}
void viewDepartmentWiseBudget(void) {
double current[DEPT_COUNT];
double total;
double average;
double change;
int i;
int highIndex;
int lowIndex;
int aboveCount = 0;
char level[5];
for (i = 0; i < DEPT_COUNT; i++) {
current[i] = deptAmounts[i][0];
}
total = calculateDepartmentTotal(0);
average = total / DEPT_COUNT;
printf("\nDEPARTMENT-WISE BUDGET 2026-27 (Rs. million)\n");
printLine('-', 77);
printf("%2s %-30s %10s %10s %8s %7s %-4s\n", "No", "Department", "2026-27 BE", "2025-26 BE", "Change%", "Share%", "Lvl");
printLine('-', 77);
for (i = 0; i < DEPT_COUNT; i++) {
change = 0.0;
if (deptAmounts[i][2] > 0.0) {
change = (deptAmounts[i][0] - deptAmounts[i][2]) / deptAmounts[i][2] * 100.0;
}
if (deptAmounts[i][0] > average) {
strcpy(level, "High");
aboveCount++;
} else {
strcpy(level, "Low");
}
printf("%2d %-30s %10.3f %10.3f %8.1f %7.1f %-4s\n", i + 1, deptNames[i], deptAmounts[i][0], deptAmounts[i][2], change, calculatePercentage(deptAmounts[i][0], total), level);
}
printLine('-', 77);
printf("%-33s %10.3f %10.3f\n", "TOTAL", total, calculateDepartmentTotal(2));
printf("Average per department: %.3f\n", average);
printf("Lvl: High = above the average, Low = at or below the average.\n");
findHighestAndLowest(current, DEPT_COUNT, &highIndex, &lowIndex);
printf("\nHighest allocation: %s (%.3f)\n", deptNames[highIndex], current[highIndex]);
printf("Lowest allocation : %s (%.3f)\n", deptNames[lowIndex], current[lowIndex]);
printf("Departments above average: %d of %d\n", aboveCount, DEPT_COUNT);
printf("Note: this view includes the first six departments from the source data.\n");
printf(" Department totals and averages cover all six displayed rows.\n");
}
void calculateTotalBudget(void) {
double totalReceipts;
double totalExpenditure;
double currentExpenditure;
double developmentExpenditure;
int i;
totalReceipts = currentReceipts + capitalReceipts;
totalExpenditure = calculateHeadTotal(0);
currentExpenditure = headAmounts[0][0] + headAmounts[1][0] + headAmounts[2][0];
developmentExpenditure = headAmounts[3][0] + headAmounts[4][0];
printf("\nTOTAL BUDGET 2026-27 (Rs. million)\n");
printLine('-', 60);
printf("A) Receipts\n");
printf(" Current receipts : %12.3f\n", currentReceipts);
printf(" Capital receipts : %12.3f\n", capitalReceipts);
printf(" TOTAL RECEIPTS : %12.3f\n", totalReceipts);
printf("\nB) Expenditure by head\n");
for (i = 0; i < HEAD_COUNT; i++) {
printf(" %-30s: %12.3f\n", headNames[i], headAmounts[i][0]);
}
printf(" Current expenditure : %12.3f\n", currentExpenditure);
printf(" Development and capital : %12.3f\n", developmentExpenditure);
printf(" TOTAL EXPENDITURE : %12.3f\n", totalExpenditure);
printf("\nC) Department subtotal (six displayed departments)\n");
printf(" Six-department subtotal : %12.3f\n", calculateDepartmentTotal(0));
printf(" Overall expenditure still uses all six official budget heads.\n");
printf("\nD) Saved category records (allocated amounts)\n");
printf(" Official records : %12.3f\n", calculateRecordTotal(0) - calculateUserTotal(0));
printf(" Records added by user : %12.3f\n", calculateUserTotal(0));
printf(" All saved records : %12.3f\n", calculateRecordTotal(0));
printf(" Note: these categories are parts of the budget. They are not\n");
printf(" extra money and must not be added to the totals above.\n");
}
void viewBudgetExpenditure(void) {
int i;
int shown = 0;
char label[LABEL_LEN];
printf("\nBUDGET EXPENDITURE (Rs. million)\n");
printf("BE = Budget Estimate, RE = Revised Estimate. The KMC documents give\n");
printf("RE (not audited actual spending) for 2025-26 and Actual for 2024-25.\n");
printf("\nA) Expenditure heads\n");
printLine('-', 72);
printf("%-30s %10s %10s %7s %11s\n", "Head", "BE 2025-26", "RE 2025-26", "RE/BE%", "Actual24-25");
printLine('-', 72);
for (i = 0; i < HEAD_COUNT; i++) {
printf("%-30s %10.3f %10.3f %7.1f %11.3f\n", headNames[i], headAmounts[i][2], headAmounts[i][1], calculatePercentage(headAmounts[i][1], headAmounts[i][2]), headAmounts[i][3]);
}
printLine('-', 72);
printf("%-30s %10.3f %10.3f %7.1f %11.3f\n", "TOTAL", calculateHeadTotal(2), calculateHeadTotal(1), calculatePercentage(calculateHeadTotal(1), calculateHeadTotal(2)), calculateHeadTotal(3));
printf("\nB) Departments (six selected rows, 2025-26)\n");
printLine('-', 72);
printf("%-30s %10s %10s %7s %11s\n", "Department", "BE 2025-26", "RE 2025-26", "RE/BE%", "RE - BE");
printLine('-', 72);
for (i = 0; i < DEPT_COUNT; i++) {
printf("%-30s %10.3f %10.3f %7.1f %11.3f\n", deptNames[i], deptAmounts[i][2], deptAmounts[i][1], calculatePercentage(deptAmounts[i][1], deptAmounts[i][2]), deptAmounts[i][1] - deptAmounts[i][2]);
}
printLine('-', 72);
printf("%-30s %10.3f %10.3f %7.1f %11.3f\n", "TOTAL", calculateDepartmentTotal(2), calculateDepartmentTotal(1), calculatePercentage(calculateDepartmentTotal(1), calculateDepartmentTotal(2)), calculateDepartmentTotal(1) - calculateDepartmentTotal(2));
printf("\nC) Saved categories with a spent amount (entered by the user)\n");
printLine('-', 72);
for (i = 0; i < recordCount; i++) {
if (recordAmounts[i][1] > 0.0) {
makeLabel(label, recordNames[i], recordDepts[i]);
printf("%3d. %s\n", i + 1, label);
printf(" Allocated: %.3f | Spent: %.3f | Spent: %.1f%%\n", recordAmounts[i][0], recordAmounts[i][1], calculatePercentage(recordAmounts[i][1], recordAmounts[i][0]));
shown++;
}
}
if (shown == 0) {
printf(" No spent amounts have been entered yet. Use option 10 to add one.\n");
}
}
void calculateRemainingBudget(void) {
double totalReceipts;
double totalExpenditure;
double remaining;
double groupAllocated = 0.0;
double groupSpent = 0.0;
int i;
int shown = 0;
char label[LABEL_LEN];
totalReceipts = currentReceipts + capitalReceipts;
totalExpenditure = calculateHeadTotal(0);
remaining = totalReceipts - totalExpenditure;
printf("\nREMAINING BUDGET (Rs. million)\n");
printLine('-', 60);
printf("A) Whole budget 2026-27\n");
printf(" Total receipts : %12.3f\n", totalReceipts);
printf(" Total expenditure : %12.3f\n", totalExpenditure);
printf(" Remaining (surplus) : %12.3f\n", remaining);
printf(" Surplus stated by KMC : %12.3f\n", officialSurplus);
if (absoluteValue(remaining - officialSurplus) < 0.0005) {
printf(" Result: the calculated surplus matches the KMC figure.\n");
} else {
printf(" Result: the figures do not match.\n");
}
printf("\nB) Saved categories with a spent amount\n");
printLine('-', 60);
for (i = 0; i < recordCount; i++) {
if (recordAmounts[i][1] > 0.0) {
makeLabel(label, recordNames[i], recordDepts[i]);
remaining = recordAmounts[i][0] - recordAmounts[i][1];
printf("%3d. %s\n", i + 1, label);
if (remaining >= 0.0) {
printf(" Allocated: %.3f | Spent: %.3f | Remaining: %.3f\n", recordAmounts[i][0], recordAmounts[i][1], remaining);
} else {
printf(" Allocated: %.3f | Spent: %.3f | OVERSPENT by %.3f\n", recordAmounts[i][0], recordAmounts[i][1], -remaining);
}
groupAllocated = groupAllocated + recordAmounts[i][0];
groupSpent = groupSpent + recordAmounts[i][1];
shown++;
}
}
if (shown == 0) {
printf(" No spent amounts have been entered yet. Use option 10 to add one.\n");
} else {
printf(" Total allocated: %.3f | Total spent: %.3f | Total remaining: %.3f\n", groupAllocated, groupSpent, groupAllocated - groupSpent);
}
}
void displayBudgetReport(void) {
double allocated[MAX_RECORDS];
double current[DEPT_COUNT];
double totalReceipts;
double totalExpenditure;
double deptTotal;
double deptAverage;
int i;
int highIndex;
int lowIndex;
int aboveCount = 0;
char label[LABEL_LEN];
totalReceipts = currentReceipts + capitalReceipts;
totalExpenditure = calculateHeadTotal(0);
printf("\n");
printLine('=', 66);
printf(" KMC BUDGET SUMMARY REPORT 2026-27 (Rs. million)\n");
printLine('=', 66);
printf("1. Overall position\n");
printf(" Total receipts : %12.3f\n", totalReceipts);
printf(" Total expenditure : %12.3f\n", totalExpenditure);
printf(" Surplus : %12.3f\n", totalReceipts - totalExpenditure);
printf("\n2. Expenditure heads (share of total expenditure)\n");
for (i = 0; i < HEAD_COUNT; i++) {
printf(" %-30s %11.3f %6.1f%%\n", headNames[i], headAmounts[i][0], calculatePercentage(headAmounts[i][0], totalExpenditure));
}
printf("\n3. Departments (six selected rows)\n");
deptTotal = calculateDepartmentTotal(0);
deptAverage = deptTotal / DEPT_COUNT;
for (i = 0; i < DEPT_COUNT; i++) {
current[i] = deptAmounts[i][0];
if (current[i] > deptAverage) {
aboveCount++;
}
}
findHighestAndLowest(current, DEPT_COUNT, &highIndex, &lowIndex);
printf(" Total : %12.3f\n", deptTotal);
printf(" Average : %12.3f\n", deptAverage);
printf(" Highest : %s (%.3f)\n", deptNames[highIndex], current[highIndex]);
printf(" Lowest : %s (%.3f)\n", deptNames[lowIndex], current[lowIndex]);
printf(" Above average : %d of %d departments\n", aboveCount, DEPT_COUNT);
printf("\n4. Saved categories\n");
for (i = 0; i < recordCount; i++) {
allocated[i] = recordAmounts[i][0];
}
findHighestAndLowest(allocated, recordCount, &highIndex, &lowIndex);
printf(" Number of records : %d\n", recordCount);
printf(" Total allocated : %12.3f\n", calculateRecordTotal(0));
printf(" Total spent : %12.3f (%.1f%% of allocated)\n", calculateRecordTotal(1), calculatePercentage(calculateRecordTotal(1), calculateRecordTotal(0)));
printf(" Total remaining : %12.3f\n", calculateRecordTotal(0) - calculateRecordTotal(1));
if (highIndex != -1) {
makeLabel(label, recordNames[highIndex], recordDepts[highIndex]);
printf(" Highest allocation : %s\n %.3f\n", label, allocated[highIndex]);
makeLabel(label, recordNames[lowIndex], recordDepts[lowIndex]);
printf(" Lowest allocation : %s\n %.3f\n", label, allocated[lowIndex]);
}
printf("\n5. Notes\n");
printf(" - Budget figures are KMC Budget Estimates for 2026-27.\n");
printf(" - RE is a revised estimate, not audited actual spending.\n");
printf(" - Spent amounts in saved categories are typed by the user.\n");
printLine('=', 66);
}
/* Add a user-defined budget category. */
void addNewCategory(void) {
char name[NAME_LEN];
char dept[DEPT_LEN];
char label[LABEL_LEN];
char newLower[NAME_LEN];
char oldLower[NAME_LEN];
double allocated;
double spent;
int i;
int duplicate = 0;
printf("\nADD NEW BUDGET CATEGORY\n");
if (recordCount >= MAX_RECORDS) {
printf("The record list is full (%d records).\n", MAX_RECORDS);
return;
}
printf("Category name: ");
if (!readLine(name, NAME_LEN) || isBlank(name)) {
printf("The name cannot be empty. Nothing was added.\n");
return;
}
underscoresToSpaces(name);
strcpy(newLower, name);
toLowerCase(newLower);
for (i = 0; i < recordCount; i++) {
strcpy(oldLower, recordNames[i]);
toLowerCase(oldLower);
if (strcmp(newLower, oldLower) == 0) {
duplicate = 1;
}
}
if (duplicate) {
printf("A category with this name already exists. Nothing was added.\n");
return;
}
printf("Department (press Enter for General): ");
if (!readLine(dept, DEPT_LEN) || isBlank(dept)) {
strcpy(dept, "General");
}
underscoresToSpaces(dept);
allocated = getAmountInput("Allocated amount (Rs. million): ");
if (allocated < 0.0) {
printf("Nothing was added.\n");
return;
}
spent = getAmountInput("Spent so far (Rs. million, enter 0 if none): ");
if (spent < 0.0) {
printf("Nothing was added.\n");
return;
}
strcpy(recordNames[recordCount], name);
strcpy(recordDepts[recordCount], dept);
strcpy(recordSource[recordCount], "USER");
recordAmounts[recordCount][0] = allocated;
recordAmounts[recordCount][1] = spent;
appendRecordToFile(recordCount);
recordCount++;
makeLabel(label, name, dept);
printf("Saved in %s as record %d: %s\n", DATA_FILE, recordCount, label);
}
/* Edit an existing record and save the change. */
void updateCategory(void) {
int number;
int choice;
int isUser;
double newValue;
char label[LABEL_LEN];
printf("\nUPDATE A SAVED CATEGORY\n");
displayRecordNames();
number = getNumberInRange("Enter the record number to update (0 to cancel): ", 0, recordCount);
if (number <= 0) {
printf("Update cancelled.\n");
return;
}
number = number - 1;
isUser = (strcmp(recordSource[number], "USER") == 0);
makeLabel(label, recordNames[number], recordDepts[number]);
printf("\nSelected: %s\n", label);
printf("Allocated: %.3f | Spent: %.3f\n", recordAmounts[number][0], recordAmounts[number][1]);
printf(" 1. Change the spent amount\n");
printf(" 2. Change the allocated amount (records added by the user only)\n");
printf(" 3. Cancel\n");
choice = getNumberInRange("Enter your choice (1-3): ", 1, 3);
if (choice == 1) {
newValue = getAmountInput("New spent amount (Rs. million): ");
if (newValue < 0.0) {
printf("Update cancelled.\n");
return;
}
recordAmounts[number][1] = newValue;
} else if (choice == 2) {
if (!isUser) {
printf("Official allocations cannot be changed.\n");
return;
}
newValue = getAmountInput("New allocated amount (Rs. million): ");
if (newValue < 0.0) {
printf("Update cancelled.\n");
return;
}
recordAmounts[number][0] = newValue;
} else {
printf("Update cancelled.\n");
return;
}
saveAllRecords();
printf("Record updated and saved in %s.\n", DATA_FILE);
printf("Allocated: %.3f | Spent: %.3f | Remaining: %.3f\n", recordAmounts[number][0], recordAmounts[number][1], recordAmounts[number][0] - recordAmounts[number][1]);
}
/* Program starts here. */
int main(void) {
int choice;
printf("Karachi Municipal Budget Tracker and Analyzer\n");
loadRecords();
do {
displayMenu();
choice = getMenuChoice();
switch (choice) {
case 1:
displayBudgetCategories();
pauseScreen();
break;
case 2:
searchBudget();
pauseScreen();
break;
case 3:
viewDepartmentWiseBudget();
pauseScreen();
break;
case 4:
calculateTotalBudget();
pauseScreen();
break;
case 5:
viewBudgetExpenditure();
pauseScreen();
break;
case 6:
calculateRemainingBudget();
pauseScreen();
break;
case 7:
displayBudgetReport();
pauseScreen();
break;
case 8:
printf("\nThank you. Your records are saved in %s.\n", DATA_FILE);
break;
case 9:
addNewCategory();
pauseScreen();
break;
case 10:
updateCategory();
pauseScreen();
break;
default:
printf("\nInvalid choice. Please enter a number from 1 to 10.\n");
}
} while (choice != 8);
return 0;
}