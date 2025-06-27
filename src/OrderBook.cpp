#include "OrderBook.h"
#include "CSVReader.h"
#include <vector>
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }

    for (const std::pair<std::string, bool> &productStringBoolPair : prodMap)
    {
        products.push_back(productStringBoolPair.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(const OrderBookType type, const std::string product, const std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry& currentOrder : orders)
    {
        if (currentOrder.orderType == type &&
            currentOrder.product == product && 
            currentOrder.timestamp == timestamp)
            {
                orders_sub.push_back(currentOrder);
            }
    }

    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;

    for (OrderBookEntry& e : orders)
    {
        if(e.price > max)
        {
            max = e.price;
        }
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double low = orders[0].price;

    for (OrderBookEntry &e : orders)
    {
        if (e.price < low)
        {
            low = e.price;
        }
    }

    return low;
}

double OrderBook::getSpread(std::vector<OrderBookEntry> &orders)
{
    return getHighPrice(orders) - getLowPrice(orders);
}

/** Receives an order set and return the given volume 
     * @param std::vector<OrderBookEntry>: Order set 
     * @return double: Volume of the given order set
    */
double OrderBook::getVolume(std::vector<OrderBookEntry> &orders)
{
    double volume = 0;
    for (OrderBookEntry &e : orders)
    {
        volume += (e.amount * e.price);
    }

    return volume;
}

std::string OrderBook::getEarliestTime()
{
    std::string earliest_timestamp = orders[0].timestamp;
    for (const OrderBookEntry &e : orders)
    {
        if (e.timestamp < earliest_timestamp)
        {
            earliest_timestamp = e.timestamp;
        }
    }
    return earliest_timestamp;
}

std::string OrderBook::getNextTime(const std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if(e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }

    if ("" == next_timestamp)
    {
        next_timestamp = getEarliestTime();
    }
    
    return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimeStamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry &bid : bids)
        {
            if (bid.price >= ask.price) //Match!
            {
                OrderBookEntry sale = {ask.price, 0, timestamp, product, OrderBookType::asksale, "dataset"};

                if ("simuser" == bid.username)
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if ("simuser" == ask.username)
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                if (bid.amount == ask.amount) //  bid completely clears as
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    // Can do no more with this ask. Go onto the next
                    break;
                }

                if (bid.amount > ask.amount) // ask is completely gone slice the bid
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    // Adjust the bid in place so it can be used to process the next ask
                    bid.amount = bid.amount - ask.amount;
                    break;
                }

                if ((bid.amount < ask.amount) && (bid.amount > 0))
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    //Update the ask and allow further bids to process the remaining amount
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0; //Make sure the bid is not processed again
                    //Some asks remain so go to the next bid
                    continue;
                }
            }
        }
    }
    return sales;
}
