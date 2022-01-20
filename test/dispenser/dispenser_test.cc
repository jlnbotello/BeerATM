#include <dispenser/dispenser.hh>
#include <dispenser/valve.hh>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

