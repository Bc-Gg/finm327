# include <iostream>
# include <vector>
# include <string>
# include <unordered_map>
# include <algorithm>

struct Trade
{
    std::string symbol;
    double price;

    Trade(const std::string &sym, double p)
        : symbol(sym), price(p) {}

    Trade() : symbol(""), price(0.0) {}
};

int main()
{
    // Dynamically allocate a single Trade object
    Trade *trade = new Trade("AAPL", 150.75);

    // Print the trade details
    std::cout << "Symbol: " << trade->symbol << std::endl;
    std::cout << "Price: " << trade->price << std::endl;
    
    // Dynamically allocate an array of 5 Trade objects
    Trade *trades = new Trade[5];
    trades[0] = Trade("AAPL", 150.75);
    trades[1] = Trade("GOOG", 2800.12);
    trades[2] = Trade("MSFT", 210.22);
    trades[3] = Trade("AMZN", 3300.77);
    trades[4] = Trade("TSLA", 720.46);

    // Print the array of trades
    std::cout << "\nArray of trades:" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Symbol: " << trades[i].symbol << ", Price: " << trades[i].price << std::endl;
    }

    delete[] trades;
    delete trade;

    return 0;
}