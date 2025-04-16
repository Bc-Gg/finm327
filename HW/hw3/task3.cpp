# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>

using namespace std;

struct Trade
{
    std::string symbol;
    double price;

    Trade(const std::string &sym, double p)
        : symbol(sym), price(p) {}

    Trade() : symbol(""), price(0.0) {}
};

struct ControlBlock
{
    int refCount;
    Trade* data;
    
    ControlBlock(Trade* p) : refCount(1), data(p) {}
    
    ~ControlBlock()
    {
        delete data;
    }
};

class TradeHandle
{
    ControlBlock* controlBlock;

public:
    TradeHandle(Trade *p)
    {
        controlBlock = new ControlBlock(p);
    }
    
    ~TradeHandle()
    {
        decrementRefCount();
    }
    
    TradeHandle(const TradeHandle &other)
    {
        controlBlock = other.controlBlock;
        controlBlock->refCount++;
    }
    
    TradeHandle &operator=(const TradeHandle &other)
    {
        if (this != &other)
        {
            decrementRefCount();
            controlBlock = other.controlBlock;
            controlBlock->refCount++;
        }
        return *this;
    }
    
    TradeHandle(TradeHandle &&other)
    {
        controlBlock = other.controlBlock;
        other.controlBlock = nullptr;
    }
    
    TradeHandle &operator=(TradeHandle &&other)
    {
        if (this != &other)
        {
            decrementRefCount();
            controlBlock = other.controlBlock;
            other.controlBlock = nullptr;
        }
        return *this;
    }
    
    Trade *operator->()
    {
        return controlBlock->data;
    }
    
    Trade &operator*()
    {
        return *(controlBlock->data);
    }
    
    int getRefCount() const
    {
        return controlBlock ? controlBlock->refCount : 0;
    }
    
private:
    void decrementRefCount()
    {
        if (controlBlock)
        {
            controlBlock->refCount--;
            if (controlBlock->refCount == 0)
            {
                delete controlBlock;
            }
        }
    }
};

int main(){
    TradeHandle tradeHandle(new Trade("AAPL", 150.0));
    cout << tradeHandle->symbol << " " << tradeHandle->price << endl;
    
    TradeHandle anotherHandle = tradeHandle;
    cout << "Reference count: " << tradeHandle.getRefCount() << endl;

    {
        TradeHandle thirdHandle = tradeHandle;
        cout << "Reference count: " << tradeHandle.getRefCount() << endl;
    }
    cout << "Reference count after scope exit: " << tradeHandle.getRefCount() << endl;

    return 0;
}