#include "DataWork.h"


void DataWork::setDataBSTR(string _key, BSTR _bstr){

	if (_bstr) {

		string key = _key + to_string(data_count);

	    data.bstr.insert(make_pair(key, _com_util::ConvertBSTRToString(_bstr)));

	}
}

void DataWork::setDataLong(string _key, UINT _uint) {

	string key = _key + to_string(data_count);

	data.longer.insert(make_pair(key, _uint));

}

string DataWork::getDataString(string _key) {

	string s = "unavailable";


	if (data.bstr.find(_key) != data.bstr.end()) {

		s = data.bstr[_key];

	} else {
		return s;
	}

	return s;
}

long long DataWork::getDataLongLong(string _key) {

	long long s = 0;

	if (data.longer.find(_key) != data.longer.end()) {

		s = data.longer[_key];

	} else {
		return s;
	}

	return s;
}

long  DataWork::getDataLong(string _key) {

	long  s = -1;

	if (data.longer.find(_key) != data.longer.end()) {

		s = data.longer[_key];

	} else {
		return s;
	}

	return s;
}

long long DataWork::uint64ToLongLong(string _value){
	long long s = 0;
	try {
		s = stoll(_value);
	} catch (invalid_argument iaex) {

	}
	return s;
}

BSTR DataWork::convertStringToBSTR(string _value){
	return _com_util::ConvertStringToBSTR(_value.c_str());
}

