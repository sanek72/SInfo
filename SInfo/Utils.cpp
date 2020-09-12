#include "Utils.h"

//https://docs.microsoft.com/en-us/windows/win32/wmisdk/cim-datetime
std::string Utils::getCIM_DATETIME(std::string value) {

	if (value.size() != 25) {
		return "NULL";
	}
	//int a;
	//std::string GMT;
	std::string year = value.substr(0, 4);
	std::string month = value.substr(4, 2);
	std::string day = value.substr(6, 2);
	std::string hour = value.substr(8, 2);
	std::string minute = value.substr(10, 2);
	std::string seconds = value.substr(12, 2);

	//if (value.find("+")) {

	//	a = std::stoi(value.substr(value.find("+") + 1)) / 60;
	//	GMT = "GMT +" + std::to_string(a);

	//}else {

	//	a = std::stoi(value.substr(value.find("-") + 1)) / 60;
	//	GMT = "GMT -" + std::to_string(a);
	//}

	return year + "/" + month + "/" + day + " " + hour + ":" + minute + ":" +  seconds;
}
