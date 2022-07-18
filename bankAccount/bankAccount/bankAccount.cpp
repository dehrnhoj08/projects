
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class bankAccount
{
    // private variables that normally defines a bank account
private:
    string name;
    int accountNumber;
    string accountType;
    double balance;
    double interestRate;
    // public methods to modify the private variables as needed
public:
    bankAccount();
    void setInformation(string n, string aT, double b, double i); // aT as in accountType
    void print();
    void setAccountNumber(int aN); // aN as in accountNumber
    int getAccountNumber();
    void bankDeposit(double bC);
    void bankWithdraw(int bC);  // bC as in balanceChange
};

// Constructor. This will initialize the private variables. I didn't find much use of it in this program
// besides keeping the IDE from throwing out warnings about uninitialized variables
bankAccount::bankAccount()
{
    name = "";
    accountType = "";
    balance = 0.0;
    interestRate = 0.0;
}

// I consolidated the four setters that I otherwise would need separately
// I left out the account number setter since it's a static member
void bankAccount::setInformation(string n, string aT, double b, double i)
{
    name = n;
    accountType = aT;
    balance = b;
    interestRate = i;
}
// static member for setting account numbers
// a random number generator might also work
void bankAccount::setAccountNumber(int index)
{
    accountNumber = 1100 + (index * 100);
}
// getter for the account number used to search for an existing ID
int bankAccount::getAccountNumber()
{
    return accountNumber;
}
// print function, basically prints all of the customer information
void bankAccount::print()
{
    cout << fixed << setprecision(2) << endl;
    cout << "Account Holder Name: " << name << endl;
    cout << "Account Type: " << accountType << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Balance: " << "$" << balance << endl;
    cout << "Interest Rate: " << interestRate << "%" << endl;
    cout << "*****************************" << endl;
}
// withdraw method
void bankAccount::bankWithdraw(int bC)
{
    balance = balance - bC;
}
// deposit method
void bankAccount::bankDeposit(double bC)
{
    balance = balance + bC;
}

// main
int main()
{
    const int MAX_SIZE = 10;    // max size of the object array
    bankAccount bankArray[MAX_SIZE];    // object array
    
    // variables that need to be passed into the object methods
    string customerName;
    string accountT;
    double balanceAmount;
    double interest;
    
    // variables to keep track of user choice inputs
    int choice = 0;
    int choice2 = 0;
    
    double balanceChange = 0.0; // used to modify the balance whether to deposit or withdraw
    int accountNumber = 0;  // used to check the object array if an existing ID is initialized
    bool accNumCheck = true;    // used to indicate if an ID is present in the object array
    
    int j = 0;  // this is the counter that will keep track of the amount of customers in the object array (bankArray)
    while (choice != 9) 
    {
        // First choice prompt
        cout << endl;
        cout << "1:Enter 1 to add a new customer." << endl;
        cout << "2:Enter 2 for an existing customer." << endl;
        cout << "3:Enter 3 to print customers data." << endl;
        cout << "9:Enter 9 to exit the program" << endl;
        cin >> choice;
        

        // Choice 1
        if (choice == 1)
        {
            if (j < MAX_SIZE)
            {
                // User input
                cout << endl;
                cout << "Enter customer's name: ";
                cin.ignore();
                getline(cin, customerName); // uses getline so that first name and last name are together in one string variable
                cout << "Enter account type (checking/savings): ";
                cin >> accountT;            // account type
                cout << "Enter amount to be deposited to open account: ";
                cin >> balanceAmount;
                cout << "Enter interest rate (as a percent): ";
                cin >> interest;
                cout << endl;
                bankArray[j].setInformation(customerName, accountT, balanceAmount, interest);
                bankArray[j].setAccountNumber(j);
                j++;
                
                // I'm commenting this out because I feel like it is an unnecessary while loop
                /*while (choice == 1)
                {
                    bankArray[j].setInformation(customerName, accountT, balanceAmount, interest);
                    bankArray[j].setAccountNumber(j);
                    j++;
                    break;
                }*/
            }
            else
                cout << "Cannot enter anymore customers." << endl;  // this statement checks if the max amount of customers is reached
        }
        
        // Choice 2
        else if (choice == 2)
        {
            cout << endl;
            cout << "Enter account number: ";
            cin >> accountNumber;
            
            // checks the entire object array for any match. i < j could also work since j keeps up
            // with the number of customers in the array, instead of searching the entire array size every time
            for (int i = 0; i < MAX_SIZE; i++)
            {
                // if a match is found, breaks out of the loop
                if (accountNumber == bankArray[i].getAccountNumber())
                {
                    accNumCheck = true;
                    break;
                }
                else
                    accNumCheck = false;
            }
 
            if (accNumCheck == false)
            {
                cout << "Invalid customer id." << endl;
            }

            else if (accNumCheck == true)
            {
                choice2 = 0;    // resets the choice2 to 0, everytime this part is exited, choice2 retains the value 9
                                // in cases that other customers need to withdraw of deposit, this part is skipped if choice2 value is
                                // not reset to 0
                while (choice2 != 9)
                {
                    cout << "\n1:Enter 1 to make a deposit." << endl;
                    cout << "2:Enter 2 to withdraw." << endl;
                    cout << "3:Enter 3 to check balance." << endl;
                    cout << "4:Enter 9 to exit." << endl;
                    cin >> choice2;

                    if (choice2 == 1)
                    {
                        cout << "\nEnter the amout to be deposited: ";
                        cin >> balanceChange;

                        for (int i = 0; i < j; i++)
                        {   
                            // this for loop uses the account number to modify the balance of the correct object in the array
                            if (accountNumber == bankArray[i].getAccountNumber())
                                bankArray[i].bankDeposit(balanceChange);
                        }
                        
                    }
                    else if (choice2 == 2)
                    {
                        cout << "Enter the amount to be withdrawn: ";
                        cin >> balanceChange;
                        for (int i = 0; i < j; i++)
                        {
                            // same method with the deposit
                            if (accountNumber == bankArray[i].getAccountNumber())
                                bankArray[i].bankWithdraw(balanceChange);
                        }
                    }
                    else if (choice2 == 3)
                    {
                        for (int i = 0; i < j; i++)
                        {
                            // same method with the other two, but only prints the contents of the object in question, not the entire object array
                            if (accountNumber == bankArray[i].getAccountNumber())
                            {
                                bankArray[i].print();
                                cout << endl;
                            }
                                
                        }
                    }
                }
            }
        }

        // Choice 3
        else if (choice == 3)
        {
            // this for loop prints the entire object array and their contents (name, type, balance, etc.)
            for (int i = 0; i < j; i++)
            {
                bankArray[i].print();
                cout << endl;
            }
        }

        // Terminates program if anything else is given
        else
            return 0;
    }
    
    
}
