#ifndef CLASS_VALVE_H
#define CLASS_VALVE_H

namespace beer_atm {
    enum class ValveState {
    OFF, ON, FAIL
    };
    
    class Valve {
        public:
            virtual ~Valve() {};
            virtual void Enable() = 0;
            virtual void Disable() = 0;
            virtual ValveState Status() = 0;
    };
}
#endif /* CLASS_VALUE_H */