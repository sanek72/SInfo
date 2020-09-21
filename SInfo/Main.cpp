
#include "SysInfoFactory.h"
#include <locale.h> 

int main(){

    setlocale(LC_CTYPE, "Russian");

    SysInfoFactory info;

    system("pause"); 
    return 0;
}

