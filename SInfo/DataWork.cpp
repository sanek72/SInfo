#include "DataWork.h"


void DataWork::setDataBSTR(std::string _key, BSTR _bstr){

	if (_bstr) {

		std::string key = _key + std::to_string(data_count);

	    data.bstr.insert(make_pair(key, _com_util::ConvertBSTRToString(_bstr)));

	}
}

void DataWork::setDataLong(std::string _key, UINT _uint) {

	std::string key = _key + std::to_string(data_count);

	data.longer.insert(make_pair(key, _uint));

}

std::string DataWork::getDataString(std::string _key) {

	std::string s = "unavailable";


	if (data.bstr.find(_key) != data.bstr.end()) {

		s = data.bstr[_key];

	}
	else {
		return s;
	}

	return s;
}

long long DataWork::getDataLong(std::string _key) {

	long long s = 0;

	if (data.longer.find(_key) != data.longer.end()) {

		s = data.longer[_key];

	}
	else {
		return 0;
	}

	return s;
}

BSTR DataWork::convertStringToBSTR(std::string _value){
	return _com_util::ConvertStringToBSTR(_value.c_str());
}

