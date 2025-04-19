#include "feed_parser.h"
#include "market_snapshot.h"
#include "order_manager.h"

int main() {
    auto feed = load_feed("sample_feed.txt");

    MarketSnapshot snapshot;
    OrderManager order_manager;

    for (const auto& event : feed) {

        // Integrate with your components:
        if (event.type == FeedType::BID) {
            snapshot.update_bid(event.price, event.quantity);
        }
        else if (event.type == FeedType::ASK) {
            snapshot.update_ask(event.price, event.quantity);
        }
        else if (event.type == FeedType::EXECUTION) {
            order_manager.handle_fill(event.order_id, event.quantity);
        }

        // Fake Strategy 1 (To meet sample_feed location)
        if (event.type == FeedType::ASK && event.price == 100.25) {
            int qty = 30;
            int id = order_manager.place_order(Side::Buy, snapshot.get_best_ask()->price, qty);
        }

        // Fake Strategy 2 (To meet sample_feed location)
        if (event.type == FeedType::BID && event.price == 100.17) {
            int qty = 50;
            int id = order_manager.place_order(Side::Sell, snapshot.get_best_bid()->price, qty);
        }
    }
    return 0;
}