#include <dispenser/flowmeter.hh>

namespace beer_atm
{

    Flowmeter::Flowmeter(int freq) : sample_freq{freq}
    {
    }

    Flowmeter::~Flowmeter()
    {
    }

    void Flowmeter::Integrate(int flowrate)
    {
        if (flowrate < 0)
            return;
        static float prev_flowrate = 0;
        if (reset)
        {
            reset = false;
        }
        else
        {
            volume += (prev_flowrate + flowrate) / (2 * sample_freq);
            CheckAlarm();
        }
        prev_flowrate = flowrate;
    }

    int Flowmeter::GetVolume()
    {
        return (int)volume;
    }

    void Flowmeter::ResetVolume()
    {
        reset = true;
        volume = 0;
    }

    void Flowmeter::SetAlarm(int dv, cb_t cb)
    {
        if (dv > 0 && cb != nullptr)
        {
            alarm_dv = dv;
            this->cb = cb;
            prev_volume = volume;
            alarm_en = true;
        }
    }

    void Flowmeter::ClearAlarm()
    {
        alarm_dv = 0;
        this->cb = nullptr;
        prev_volume = 0;
        alarm_en = false;
    }

    void Flowmeter::CheckAlarm()
    {
        if (!alarm_en)
            return;
        
        float curr_dv = volume - prev_volume;
        
        if (curr_dv >= alarm_dv)
        {
            prev_volume = volume;
            cb(curr_dv);
        }
    }
}