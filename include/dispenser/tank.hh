#ifndef CLASS_TANK_H
#define CLASS_TANK_H
#include <string>
#include <stdexcept>

namespace beer_atm
{
    class Tank
    {
    public:
        Tank(float capacity, std::string name) : capacity{capacity}, name{name} {
            if ( capacity <= 0) {
                throw std::invalid_argument( "invalid capacity" );
    }
        };
        float GetCapacity() { return capacity; };
        float GetRemaining() { return capacity - withdrawn; };
        std::string GetName() { return name; };
        void Withdraw(float litres){
            if (litres < 0) return;
            if(litres < (capacity - withdrawn))
                withdrawn += litres;
            else
                withdrawn = capacity;
        };

    private:
        const float capacity;
        std::string name;
        float withdrawn = 0;
    };
}
#endif /* CLASS_TANK_H */