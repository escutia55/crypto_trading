#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;

    signed int start, end;
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

int main()
{
    
    std::ifstream csvFile {"logger.csv"};
    std::string line;
    std::vector<std::string> tokens;

    if (csvFile.is_open())
    {
        while(std::getline(csvFile,line))
        {
            //std::cout << line << std::endl;
            tokens = tokenise(line, ',');
            if(tokens.size() != 5)
            {
                std::cout << "bad line" << std::endl; 
                continue;
            }

            try
            {
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
                std::cout << price << ":" << amount << std::endl;
            }
            catch(std::exception& e)
            {
                std::cout << "Bad float! " << tokens[3] << std::endl;
                std::cout << "Bad float! " << tokens[4] << std::endl;
                break;
            }
 
            for (std::string& token : tokens)
            {
                std::cout<< token << std::endl;
            }
        }

        csvFile.close();
    }
    else
    {
        std::cout << "could not open file" << std::endl;
    }

    return 0;
}