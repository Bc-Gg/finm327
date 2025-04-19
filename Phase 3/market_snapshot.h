//
// Created by Zhengyun Xu on 2025/4/18.
//

#ifndef MARKET_SNAPSHOT_H
#define MARKET_SNAPSHOT_H

#include <map>
#include <memory>
#include <iostream>

struct PriceLevel {
    double price;
    int quantity;
    PriceLevel(double p, int q) : price(p), quantity(q) {}
};

class MarketSnapshot {
    std::map<double, std::unique_ptr<PriceLevel>> bids; // sorted descending
    std::map<double, std::unique_ptr<PriceLevel>> asks; // sorted ascending

public:
    void update_bid(double price, int qty) {
        if (bids.find(price) != bids.end()) {
            if (qty == 0) {
                if (get_best_bid()->price == price) {
                    std::cout << "[Market] Best Bid: " << price << " removed" << "\n";
                }
                bids.erase(price);
            }
            else {
                bids[price] = std::make_unique<PriceLevel>(price, qty);
            }
        }
        else {
            bids[price] = std::make_unique<PriceLevel>(price, qty);
            std::cout << "[Market] New Bid: " << price << " x " << qty << "\n";
        }
    };

    void update_ask(double price, int qty) {
        if (asks.find(price) != asks.end()) {
            if (qty == 0) {
                if (get_best_ask()->price == price) {
                    std::cout << "[Market] Best Ask: " << price << " removed" << "\n";
                }
                asks.erase(price);
            }
        }
        else {
            asks[price] = std::make_unique<PriceLevel>(price, qty);
            std::cout << "[Market] New Ask: " << price << " x " << qty << "\n";
        }
    };

    const PriceLevel* get_best_bid() const {
        if (bids.empty()) {
            std::cout << "[Market] No Bid Available" << "\n";
            return nullptr;
        }
        const PriceLevel* best_bid = bids.rbegin()->second.get();
        std::cout << "[Market] Best Bid: " << best_bid->price << " x " << best_bid->quantity << "\n";
        return best_bid;
    }

    const PriceLevel* get_best_ask() const {
        if (asks.empty()) {
            std::cout << "[Market] No Ask Available" << "\n";
            return nullptr;
        }
        const PriceLevel* best_ask = asks.begin()->second.get();
        std::cout << "[Market] Best Ask: " << best_ask->price << " x " << best_ask->quantity << "\n";
        return best_ask;
    };
};

#endif //MARKET_SNAPSHOT_H
