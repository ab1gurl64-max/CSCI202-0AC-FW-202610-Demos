#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
class date
{
public:
    date(int month, int day, int year);
    int getMonth();
    int getDay();
    int getYear();
    bool isLeapYear();
    void setMonth(int month);
    void setDay(int day);
    void setYear(int year);
    date operator+(int daysToAdd);
    friend date operator+(int daysToAdd, date &addToDate);
    date operator-(int daysToSub);
    friend date operator-(int daysToSub, date &subFromDate);
    bool operator<(const date &otherDate) const;
    bool operator<=(const date &otherDate) const;
    bool operator>=(const date &otherDate) const;
    bool operator>(const date &otherDate) const;
    bool operator==(const date &otherDate) const;
    bool operator!=(const date &otherDate) const;
    friend std::istream &operator>>(std::istream &in, date &dateToFill);
    friend std::ostream &operator<<(std::ostream &out, date &dateToPrint);
    date operator++();
    date operator++(int);
    date operator--();
    date operator--(int);

private:
    int month;
    int day;
    int year;
};

#endif