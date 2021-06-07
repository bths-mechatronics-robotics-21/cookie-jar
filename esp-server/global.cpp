#include "global.h"
#include <Arduino.h>
using namespace std;

int timeLeft;
String webCodeApproved = "<h1>Hooray! Your cookie has been dispensed.</h1>";
String webCodeDenied = "<h1>Please wait " + String(timeLeft) + " hours for your cookie.</h1>";
