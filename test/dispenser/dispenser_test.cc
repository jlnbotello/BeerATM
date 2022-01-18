#include <dispenser/dispenser.hh>
#include "valve_stub.hh"
#include "gtest/gtest.h"

TEST(ValveTests, initialization)
{
    // Arrange
    beer_atm::Valve *val = new beer_atm::ValveStub();

    // Act & Assert
    EXPECT_EQ(val->Status(), beer_atm::ValveState::OFF);

    // Release
    delete val;
}
