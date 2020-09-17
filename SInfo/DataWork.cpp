#include "DataWork.h"


void DataWork::setDataBSTR(std::string _key, BSTR _bstr, Data *_data){

	//if (_data->data_count == 0) {
	//	_data->data_count++;
	//}

	std::string key = _key + std::to_string(_data->data_count);

	if (_data->bstr.find(key) != _data->bstr.end()) {

		_data->data_count++;

		key = _key + std::to_string(_data->data_count);

		_data->bstr.insert(make_pair(key, _bstr));

	} else {

		_data->bstr.insert(make_pair(key, _bstr));

	}	

}

void DataWork::setDataSAFEARRAY_string(HRESULT hr, std::string _key, SAFEARRAY* _safearray, Data* _data){

    std::string s;
    BSTR* temp;
    hr = SafeArrayAccessData(_safearray, (void**)&temp);

    if (SUCCEEDED(hr)) {

        long lowerBound, upperBound;
        SafeArrayGetLBound(_safearray, 1, &lowerBound);
        SafeArrayGetUBound(_safearray, 1, &upperBound);

        long cnt_elements = upperBound - lowerBound + 1;
        BSTR v;

        for (int i = 0; i < cnt_elements; ++i) {

			v = temp[i];

			s += _com_util::ConvertBSTRToString(v);

        }

        SafeArrayUnaccessData(_safearray);

    } else {

        s = " unavailable";

    }

	std::string key = _key + std::to_string(_data->data_count);

	if (_data->array_string.find(key) != _data->array_string.end()) {

		_data->data_count++;

		key = _key + std::to_string(_data->data_count);

		_data->array_string.insert(make_pair(key, s));

	}
	else {

		_data->array_string.insert(make_pair(key, s));

	}

}

void DataWork::setDataSAFEARRAY_uint(HRESULT hr, std::string _key, SAFEARRAY* _safearray, Data* _data){
}

std::string DataWork::getData(std::string _key, Data *_data) {

	std::string s = "unavailable";

	//std::string  key = _key + std::to_string(_data->data_count);
	//std::cout << "getData " << _key << std::endl;

	if (_data->bstr.find(_key) != _data->bstr.end()) {

		s = _com_util::ConvertBSTRToString(_data->bstr[_key]);
	}

	if (_data->array_string.find(_key) != _data->array_string.end()) {

		s = _data->array_string[_key];
	}

	return s;
}

