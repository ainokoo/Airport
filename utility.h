#pragma once
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

enum Error_code {
	result, fail, success, overflow, underflow, 
}; 

void run_idle(int time);