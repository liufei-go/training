#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib> // RAND_MAX
#include <cmath>
#include <iomanip>
#include <map>

double getRandom()
{
    return (double)rand() / RAND_MAX;
}

double getRoundValue(const double value, const int decimal)
{
    int factor = 1;
    int counter = 0;
    while (counter < decimal)
    {
        factor *= 10;
        ++counter;
    }
    return round(value * factor) / factor;
}

double getRedPackMoney(double& totalMoneyLeft, int& numPeopleLeft)
{
    if (numPeopleLeft == 1)
    {
        return totalMoneyLeft;
    }

    const double minMoney = 0.01;
    const double maxMoney = totalMoneyLeft / numPeopleLeft * 2;
    
    double thisMoney = getRoundValue(getRandom() * maxMoney, 2);
    if (thisMoney < minMoney)
    {
        thisMoney = minMoney;
    }
    --numPeopleLeft;
    totalMoneyLeft -= thisMoney;

    return thisMoney;
}

void dispenseRedPack(const double redPackMoney, 
                     const int numPeople, 
                     const int bypassIdx, 
                     std::map<int, double>& accounts)
{
    double * changes = new double[numPeople - 1];

    double totalMoneyLeft = redPackMoney;
    int numPeopleLeft = numPeople - 1;
    for (int i = 0; i < numPeople - 1; ++i)
    {
        changes[i] = getRedPackMoney(totalMoneyLeft, numPeopleLeft);
    }

    int j = 0;
    for (int i = 0; i < numPeople; ++i)
    {
        if (i == bypassIdx)
        {
            continue;
        }

        accounts[i] += changes[j];
        ++j;
    }

    delete changes;
}

void analyzeAccounts(const std::map<int, double>& accounts)
{
    double sum = 0;
    for (std::map<int, double>::const_iterator citer = accounts.begin(); citer != accounts.end(); ++citer)
    {
        sum += citer->second;
    }
    double mean = sum / accounts.size();

    double sd = 0;
    for (std::map<int, double>::const_iterator citer = accounts.begin(); citer != accounts.end(); ++citer)
    {
        sd += pow(citer->second - mean, 2);
    }
    sd = sqrt(sd / accounts.size());

    std::cout << "Standard deviation: ";
    for(size_t i = 0; i < sd;)
    {
        std::cout << "+";
        i = i + 5;
    }
    std::cout << std::endl;
}

int main(int argc, char * argv[])
{
    srand(time(NULL));

    // Define variables
    int numPeople = 10;
    double initialMoney = 1000;
    double redPackMoney = 50;
    const int LOOPS = atoi(argv[1]);

    // Initialize accounts
    std::map<int, double> accounts;
    for (int i = 0; i < numPeople; ++i)
    {
        accounts.insert(std::pair<int, double>(i, initialMoney));
    }

    // Dispense redpacks
    for (int i = 0; i < LOOPS; ++i)
    {
        for (int j = 0; j < numPeople; ++j)
        {
            accounts[j] -= redPackMoney;
            dispenseRedPack(redPackMoney, numPeople, j, accounts);
        }

        analyzeAccounts(accounts);
    }

    std::cout << "After " << LOOPS << " rounds" << std::endl;
    for (int i = 0; i < numPeople; ++i)
    {
        std::cout << "People " << i + 1 << ": ";
        std::cout << initialMoney << "   " << accounts[i] << std::endl;
    }

    return 0;
}
