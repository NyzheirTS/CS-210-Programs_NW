//Nyzheir Warner
//03/28/2023

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;
char c;
double intVest, monDep,interestEarned, annInt, numYears;



string nCharString(size_t n, char c) { // function that takes in prameters n, c and outsputs a string of char c for length n.

    string chrstr = "";
    chrstr.append(n, c);
    return chrstr;
}

void menu() {
    cout << nCharString(34, '*') << endl;
    cout << nCharString(11, '*') << " Data Input " << nCharString(11, '*') << endl;
    cout << "Initial Investment Amount:  $";
    cin >> intVest;
    cout << "Monthly Deposit:  $";
    cin >> monDep;
    cout << "Annual Interest:  %";
    cin >> annInt;
    cout << "Number of Years:  ";
    cin >> numYears;
    system("pause");
}

void printDetails(int numYears, double yearEndBalance, double interestEarned) {

    stringstream ss;
    stringstream rr;
    ss << fixed << setprecision(2) << yearEndBalance;
    rr << fixed << setprecision(2) << interestEarned;   //convert the double to string retaining the setprecision to work correctly with setw() and "$"

    string n = ss.str();
    string d = rr.str();

    //cout << setw(2) << numYears << setw(25) << "$" <<  yearEndBalance << setw(25) << "$" <<  interestEarned  << endl;  //not working correctly 

    cout << "|" << setw(5) << numYears << setw(22) << ("$" + n) << setw(25) << ("$" + d) << "     |" << endl;
}

double calculateBalanceWithoutMonthlyDeposit(double initialInvestment, double interestRate, int numberOfYears) {

    double numInterest = interestRate / 100;
    double yearEndBalance = 0.00, intEarned;

    cout << nCharString(59, '=') << endl;
    cout << "#       Balance and Interest Without Monthly Deposits     #" << endl;
    cout << nCharString(59, '=') << endl;
    cout << "# -Years-" << "        " << " -End Balance-   " << "        " << "-End Interest-  #" << endl;
    cout << nCharString(59, '~') << endl;

    if (numberOfYears == 0) {
        printDetails(0, initialInvestment, 0);
    }
    else {
        double n = 0.00;
        for (int i = 1; i <= numberOfYears; ++i) {
            if (i < 2) {
                yearEndBalance = initialInvestment * pow((1 + numInterest / 12), (12 * i));
                intEarned = (yearEndBalance - n) - initialInvestment;
                printDetails(i, yearEndBalance, intEarned);
                n = intEarned;
            }                                                                           //calculate monthly interest with monthly installments
            else {
                yearEndBalance = initialInvestment * pow((1 + numInterest / 12), (12 * i));
                intEarned = (yearEndBalance - n) - initialInvestment;
                printDetails(i, yearEndBalance, intEarned);
                n = yearEndBalance - initialInvestment;
            }
        }
    }
    cout << nCharString(59, '-') << endl;
    return yearEndBalance;
}

double balanceWithMonthlyDeposit(double initialInvestment, double monthlyDeposit, double interestRate, int numberOfYears) {
        double endingBalance = initialInvestment, interest = interestRate / 100, intEarned, finalInterest, yearDep = monthlyDeposit * 12;
        int months = numberOfYears * 12;
        cout << nCharString(59, '=') << endl;
        cout << "#       Balance and Interest With Monthly Deposits        #"<< endl;
        cout << nCharString(59, '=') << endl;
        cout << "# -Years-" << "        " << " -End Balance-   " << "        " << "-End Interest-  #" << endl;
        cout << nCharString(59, '~') << endl;
        if (numberOfYears == 0) {
            printDetails(0, initialInvestment, 0);
        }
        else { 
            for (int i = 1; i <= months; i++) {
                intEarned = endingBalance * (interest / 12);
                endingBalance += intEarned;
                endingBalance += monthlyDeposit;
                                                        //function that calculates monthly interest with monthly deposits 
                if (i % 12 == 0) {
                    finalInterest = endingBalance - initialInvestment - yearDep;
                    printDetails(i / 12, endingBalance, finalInterest);
                    initialInvestment = endingBalance;
                }
            }
        }
        cout << nCharString(59, '-') << endl;

        return endingBalance;
}


int main(){
    char pick;
    
    do {  
        menu();
        cout << endl << endl;

        calculateBalanceWithoutMonthlyDeposit(intVest, annInt, numYears);
        cout << endl;
        balanceWithMonthlyDeposit(intVest, monDep, annInt, numYears);

        cout << endl << "Would You like to go again. (Y/N)" << endl;
        cin >> pick;
        pick = toupper(pick);
        cout << endl;

    } while (pick != 'N');

    cout << endl << "You Have Exited the Program!" << endl;

    return 0;
}
