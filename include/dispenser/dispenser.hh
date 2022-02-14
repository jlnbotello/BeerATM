#ifndef DISPENSER_CLASS_H
#define DISPENSER_CLASS_H

#include "valve.hh"
#include "tank.hh"
#include "flowmeter.hh"

namespace beer_atm
{
    struct Price{
        float value;
        std::string unit;
    };
    struct Drink{
        std::string name;
        std::string desc;
        Price price;
    };
    
    class Dispenser
    {
    public:
        Dispenser(int id, Drink d, Valve & v, Tank & t, Flowmeter & f);
        void Enable();
        void Disable();
        Drink GetDrink();
        void OnDeliveryStart(/* callback */);
        void OnDeliveryStop(/* callback */);
        void OnDeliveryUpdate(/* callback */ int threshold);
    };
} // namespace beer_atm

#endif /* DISPENSER_CLASS_H */