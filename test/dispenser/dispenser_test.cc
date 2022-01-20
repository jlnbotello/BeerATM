#include <dispenser/dispenser.hh>
#include <dispenser/valve.hh>
#include <dispenser/flowmeter.hh>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define SAMPLE_FREQ 100

using namespace beer_atm;
using ::testing::AtLeast; 

class MockValve : public Valve {
 public:
  MOCK_METHOD(void, Enable, (), (override));
  MOCK_METHOD(void, Disable, (), (override));
  MOCK_METHOD(ValveState, Status, (), (override));
  
};

TEST(ValveTests, enable)
{
    MockValve valve;
    EXPECT_CALL(valve, Enable())
    .Times(AtLeast(1));
    
    valve.Enable();
}


/**
 * @brief Construct a new TEST object
 *        GetVolume is zero after creation
 * 
 */

TEST(FlowmeterTests, Initialization){
  Flowmeter fm(SAMPLE_FREQ);
  
  int expected = 0;
  int result = fm.GetVolume();
  
  EXPECT_EQ(result, expected);
}

/**
 * @brief Construct a new TEST object
 *        Negative value are not valid entries
 */

TEST(FlowmeterTests, IntegrateNegativeNoHarmful){
  Flowmeter fm(SAMPLE_FREQ);

    fm.Integrate(-1);
    fm.Integrate(-2000);

    int expected = 0;
    int result = fm.GetVolume();

    EXPECT_EQ(result, expected);
}

/**
 * @brief Construct a new TEST object
 * 
 */

TEST(FlowmeterTests, GetVolume_500ml){
  Flowmeter fm(SAMPLE_FREQ);
  int flowrate = 250; //ml_per_sec
  int total_volume = 500;
  int time_to_500ml = total_volume/flowrate;  //2 seconds
  int n_samples = time_to_500ml * SAMPLE_FREQ;
  

  for(int i=0; i<= n_samples;i++)
    fm.Integrate(flowrate);
  
  int expected = total_volume;
  int result = fm.GetVolume();

  EXPECT_EQ(result, expected);
}


TEST(FlowmeterTests, ResetVolume){
  Flowmeter fm(SAMPLE_FREQ);
  
  fm.Integrate(20);
  fm.Integrate(20);
  fm.ResetVolume();
  
  int expected = 0;
  int result = fm.GetVolume();

  EXPECT_EQ(result, expected);
}

static int times = 0;
static void OnChangeVolCallback(int ml){
    times++;
}

TEST(FlowmeterTests, DeltaVolumeAlarm){
  Flowmeter fm(SAMPLE_FREQ);
  int flowrate = 250; //ml_per_sec
  int total_volume = 500;
  int time_to_500ml = total_volume/flowrate;  //2 seconds
  int n_samples = time_to_500ml * SAMPLE_FREQ;
  int delta_vol = 50;

  fm.SetAlarm(delta_vol, OnChangeVolCallback);
  
  for(int i=0; i<= n_samples;i++)
    fm.Integrate(flowrate);

  int expected = 10;
  int result = times;

  EXPECT_EQ(result, expected);

}