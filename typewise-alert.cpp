#include "typewise-alert.h"
#include <stdio.h>
#include <map>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

std::map<CoolingType, std::pair<int, int>> classifyCoolingTypeRange =
    {
        {CoolingType::PASSIVE_COOLING, std::make_pair(0, 35)},
        {CoolingType::HI_ACTIVE_COOLING, std::make_pair(0, 45)},
        {CoolingType::MED_ACTIVE_COOLING, std::make_pair(0, 40)}
    };

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  lowerLimit = classifyCoolingTypeRange.find(coolingType)->second.first;
  upperLimit = classifyCoolingTypeRange.find(coolingType)->second.second;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

std::map<BreachType, std::string> BreachTypeMsg =
    {
        {BreachType::TOO_LOW, "Hi, the temperature is too low\n"},
        {BreachType::TOO_HIGH, "Hi, the temperature is too high\n"},
        {BreachType::NORMAL, "Hi, the temperature is normal\n"}
    };


bool sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return true;
}

bool sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType != NORMAL)
  {
      const char* BreachMessage = BreachTypeMsg[breachType];
      printf("To: %s\n", recepient);
      printf("%s\n", BreachMessage  );
      return true;
  }
  return false;
  }

void sendAlert(AlertTarget alertTarget, BreachType breachType)
{
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  sendAlert(alertTarget, breachType);
  
}
