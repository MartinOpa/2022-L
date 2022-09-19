#include <iostream>

using namespace std;

int findPrimes(int n, int* numbers)
{
    for ( int i = 2; i * i <= n; i++)
    {
        if ( numbers[i] != 0 )
        {
            for ( int j = i * i; j <= n; j += i )
                {
                    numbers[j] = 0;
                }
        }
    }

    return 0;
}

int printPrimes(int n, int* numbers)
{
    for ( int i = 0; i <= n; i++)
    {
        if (numbers[i] != 0)
        {
        cout << numbers[i] << " ";
        }
    }
    
    cout << "\n";

    return 0;
}

int main()
{
    int n;
    cin >> n;
    int numbers[n];
    memset ( numbers, 0, sizeof(int));
    
    for ( int i = 0; i <= n; i++)
    {
        numbers[i] = i;
    }
    
    findPrimes(n, numbers);
    printPrimes(n, numbers);
    
    return 0;
}