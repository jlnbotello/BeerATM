#ifndef CLASS_FLOWMETER_H
#define CLASS_FLOWMETER_H

namespace beer_atm
{
	class Flowmeter
	{
	public:
		Flowmeter(int freq);
		~Flowmeter();
		void Integrate(int flowrate);
		int GetVolume();
		void ResetVolume();
		typedef void (*cb_t)(int);
		void SetAlarm(int dv, cb_t cb);
		void ClearAlarm();


	private:
		float volume = 0;
		float prev_volume = 0;
		int sample_freq = 0;
		bool reset = true;
		cb_t cb = nullptr;
		int alarm_dv = 0;
		bool alarm_en = false;
		void CheckAlarm();
	};
}
#endif /* CLASS_FLOWMETER_H */