#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
                               double _amount,
                               std::string _timestamp,
                               std::string _product,
                               OrderBookType _orderType,
                               std::string _username)
  : price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    orderType(_orderType),
    username(_username)

  {

  }

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string& s)
{
  OrderBookType orderType;
  if("ask" == s)
  {
    orderType = OrderBookType::ask;
  }
  else if ("bid" == s)
  {
    orderType = OrderBookType::bid;
  }
  else if ("asksale" == s)
  {
    orderType = OrderBookType::asksale;
  }
  else if ("bidsale" == s)
  {
    orderType = OrderBookType::bidsale;
  }
  else
  {
    orderType = OrderBookType::unknown;
  }

  return orderType;
}

bool OrderBookEntry::compareByTimeStamp(OrderBookEntry &e1, OrderBookEntry &e2)
{
  return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2)
{
  return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2)
{
  return e1.price > e2.price;
}
