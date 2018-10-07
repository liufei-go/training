#include "datetime.h"

#include <iostream>

namespace {

   enum {
       JAN = 1,
       FEB = 2,
       MAR = 3,
       APR = 4,
       MAY = 5,
       JUN = 6,
       JUL = 7,
       AUG = 8,
       SEP = 9,
       OCT = 10,
       NOV = 11,
       DEC = 12,

       DAYS_NOT_IN_LEAP_YEAR = 365,
       DAYS_IN_LEAP_YEAR = 366
   };
   
   const int DAYS_IN_EACH_MONTH[] =
   {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31
   };

   bool is_leap_year(const int year)
   {
        if (year % 4 == 0)
        {
            if (year % 100 == 0)
            {
                if (year % 400 == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
   }

   bool is_month_30(const int month)
   {
       if (month == APR ||
           month == JUN ||
           month == SEP ||
           month == NOV)
       {
           return true;
       }
       else
       {
           return false;
       }
   }

   bool is_valid_date(const int month, const int day, const int year)
   {
       if (month < JAN  || month > DEC)
       {
           return false;
       }

       if (day < 1 || day > 31)
       {
           return false;
       }

       if (year < 0)
       {
           return false;
       }

       if (is_month_30(month))
       {
           if (day > 30)
           {
               return false;
           }
       }

       if (month == FEB)
       {
           if (is_leap_year(year))
           {
               if (day > 29)
               {
                   return false;
               }
           }
           else
           {
               if (day > 28)
               {
                   return false;
               }
           }
       }

       return true;
   }
   
   void invalid_date_log_error(const int month, const int day, const int year)
   {
        std::cerr << "Invalid date: month " << month 
                   << " day " << day 
                   << " year " << year << std::endl;
   }

} 
// End of anonymous namespace


Date::Date(const int month, const int day, const int year)
{
    if (is_valid_date(month, day, year))
    {
        m_month = month;
        m_day = day;
        m_year = year;

        m_serialDate = date_to_number(*this);
    }
    else
    {
        invalid_date_log_error(month, day, year);
        reset();
    }
}

Date::Date(const int date_yyyymmdd)
{
    if (date_yyyymmdd <= 10000000)
    {
        reset();
        return;
    }

    int year = date_yyyymmdd % 10000;
    int month = (date_yyyymmdd - year * 10000) % 100;
    int day = date_yyyymmdd - year * 10000 - month * 100;

    set_date(month, day, year);
}

Date::Date(const Date& date)
{
    m_month = date.month();
    m_day = date.day();
    m_year = date.year();

    m_serialDate = date_to_number(*this);
}

Date Date::operator=(const Date& date)
{
    m_month = date.month();
    m_day = date.day();
    m_year = date.year();

    m_serialDate = date_to_number(*this);
    return *this;
}

Date Date::operator+(const int n)
{
    Date date;
    if (!this->is_valid())
    {
        std::cerr << "Input date is invalid" << std::endl;
        return date;
    }

    int& num = this->m_serialDate;
    num += n;
    return number_to_date(num);
}

Date Date::operator-(const int n)
{
    Date date;
    if (!this->is_valid())
    {
        std::cerr << "Input date is invalid" << std::endl;
        return date;
    }

    int& num = this->m_serialDate;
    num -= n;
    return number_to_date(num);
}

Date& Date::operator++()
{
    *this = number_to_date(this->m_serialDate + 1);
    return *this;
}

Date Date::operator++(int)
{
    Date temp(*this);
    operator++();
    return temp;
}
    
Date& Date::operator--()
{
    *this = number_to_date(this->m_serialDate - 1);
    return *this;
}

Date Date::operator--(int)
{
    Date temp(*this);
    operator--();
    return temp;
}

std::ostream& operator<< (std::ostream& os, const Date& date)
{
    os << date.month() << "/" << date.day() << "/" << date.year();
    return os;
}

bool operator<(const Date& date1, const Date& date2)
{
    return (date1.date_to_yyyymmdd() < date2.date_to_yyyymmdd());
}

bool operator>(const Date& date1, const Date& date2)
{
    return (date1.date_to_yyyymmdd() > date2.date_to_yyyymmdd());
}

bool operator==(const Date& date1, const Date& date2)
{
    return (date1.date_to_yyyymmdd() == date2.date_to_yyyymmdd());
}

void Date::set_date(const int month, const int day, const int year)
{
    if (is_valid_date(month, day, year))
    {
        m_month = month;
        m_day = day;
        m_year = year;

        m_serialDate = date_to_number(*this);
    }
    else
    {
        invalid_date_log_error(month, day, year);
        reset();
    }
}

bool Date::is_valid() const
{
    return is_valid_date(m_month, m_day, m_year);
}

int Date::date_to_yyyymmdd() const
{
    int date_yyyymmdd = 0;

    if (!is_valid())
    {
        return 0;
    }

    date_yyyymmdd += m_year * 10000;
    date_yyyymmdd += m_month * 100;
    date_yyyymmdd += m_day;

    return date_yyyymmdd;
}

void Date::reset()
{
    m_month = 0;
    m_day = 0;
    m_year = 0;
    m_serialDate = 0;
}

int Date::date_to_number(const Date& date)
{
    int m = date.month();
    int d = date.day();
    int y = date.year() - 1;

    int num = 0;
    num += DAYS_NOT_IN_LEAP_YEAR * y + y /4 - y / 100 + y / 400;
    for (size_t i = 0; i < m - 1; ++i)
    {
        num += DAYS_IN_EACH_MONTH[i];
    }
    num += d;
    
    if (is_leap_year(y + 1) && m > FEB)
    {
        ++num;
    }

    return num;
}

Date Date::number_to_date(const int number)
{
    Date date;

    int year = number / DAYS_NOT_IN_LEAP_YEAR - 1;
    int remainder = number - (365 * year + year / 4 - year / 100 + year / 400);
    if (remainder < 0)
    {
        --year;
        remainder = number - (365 * year + year / 4 - year / 100 + year / 400);
    }
    
    ++year;

    int month = 0;
    int day = 0;
    int num = 0;
    for (size_t i = 0; i < DEC; ++i)
    {
        int increment = DAYS_IN_EACH_MONTH[i];
        if (is_leap_year(year))
        {
            if (i == FEB - 1)
            {
                ++increment;
            }
        }
        num += increment;
        if (num > remainder)
        {
            month = i + 1;
            day = remainder - (num - increment);
            break;
        }
    }

    date.set_date(month, day, year);
    return date;
}

