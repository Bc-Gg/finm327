//
// Created by Zhengyun Xu on 2025/4/18.
//

#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <map>
#include <memory>
#include <iostream>

enum class OrderStatus { New, Filled, PartiallyFilled, Cancelled };
enum class Side { Buy, Sell };

struct MyOrder {
    int id;
    Side side;
    double price;
    int quantity;
    int filled = 0;
    OrderStatus status = OrderStatus::New;
};

class OrderManager {
    std::map<int, std::unique_ptr<MyOrder>> orders;
    std::map<int, std::unique_ptr<MyOrder>> active_orders;
    static int ID_num;

public:
    int place_order(Side side, double price, int qty) {
        ID_num++;
        orders[ID_num] = std::make_unique<MyOrder>(ID_num, side, price, qty);
        active_orders[ID_num] = std::make_unique<MyOrder>(ID_num, side, price, qty);
        const char* side_str = (side == Side::Buy) ? "BUY" : "SELL";

        std::cout << "[Place] " << side_str << " "
        << price << " x " << qty << " -> ID = " << ID_num << "\n";

        return ID_num;
    };

    void cancel(int id) {
        if (orders.find(id) == orders.end()) {
            std::cout << "[Cancel] Order Can Not Be Found" << "\n";
        }
        else {
            orders[id]->status = OrderStatus::Cancelled;
            active_orders.erase(id);
            std::cout << "[Cancel] Order " << id << "Cancel Successful" << "\n";
        }
    };

    void handle_fill(int id, int filled_qty) {
        int rest_qty = active_orders[id]->quantity;
        if (filled_qty < rest_qty) {
            orders[id]->status = OrderStatus::PartiallyFilled;
            active_orders[id]->quantity -= filled_qty;
            active_orders[id]->status = OrderStatus::PartiallyFilled;
            std::cout << "[Execution] Order " << id << " filled " << filled_qty << "\n";
            std::cout << "[Status] Partial fill" << "\n";
        }
        else {
            orders[id]->status = OrderStatus::Filled;
            active_orders.erase(id);
            std::cout << "[Execution] Order " << id << " filled " << filled_qty << "\n";
            std::cout << "[Status] Filled -> Order removed from active list" << "\n";
        }
    };

    void print_active_orders() const {
        for (const auto& order : active_orders) {
            const char* side_str = (order.second->side == Side::Buy) ? "BUY" : "SELL";
            std::cout << "[Active Order] " << side_str << " "
                      << order.second->price << " x " << order.second->quantity
                      << " -> ID = " << order.first << "\n";
        }
    };
};

int OrderManager::ID_num = 0;

#endif //ORDER_MANAGER_H
