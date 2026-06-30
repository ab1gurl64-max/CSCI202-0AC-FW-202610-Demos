#include "date.h"

date::date(int month, int day, int year)
{
    setMonth(month);
    setYear(year);
    setDay(day);
}

int date::getMonth()
{
    return month;
}

int date::getDay()
{
    return day;
}

int date::getYear()
{
    return year;
}

bool date::isLeapYear()
{
    /*  1. If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.
        2. If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.
        3. If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
        4. The year is a leap year (it has 366 days).
        5. The year is not a leap year (it has 365 days). */
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
            if (year % 400 == 0)
                return true;
            else
                return false;
        else
            return true;
    }
    return false;
}

void date::setMonth(int month)
{
    if (month < 1 || month > 12)
        throw std::invalid_argument("The month must be between 1 and 12.");
    else
        this->month = month;
}

void date::setDay(int day)
{
    if (day < 1 || day > 31)
        throw std::invalid_argument("The day must be between 1 and 31.");
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            throw std::invalid_argument("The day must be between 1 and 30.");
        else
            this->day = day;
    }
    else if (month == 2)
    {
        if (day > 29)
            throw std::invalid_argument("The day must be between 1 and 29.");
        else if (!isLeapYear() && day > 28)
            throw std::invalid_argument("The day must be between 1 and 28.");
        else
            this->day = day;
    }
    else
        this->day = day;
}

void date::setYear(int year)
{
    if (year < 0)
        throw std::invalid_argument("The year must be greater than 0.");
    this->year = year;
}

date date::operator+(int daysToAdd)
{
    int mod;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        mod = 30;
    else if (month == 2)
        if (isLeapYear())
            mod = 29;
        else
            mod = 28;
    else
        mod = 31;
    int daysToEnd = mod - day;
    if (daysToEnd < daysToAdd)
    {
        day = (day + (daysToEnd + 1)) % mod;
        if (month != 12)
            month += 1;
        else
        {
            month = 1;
            year += 1;
        }
        if (daysToAdd - (daysToEnd + 1) > 0)
        {
            return *this + (daysToAdd - (daysToEnd + 1));
        }
    }
    else
    {
        day += daysToAdd;
    }

    return *this;
}

date date::operator-(int daysToSub)
{
    int mod;
    if (month == 5 || month == 7 || month == 10 || month == 12)
        mod = 30;
    else if (month == 3)
        if (isLeapYear())
            mod = 29;
        else
            mod = 28;
    else
        mod = 31;

    // day = day - daysToSub;
    if (day - daysToSub <= 0)
    {
        daysToSub -= day;
        // day = day + mod;
        day = mod;
        if (month != 1)
            month--;
        else
        {
            month = 12;
            year--;
        }

        return *this - daysToSub;
    }
    else
    {
        day = day - daysToSub;
    }
    return *this;
}

bool date::operator<(const date &otherDate) const
{
    bool less = false;
    if (year < otherDate.year)
        less = true;
    else if (year == otherDate.year)
        if (month < otherDate.month)
            less = true;
        else if (month == otherDate.month)
            if (day < otherDate.day)
                less = true;
    return less;
}

bool date::operator<=(const date &otherDate) const
{

    return *this < otherDate || *this == otherDate;
}

bool date::operator>=(const date &otherDate) const
{
    return *this > otherDate || *this == otherDate;
}

bool date::operator>(const date &otherDate) const
{
    bool more = false;
    if (year > otherDate.year)
        more = true;
    else if (year == otherDate.year)
        if (month > otherDate.month)
            more = true;
        else if (month == otherDate.month)
            if (day > otherDate.day)
                more = true;
    return more;
}

bool date::operator==(const date &otherDate) const
{
    return this->month == otherDate.month && this->day == otherDate.day && this->year == otherDate.year;
}

bool date::operator!=(const date &otherDate) const
{
    return !(*this == otherDate);
}

date date::operator++()
{

    return *this + 1;
}

date date::operator++(int x)
{
    date temp(*this);
    *this = *this + 1;
    return temp;
}

date date::operator--()
{
    return *this - 1;
}

date date::operator--(int x)
{
    date temp(*this);
    *this = *this - 1;
    return temp;
}

date operator+(int daysToAdd, date &addToDate)
{
    return addToDate + daysToAdd;
}

date operator-(int daysToSub, date &subFromDate)
{
    return subFromDate - daysToSub;
}

std::istream &operator>>(std::istream &in, date &dateToFill)
{
    int m, d, y;
    in >> m >> d >> y;
    dateToFill.setMonth(m);
    dateToFill.setYear(y);
    dateToFill.setDay(d);
    return in;
}

std::ostream &operator<<(std::ostream &out, date &dateToPrint)
{
    out << std::setfill('0');
    out << std::setw(4) << dateToPrint.year << "-" << std::setw(2) << dateToPrint.month << "-" << std::setw(2) << dateToPrint.day;
    out << std::setfill(' ');
    return out;
}