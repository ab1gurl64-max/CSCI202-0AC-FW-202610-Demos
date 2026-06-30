#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <map>
#include <limits>
#include "arrayStack.h"
#include "linkedStack.h"

// M03-a Lab come up with 5 binary numbers of test data for the converter
// also come up with 5 hex numbers
std::string inputBinaryNumber();
int convertBinaryToDecimal(StackADT<int> &);
void convertDecimalToBinary(StackADT<int> &, int);
std::string inputHexadecimalNumber();
int convertHexToDecimal(StackADT<int> &);
void resetStream();
const std::map<char, int> hexDigit = {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};
const std::regex space(R"(\s+)");

int main()
{
    ArrayStack<int> aStack;
    LinkedStack<int> lStack;
    char numberType;
    while (true)
    {
        aStack.initializeStack();
        lStack.initializeStack();
        std::cout << "Do you want to convert a (H)ex number, a (B)inary number or (D)ecimal to binary, enter q to quit? ";
        std::cin >> numberType;
        std::cout << std::endl;
        numberType = toupper(numberType);
        if (numberType == 'Q')
        {
            break;
        }
        while (numberType != 'H' && numberType != 'B' && numberType != 'D')
        {
            std::cout << "Please enter H or B." << std::endl;
            std::cout << "Do you want to convert a (H)ex number, a (B)inary number or (D)ecimal to binary, enter q to quit? ";
            std::cin >> numberType;
            std::cout << std::endl;
            numberType = toupper(numberType);
        }
        if (numberType == 'B')
        {
            std::string binNumber = inputBinaryNumber();

            for (int i = 0; i < binNumber.size(); i++)
            {
                aStack.push(binNumber[i] - '0');
            }
            std::cout << binNumber << " converted to decimal is " << convertBinaryToDecimal(aStack) << std::endl;
        }
        else if (numberType == 'H')
        {
            std::string hexNumber = inputHexadecimalNumber();

            for (int i = 0; i < hexNumber.size(); i++)
            {
                if (hexDigit.count(hexNumber[i]))
                {
                    lStack.push(hexDigit.at(hexNumber[i]));
                }
                else
                {
                    lStack.push(hexNumber[i] - '0');
                }
            }
            std::cout << hexNumber << " converted to decimal is " << convertHexToDecimal(lStack) << std::endl;
        }
        else
        {
            int number;
            std::cout << "Enter a positive number: ";
            std::cin >> number;
            while (!std::cin)
            {
                resetStream();
                std::cout << "You entered something that is not a number." << std::endl;
                std::cout << "Enter a positive number: ";
                std::cin >> number;
            }
            number = abs(number);
            aStack.initializeStack();
            convertDecimalToBinary(aStack, number);
            std::cout << number << " converted to binary is ";
            while (!aStack.isEmptyStack())
            {
                std::cout << aStack.pop();
            }
            std::cout << std::endl;
        }
    }
    return 0;
}

std::string inputBinaryNumber()
{
    std::regex binNum(R"([^10]+)");

    std::string binaryNumber;
    std::cout << "Enter a number in binary: ";
    std::getline(std::cin >> std::ws, binaryNumber);
    binaryNumber = std::regex_replace(binaryNumber, space, "");
    std::transform(binaryNumber.begin(), binaryNumber.end(), binaryNumber.begin(), ::toupper);

    while (std::regex_search(binaryNumber, binNum))
    {
        std::cout << "Please enter only 1s and 0s." << std::endl;
        std::cout << "Enter a number in binary: ";
        std::getline(std::cin >> std::ws, binaryNumber);
        binaryNumber = std::regex_replace(binaryNumber, space, "");
    }
    return binaryNumber;
}

int convertBinaryToDecimal(StackADT<int> &binNum)
{
    int digit = 0;
    int position = 0;
    int converted = 0;
    while (!binNum.isEmptyStack())
    {
        digit = binNum.pop();
        converted += pow(2, position) * digit;
        position++;
    }
    return converted;
}

void convertDecimalToBinary(StackADT<int> &result, int number)
{
    while (number != 0)
    {
        result.push(number % 2);
        number /= 2; // number = number /2;
    }
}

std::string inputHexadecimalNumber()
{
    std::regex hexNum(R"([^\dABCDEFabcdef]+)");
    std::regex space(R"(\s+)");
    std::string hexNumber;
    std::cout << "Enter a number in hexadecimal: ";
    std::getline(std::cin >> std::ws, hexNumber);
    hexNumber = std::regex_replace(hexNumber, space, "");
    std::transform(hexNumber.begin(), hexNumber.end(), hexNumber.begin(), ::toupper);

    while (std::regex_search(hexNumber, hexNum))
    {
        std::cout << "Please enter only hexadecimal digits (0-9 and a-f)." << std::endl;
        std::cout << "Enter a number in hexadecimal: ";
        std::getline(std::cin >> std::ws, hexNumber);
        hexNumber = std::regex_replace(hexNumber, space, "");
    }
    return hexNumber;
}

int convertHexToDecimal(StackADT<int> &hex)
{
    int digit = 0;
    int position = 0;
    int converted = 0;
    while (!hex.isEmptyStack())
    {
        digit = hex.pop();
        converted += pow(16, position) * (digit);
        position++;
    }
    return converted;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
