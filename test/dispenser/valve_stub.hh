#ifndef VALVE_STUB_CLASS_H
#define VALVE_STUB_CLASS_H

#include "dispenser/valve.hh"
#include <iostream>

namespace beer_atm
{
    class ValveStub : public Valve
    {
    public:
        ~ValveStub() {};
        void Enable() {status = ValveState::ON;};
        void Disable() {status = ValveState::OFF;};
        ValveState Status(){return status;};
    private:
        ValveState status = ValveState::OFF;
        
    };
} // namespace beer_atm

#endif /* VALVE_STUB_CLASS_H */