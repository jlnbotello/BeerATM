#include "ev_manager.hh"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockSubscriber
{
public:
  MOCK_METHOD(void, ev_cancel_pressed, ());
  MOCK_METHOD(void, ev_cw_step, ());
};

class EvMgrTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  
  }

  EventHandler evh;
  MockSubscriber subscriber;
  EventRouter rtr;

};

TEST_F(EvMgrTest, cancelOnce)
{
  EventHandler::cb_t<MockSubscriber> callback = [](MockSubscriber* obj)
  {
    obj->ev_cancel_pressed();
  };
  
  evh.add(EventHandler::EV_CANCEL_PRESSED, callback, &subscriber);

  EXPECT_CALL(subscriber, ev_cancel_pressed()).Times(1);

  evh.trigger(EventHandler::EV_CANCEL_PRESSED);
}

TEST_F(EvMgrTest, cwStepOnce)
{
  EventHandler::cb_t<MockSubscriber> callback = [](MockSubscriber* obj) 
  {
    obj->ev_cw_step();
  };
  
  evh.add(EventHandler::EV_CW_STEP, callback, &subscriber);

  EXPECT_CALL(subscriber, ev_cw_step()).Times(1);

  evh.trigger(EventHandler::EV_CW_STEP);
}

void standalone_callback(void * obj){};

TEST_F(EvMgrTest, addStandaloneFunction)
{
  bool added = evh.add(EventHandler::EV_CW_STEP, standalone_callback, (void*)0);
  ASSERT_EQ(added,true);
}

TEST_F(EvMgrTest, routeEvent)
{
  EventHandler::cb_t<MockSubscriber> callback = [](MockSubscriber* obj) 
  {
    obj->ev_cw_step();
  };
  
  evh.add(EventHandler::EV_CW_STEP, callback, &subscriber);
  rtr.add("home/page1", &evh);

  EXPECT_CALL(subscriber,ev_cw_step()).Times(1);

  rtr.route("home/page1", EventHandler::EV_CW_STEP);  
}