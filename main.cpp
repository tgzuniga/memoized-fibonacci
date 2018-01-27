/*
* Fibonacci:
* This program finds the nth Fibonacci number using a recursive function with
* memoization and a naive recursive funtion. It also outputs the runtime for
* both functions along with the number of times each function recurses.
*
* Created by Theodore Zuniga on 10/12/17.
* Copyright (c) 2017 Theodore Zuniga. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

//Global Variables
int const SIZE = 44;
vector<long> mem(SIZE, 0);

//Function declarations
long naiveFib(int, int&);
long memoFib(int, int&);

//Main
int main()
{
    int num = 0;          //Users choice for which Fibonacci number to find.
    char choice = 'Y';    //Menu choice for whether or not to cotinue.
    bool notValid = true; //Flag for "choice" input validity.
    bool exit = false;    //Flag for "choice" equal to N||n.
    long naiveNum = 0;    //Result from naiveFib().
    long memoNum = 0;     //Result from memoFib().
    int naiveCalls = 0;   //Number of times naive function is called.
    int memoCalls = 0;    //Number of times memoized function is called.

    //Main loop
    while(!exit)
    {
        cout << "Enter a integer from 0 to " << SIZE << ": ";
        if((cin >> num)&&(num <= SIZE))
        {
            //Reset number of calls
            naiveCalls = 0;
            memoCalls = 0;

            //Memoized recursive function results
            cout << "The " << num << " Fibonacci number according to a "
                 << "recursive function with memoization is: ";

            auto t1 = chrono::high_resolution_clock::now();
            memoNum = memoFib(num, memoCalls);
            auto t2 = chrono::high_resolution_clock::now();
            auto memoRunT = chrono::duration_cast<chrono::microseconds>
                            ( t2 - t1 ).count();

            cout << memoNum << endl << "The Memoized runtime was " << memoRunT
                 << " microsecond(s), and the function was called "
                 << memoCalls << " time(s)." << endl << endl;

            //Naive recursive function results
            cout << "The " << num << " Fibonacci number according to a naive "
                 << "recursive function is: ";

            auto t3 = chrono::high_resolution_clock::now();
            naiveNum = naiveFib(num, naiveCalls);
            auto t4 = chrono::high_resolution_clock::now();
            auto naiveRunT = chrono::duration_cast<chrono::microseconds>
                             ( t4 - t3 ).count();

            cout << naiveNum << endl << "The Naive runtime was " << naiveRunT
                 << " microsecond(s), and the function was called "
                 << naiveCalls << " time(s)."<< endl << endl;

            //Reset notValid and present continuation menu
            notValid = true;
            while(notValid)
            {
                cout << "Would you like to find another fibonacci number? "
                     << "Enter Y||y or N||n: ";
                if(!(cin >> choice)||((choice != 'n')&&(choice != 'N')&&
                                      (choice != 'y')&&(choice != 'Y')))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input was not a valid character Y||y||N||n."
                         << endl << endl;
                }
                else
                {
                    notValid = false;
                    if((choice == 'N')||(choice == 'n'))
                        exit = true;
                }
            }
            cout << endl << endl;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input was not a valid integer from 0 to " << SIZE << "."
                 << endl << endl;
        }
    }

    return 0;
}

/*
* This recursive function finds the nth Fibonacci number without any
* optimizations.
*/
long naiveFib(int n, int& t)
{
    long f = 0; //Fibonacci number to be returned

    //Count times naiveFib() is called.
    t++;

    //Base case
    if(n <= 2)
        return 1;
    else
    {
        //Recurse
        f = naiveFib(n-1, t) + naiveFib(n-2, t);
        return f;
    }
}

/*
* This recursive function uses memoization to remember previously found
* Fibonacci numbers. This speeds up the running time of the algorithm from
* exponential to linear.
*/
long memoFib(int n, int& t)
{
    long f = 0; //Fibonacci number to be returned

    //Count times memoFib() is called.
    t++;

    //Check if memoFib(n) already found.
    if(mem.at(n-1) != 0)
        return mem[n-1];
    //Base case
    if(n <= 2)
        return 1;
    else
    {
        //Recurse
        f = memoFib(n-1, t)+memoFib(n-2, t);

        //Save memoFib(n) and return.
        mem[n-1] = f;
        return f;
    }
}


