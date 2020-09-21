#include "SysInfoFactory.h"


SysInfoFactory::SysInfoFactory(){
	gathered();
}

void SysInfoFactory::gathered(){

	GPU gpu = GPU(true);
	BIOS bios = BIOS(true);

}


