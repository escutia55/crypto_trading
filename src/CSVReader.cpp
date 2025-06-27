#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFileName};
    std::string line;

    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV read Bad data " << std::endl;
            }
        }
    }

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;

    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;

    int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0); //Find the first character which is not a separator

    do
    {
        /* Find a separator */
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
        {
            /*A separator was found, get the token before the separator*/
            token = csvLine.substr(start, end - start);
        }
        else
        {
            /* If it reaches this point, it means that no separator was found, Example: "thing1" */
            token = csvLine.substr(start, csvLine.length() - start);
        }

        tokens.push_back(token);

        start = end + 1; //Add plus one to move one character after the separator

    } while (end != std::string::npos);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> strings)
{
    double price, amount;

    if (strings.size() != TOKENS_PER_LINE)
    {
        std::cout << "Bad line" << std::endl;
        throw std::exception{};
    }

    try
    {
        price = std::stod(strings[3]);
        amount = std::stod(strings[4]);
    }
    catch (const std::exception &e)
    {
        std::cout << "Bad float! " << strings[3] << std::endl;
        std::cout << "Bad float! " << strings[4] << std::endl;
        throw;
    }

    OrderBookEntry obe{
        price,
        amount,
        strings[0],
        strings[1],
        OrderBookEntry::stringToOrderBookType(strings[2]),
        "dataset"};

    return obe; 
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       std::string orderType,
                                       std::string username)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception &e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << std::endl;
        throw;
    }

    OrderBookEntry obe{
        price,
        amount,
        timestamp,
        product,
        OrderBookEntry::stringToOrderBookType(orderType),
        username
        };

    return obe;
}