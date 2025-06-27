#pragma once
#include <string>


enum class OrderBookType{ask, bid, unknown, asksale, bidsale};

class OrderBookEntry
{
    public:
        OrderBookEntry(double _price,
                       double _amount,
                       std::string _timestamp,
                       std::string _product,
                       OrderBookType _orderType,
                       std::string _username = "dataset");

        static OrderBookType stringToOrderBookType(const std::string& s);

        //Leaving implementation of the function in the header file because headers are compiled 
        // every time. Even if they do not change, while cpp files are only compiled if they change
        static bool compareByTimeStamp(OrderBookEntry &e1, OrderBookEntry &e2);
        static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2);
        static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};