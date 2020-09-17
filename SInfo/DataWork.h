#pragma once
#include <string>
#include <Wbemidl.h>
#include <comutil.h>
#include <iostream>
#include <map>
#include "Data.h"


class DataWork{

private:



public:

	void setDataBSTR(std::string _key, BSTR _bstr, Data *_data);

	void setDataSAFEARRAY_string(HRESULT hr, std::string _key, SAFEARRAY* _safearray, Data* _data);

	void setDataSAFEARRAY_uint(HRESULT hr, std::string _key, SAFEARRAY* _safearray, Data* _data);

	std::string getData(std::string _key, Data *_data);

};

