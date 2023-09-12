
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class lotteryNumbers
{
private:
    int* arr;
    int maxSize;
    int nElems;
public:
    lotteryNumbers(int max);
    lotteryNumbers(int max, char play);
    ~lotteryNumbers();
    void setNum() const;
    void generateNum() const;
    void sort() const;
    void print() const;
    void duplicate() const;
    bool operator==(const lotteryNumbers& otherNumbers) const;
};
// Takes 5 distinct numbers from the player
void lotteryNumbers::setNum() const
{
    cout << "Enter five distinct integers between 1 and 40 (inclusive):" << endl;
    for (int i = 0; i < maxSize; i++)
    {
        if (i == 0)
        {
            cout << "Enter the first number: ";
            cin >> arr[i];
        }
        else
        {
            cout << "Enter the next number: ";
            cin >> arr[i];
        }
        
        for (int j = 0; j < i; j++)
        {
            while (arr[j] == arr[i])
            {
                cout << "Enter a non-duplicate number: ";
                cin >> arr[i];
            }
        }
        while (arr[i] < 1 || arr[i] > 40)
        {
            cout << "Number must be between 1 and 40. Select another." << endl;
            cin >> arr[i];
            for (int j = 0; j < i; j++)
            {
                while (arr[j] == arr[i])
                {
                    cout << "Enter a non-duplicate number: ";
                    cin >> arr[i];
                }
            }
        }
       
    }
}
// Generates random numbers
void lotteryNumbers::generateNum() const
{
    srand(time(0));
    for (int i = 0; i < maxSize; i++)
    {
        arr[i] = rand() % (40) + 1;
        //nElems++;
    }
}
// Constructor
lotteryNumbers::lotteryNumbers(int max)
{
    maxSize = max;
    //nElems = 0;
    arr = new int[maxSize];
    generateNum();
    sort();
    duplicate();
    
}
// Overloaded Constructor
lotteryNumbers::lotteryNumbers(int max, char play)
{
    maxSize = max;
    //nElems = 0;
    arr = new int[maxSize];
    if (play == 'y' || play == 'Y')
    {
        setNum();
        sort();
        print();
    }
}
// Destructor
lotteryNumbers::~lotteryNumbers()
{
    delete[] arr;
}
// Insertion sort
void lotteryNumbers::sort() const
{
    // insertion sort
    for (int i = 1; i < maxSize; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// Searches for duplicate numbers and replaces them
void lotteryNumbers::duplicate() const
{
    // checks for duplicates
    for (int i = 0; i < maxSize; i++)
    {

        if (arr[i] == arr[i + 1])
        {
            arr[i + 1] = rand() % (40) + 1;
        }
    }
}
// Print function
void lotteryNumbers::print() const
{
    for (int k = 0; k < maxSize; k++)
    {
        cout << arr[k] << " ";
    }
    cout << endl;
}
// Overloads the == operator to allow comparison of user defined variables
bool lotteryNumbers::operator==(const lotteryNumbers& otherNumbers) const
{
    for (int i = 0; i < maxSize; i++)
    {
        if (arr[i] != otherNumbers.arr[i])
        {
            return false;
        }
    }
    return true;
}
int main()
{    
    
    const int MAX = 5;
    char play = 'y';
    cout << "Play lotto (Y/y)/(N/n): ";
    cin >> play;

    while (play == 'y' || play == 'Y')
    {
        lotteryNumbers lotNum(MAX);
        //lotNum.print();
        lotteryNumbers playerNum(MAX, play);
        if (lotNum == playerNum)
        {
            cout << "You win!" << endl;
            cout << "The correct numbers are: ";
            lotNum.print();
        }
        else
        {
            cout << "You lose!" << endl;
            cout << "The correct numbers are: ";
            lotNum.print();
        }
        cout << "Play another (Y/y)/(N/n): ";
        cin >> play;
    }
    return 0;
}

