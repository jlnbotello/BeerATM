#ifndef DISPENSER_CLASS_H
#define DISPENSER_CLASS_H

#include "valve.hh"

namespace beer_atm
{
    class Dispenser
    {
    public:
        Dispenser(Valve & v);
        void EnableOutput();
        void DisableOutput();    
        void ResetAccumulator();
        void AddToAccumulator(int mililitres);
        void GetAccumulator();
    };
} // namespace beer_atm

#endif /* DISPENSER_CLASS_H */