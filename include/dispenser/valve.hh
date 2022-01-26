#ifndef CLASS_VALVE_H
#define CLASS_VALVE_H

namespace beer_atm {
    enum class ValveState {
    OFF, ON, FAIL
    };
    
    class Valve {
        public:
            Valve(){};
            virtual ~Valve() {};
            virtual void Enable() {status = ValveState::ON;};
            virtual void Disable() {status = ValveState::OFF;};
            virtual ValveState Status(){return status;};
        protected:
            ValveState status = ValveState::OFF;
    };
}
#endif /* CLASS_VALVE_H */