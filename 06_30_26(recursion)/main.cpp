#include <iostream>
#include <string>
#include <limits>

int inputInt(std::string prompt, std::string err, int low, int high);
void resetStream();
int factorial(int n);

int main()
{
    factorial(7);
    return 0;
}

int inputInt(std::string prompt, std::string err, int low, int high)
{
    int num;
    std::cout << prompt;
    std::cin >> num;
    std::cout << std::endl;
    if (std::cin && num >= low && num <= high)
    {
        return num;
    }
    if (!std::cin) //|| num < low || num > high
    {

        resetStream();
    }
    std::cout << err << std::endl;
    return inputInt(prompt, err, low, high);
}

int factorial(int n)
{
    n = abs(n);
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}