#include <dispenser/dispenser.hh>
#include <dispenser/flowmeter.hh>
#include <dispenser/tank.hh>
#include <dispenser/valve.hh>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define DEFAULT_SAMPLE_FREQ   100
#define DEFAULT_FLOWRATE      250   // [ml/sec]
#define DEFAULT_TOTAL_VOLUME  500   // [ml]

using namespace beer_atm;

class MockClient {
  public:
  MOCK_METHOD(void, Callback, (int ml),());
};

static MockClient client;

static void OnChangeVolCallback(int ml){
  client.Callback(ml);
}

static void simulte_flow(Flowmeter & f, int flowrate, int final_volume, int sample_freq){
  int time_to_500ml = final_volume/flowrate;  //2 seconds
  int n_samples = time_to_500ml * sample_freq; 

  for(int i=0; i<= n_samples;i++)
    f.Integrate(flowrate);
}

TEST(ValveTests, DisableOnInit){
    Valve valve;

    EXPECT_EQ(valve.Status(), ValveState::OFF);
}

TEST(ValveTests, Enable){
    Valve valve;
    
    valve.Enable();

    EXPECT_EQ(valve.Status(), ValveState::ON);
}

TEST(ValveTests, Disable){
    Valve valve;
    valve.Enable();

    valve.Disable();
    
    EXPECT_EQ(valve.Status(), ValveState::OFF);
}

TEST(FlowmeterTests, ZeroVolumeOnInit){
  Flowmeter fm(DEFAULT_SAMPLE_FREQ);
  
  EXPECT_EQ(fm.GetVolume(), 0);
}

TEST(FlowmeterTests, IntegrateNegativeNoHarmful){
    Flowmeter fm(DEFAULT_SAMPLE_FREQ);

    fm.Integrate(-9999);

    EXPECT_EQ(fm.GetVolume(), 0);
}

TEST(FlowmeterTests, GetVolume){
  Flowmeter fm(DEFAULT_SAMPLE_FREQ);

  simulte_flow(fm, DEFAULT_FLOWRATE, DEFAULT_TOTAL_VOLUME, DEFAULT_SAMPLE_FREQ);

  EXPECT_EQ(fm.GetVolume(), DEFAULT_TOTAL_VOLUME);
}

TEST(FlowmeterTests, ResetVolume){
  Flowmeter fm(DEFAULT_SAMPLE_FREQ);  
  simulte_flow(fm, DEFAULT_FLOWRATE, DEFAULT_TOTAL_VOLUME, DEFAULT_SAMPLE_FREQ);
  
  fm.ResetVolume();

  EXPECT_EQ(fm.GetVolume(), 0);
}

TEST(FlowmeterTests, SetAlarm){
  Flowmeter fm(DEFAULT_SAMPLE_FREQ);
  int delta_vol = 50;
  int expected = DEFAULT_TOTAL_VOLUME/delta_vol;
  
  EXPECT_CALL(client, Callback(delta_vol)).Times(expected);

  fm.SetAlarm(delta_vol, OnChangeVolCallback);
  simulte_flow(fm, DEFAULT_FLOWRATE, DEFAULT_TOTAL_VOLUME, DEFAULT_SAMPLE_FREQ);
}

TEST(FlowmeterTests, ClearAlarm){
  Flowmeter fm(DEFAULT_SAMPLE_FREQ);
  int delta_vol = 50;
  int half_total_volume = DEFAULT_TOTAL_VOLUME / 2;
  int n_calls = half_total_volume/delta_vol;
  
  EXPECT_CALL(client, Callback(delta_vol)).Times(n_calls);
  
  fm.SetAlarm(delta_vol, OnChangeVolCallback);
  simulte_flow(fm, DEFAULT_FLOWRATE, half_total_volume, DEFAULT_SAMPLE_FREQ);
  fm.ClearAlarm();
  simulte_flow(fm, DEFAULT_FLOWRATE, half_total_volume, DEFAULT_SAMPLE_FREQ);
}

TEST(TankTests, InitException)
{
  EXPECT_THROW({
    try
    {
      Tank(-50, "IPA #3");
    }
    catch(const std::invalid_argument &e)
    {
      EXPECT_STREQ( "invalid capacity", e.what() );
      throw;
    }
  },std::invalid_argument);
}

TEST(TankTests, GetCapacity)
{
  Tank tank(50, "IPA #3");
  EXPECT_EQ(tank.GetCapacity(), 50);
}

TEST(TankTests, GetRemaining) 
{
    Tank tank(50, "IPA #3");
    EXPECT_EQ(tank.GetRemaining(), 50);
}

TEST(TankTests, Withdraw) 
{
  float w = 20.5, r = 29.5;
  Tank tank(w+r, "IPA #3");

  tank.Withdraw(w);

  EXPECT_EQ(tank.GetRemaining(),r);
}

TEST(TankTests, SafeWithdraw) 
{
  
  Tank tank(50, "IPA #3");

  tank.Withdraw(50.5);

  EXPECT_EQ(tank.GetRemaining(),0);
}

TEST(TankTests, GetName) 
{ 
  Tank tank(50, "IPA #3");
  EXPECT_EQ(tank.GetName(),"IPA #3");
}