#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"

class OrderBook
{
    public:
    /** Construct, reading a csv data file */
        OrderBook(std::string filename);

    /** return vector of all known unique products in the dataset */
        std::vector<std::string> getKnownProducts();

    /** return vector of known orders according to the filters sent */
        std::vector<OrderBookEntry> getOrders(const OrderBookType type, 
                                              const std::string product, 
                                              const std::string timestamp);
    /** return a double of the highest bid in the set */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);

    /** return a double of the lowest bid in the set */
        static double getLowPrice(std::vector<OrderBookEntry> &orders);

        void insertOrder(OrderBookEntry& order);

        /** Return spread of a given order */
        static double getSpread(std::vector<OrderBookEntry> &orders);

    /** Receives an order set and return the given volume 
     * @param std::vector<OrderBookEntry>: Order set 
     * @return double: Volume of the given order set
    */
        static double getVolume(std::vector<OrderBookEntry> &orders);

        /** returns the earliest time in the orderbook */
        std::string getEarliestTime();
    /** returns the next time after the sent time in the orderbook 
     * If there is no next timestamp, wraps around the start
    */
        std::string getNextTime(const std::string timestamp);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    private:
        std::vector<OrderBookEntry> orders;
};