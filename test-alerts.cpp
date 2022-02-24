#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits")
{
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(32, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(22, 20, 30) == NORMAL);
}

TEST_CASE("classify the temperature breach according to limits") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,2) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,25) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-2) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,42) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-6) == TOO_LOW);
}
 
TEST_CASE("verify if the message is sent to Controller")
{
  REQUIRE(sendToController(TOO_LOW) == true);
  REQUIRE(sendToController(TOO_HIGH) == true);        
  REQUIRE(sendToController(NORMAL) == true);
}

TEST_CASE("verify if the message is sent on Email")
{
  REQUIRE(sendToEmail(TOO_LOW) == true);
  REQUIRE(sendToEmail(TOO_HIGH) == true);        
  REQUIRE(sendToEmail(NORMAL) == false);
}
  
TEST_CASE("check breach type and alert the user ")
{
 BatteryCharacter.coolingType = CoolingType::PASSIVE_COOLING;
 REQUIRE(checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,20) == true);
 batteryChar.coolingType = CoolingType::HI_ACTIVE_COOLING;
 REQUIRE(checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,46) == true); 
 batteryChar.coolingType = CoolingType::MED_ACTIVE_COOLING;
 REQUIRE(checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING,-2) == true);  
}

