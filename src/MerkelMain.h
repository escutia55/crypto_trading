#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
    public:
        MerkelMain();
        /*Call this to start the sim*/
        void init();
        
    private:
        void printMenu();
        int getUserOption();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
        void processUserInput(int userOption);
        std::vector<OrderBookEntry> orders;
        OrderBook orderBook{"logger.csv"};
        Wallet wallet;
        std::string currentTime;
};