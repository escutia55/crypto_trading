#include "Wallet.h"
#include <vector>
#include "CSVReader.h"

Wallet::Wallet()
{

}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    if (0 > amount)
    {
        throw std::exception{};
    }

    if (0 == currencies.count(type))
    {
        balance = 0;
    }
    else // Is there
    {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (0 > amount)
    {
        throw std::exception{};
    }

    if (0 == currencies.count(type))
    {
        return false;
    }
    else if (containsCurrency(type,amount)) // There is enough currency
    {
        currencies[type] -= amount;
        return true;
    }
    else //they have it but not enough
    {
        return true;
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    //If the type of currency is not in the wallet, it will return false
    
    return (currencies[type] >= amount);
    
}

std::string Wallet::toString()
{
    std::string s;

    for (std::pair<std::string,double> pair: currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product,'/');
    // ask
    if (order.orderType == OrderBookType::ask)
    {
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder" << " : " << order.amount << std::endl;
        return containsCurrency(currency, order.amount);
    }
    // bid 
    if (order.orderType == OrderBookType::bid)
    {
        std::string currency = currs[1];
        std::cout << "Wallet::canFulfillOrder" << " : " << order.amount << std::endl;
        return containsCurrency(currency, (order.price * order.amount));
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, Wallet &wallet)
{
    os << wallet.toString();
    return os;
}

void Wallet::processSale(OrderBookEntry &sale)
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product,'/');
    // ask
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingcurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingcurrency] -= outgoingAmount;
    }
    // bid
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingcurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingcurrency] -= outgoingAmount;
    }
}