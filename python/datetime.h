#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
/*
enum
{
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
    DEC = 12
};
*/

class Date
{
public:
    Date():m_day(0), m_month(0), m_year(0), m_serialDate(0) {}
    Date(const int month, const int day, const int year);
    Date(const int date_yyyymmdd);
    Date(const Date& date);
    Date operator=(const Date& date);
    Date operator+(const int n);
    Date operator-(const int n);
    Date& operator++(); // ++date
    Date operator++(int); // date++
    Date& operator--();
    Date operator--(int);
    friend std::ostream& operator<< (std::ostream& os, const Date& date);
    friend bool operator<(const Date& date1, const Date& date2);
    friend bool operator>(const Date& date1, const Date& date2);
    friend bool operator==(const Date& date1, const Date& date2);
    
    ~Date() {}

    void set_date(const int month, const int day, const int year);
    bool is_valid() const;
    int date_to_yyyymmdd() const;
    void reset();
    inline int month() const {return m_month;}
    inline int day() const {return m_day;}
    inline int year() const {return m_year;}

private:
    int m_day;
    int m_month;
    int m_year;
    int m_serialDate;

    int date_to_number(const Date& date);
    Date number_to_date(const int number);
};

#endif
