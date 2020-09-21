#pragma once

#include <iostream>
#include <cstdlib> 
#include "Utils.h"
#include "Motherboard.h"
#include "OS.h"
#include "CPU.h"
#include "GPU.h"
#include "RAM.h"
#include "BIOS.h"

using namespace std;

class SysInfoFactory {

private:

	
public:

	SysInfoFactory();

	void gathered();

};

