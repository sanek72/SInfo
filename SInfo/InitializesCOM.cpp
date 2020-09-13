#include "InitializesCOM.h"

//https://docs.microsoft.com/ru-ru/windows/win32/wmisdk/example-creating-a-wmi-application?redirectedfrom=MSDN
InitializesCOM::InitializesCOM(std::string _objectPath, std::string _wql, std::vector< std::string > _properties) {

    c.objectPath = _objectPath;
    c.wql = _wql;
    c.properties = _properties;
}

    bool InitializesCOM::Initialize(std::vector< std::string > &_value) {

    if (c.properties.size() == 0) {
        return false;
    }
    
    HRESULT hresult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    //HRESULT hresult = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (FAILED(hresult)) {
        std::cout << "Failed to initialize COM library. " << std::endl;
        return false;
    }
    
    hresult = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

    if (FAILED(hresult)) {
        std::cout << "Failed to initialize security. " << std::endl;
        return false;
    }
    
    IWbemLocator* pLocator = NULL;

    hresult = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_ALL, IID_IWbemLocator, (LPVOID*)&pLocator);
    if (FAILED(hresult)) {
        std::cout << "Failed to create IWbemLocator object. " << std::endl;
        ::CoUninitialize();
        return false;
    }
    
    IWbemServices* pService = NULL;

    _bstr_t objectPath = c.objectPath.c_str();

    hresult = pLocator->ConnectServer(objectPath, NULL, NULL, NULL, NULL, NULL, NULL, &pService);

    if (hresult != S_OK) {
        std::cout << "The COM library is already initialized on this thread. " << std::endl;
        ::CoUninitialize();
        return false;

    }
    
    IEnumWbemClassObject* pEnum;

    _bstr_t wql = c.wql.c_str();

    hresult = pService->ExecQuery(_bstr_t(L"WQL"), wql, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, 0, &pEnum);
    if (FAILED(hresult)) {
        std::cout << "Query for operating system name failed." << std::endl;
        pLocator->Release();
        ::CoUninitialize();
        return false;
    }
    
    ULONG uReturn = 0;
    IWbemClassObject* pObject = NULL;
    
    while (pEnum) {

        hresult = pEnum->Next(WBEM_INFINITE, 1, &pObject, &uReturn);

        if (FAILED(hresult)) {
            
            pLocator->Release();
            pService->Release();
            pEnum->Release();
            ::CoUninitialize();
            return false;

        }

        if (0 == uReturn) {

            break;
        
        }

        BSTR temp;
        VARIANT v;

        VariantInit(&v);
        
        size_t len = c.properties.size();


        for (size_t i = 0; i < len; ++i) {

            temp = _com_util::ConvertStringToBSTR(c.properties[i].c_str());

            hresult = pObject->Get(temp, NULL, &v, NULL, NULL);

            if (FAILED(hresult)) {
                
                _value.push_back("unavailable");
                VariantClear(&v);
             
            }else if (v.bstrVal == NULL) {

                _value.push_back("unavailable");
                VariantClear(&v);

            } else {

                int vType = v.vt;

 //               std::cout << c.wql + "p ropertie[" + c.properties[i] + "] = " + " The VARTYPE " + std::to_string(vType)  << std::endl;

                switch (vType) {

                case VBSTRING_TYPE:

                    _value.push_back(_com_util::ConvertBSTRToString(v.bstrVal));
                    VariantClear(&v);
                    break;

                case VBARRAY_TYPE + VBSTRING_TYPE:

                    _value.push_back(getArrayValues_(hresult, v.parray, VBSTRING_TYPE));
                    VariantClear(&v);
                    break;

                case VBARRAY_TYPE + VBLONG_TYPE:

                    _value.push_back(getArrayValues_(hresult, v.parray, VBLONG_TYPE));
                    VariantClear(&v);
                    break;

                case VBBOOLEAN_TYPE:

                    _value.push_back(((v.boolVal != VARIANT_FALSE) ? "true" : "fasle"));
                    VariantClear(&v);
                    break;

                case VBINTEGER_TYPE:

                    _value.push_back(std::to_string(v.intVal));
                    VariantClear(&v);
                    break;

                case VBBYTE_TYPE:

                    _value.push_back(std::to_string(v.uintVal));
                    VariantClear(&v);
                    break;

                case VBLONG_TYPE:

                    _value.push_back(std::to_string(v.uintVal));
                    VariantClear(&v);
                    break;

                case VTNULL_TYPE:

                    _value.push_back("unavailable");
                    VariantClear(&v);
                    break;

                default:
                    std::cout << typeid(InitializesCOM).name() << "p ropertie[" + c.properties[i] + "] = " "The VARTYPE " + std::to_string(vType) + " is unknown." << std::endl;
                    _value.push_back("unavailable");
                    VariantClear(&v);
                    break;
                }
            }

        }
      
    }

    pLocator->Release();
    pService->Release();
    pEnum->Release();
    pObject->Release();
    ::CoUninitialize();

    return true;

}

std::string InitializesCOM::getArrayValues_(HRESULT hr, SAFEARRAY* parray, int vType) {

    std::string s;
    BSTR* temp;
    hr = SafeArrayAccessData(parray, (void**)&temp); 

    if (SUCCEEDED(hr)){

        long lowerBound, upperBound;  
        SafeArrayGetLBound(parray, 1, &lowerBound);
        SafeArrayGetUBound(parray, 1, &upperBound);

        long cnt_elements = upperBound - lowerBound + 1;
        BSTR v;

        for (int i = 0; i < cnt_elements; ++i){  

             v = temp[i];

            if (vType == VBSTRING_TYPE) {

                    s +=  _com_util::ConvertBSTRToString(v);
                    s += "|";

            }
            else if (vType == VBLONG_TYPE) {

                    s += std::to_string((UINT)v);// TODO: 
                    s += "|";               

            }


        }

        SafeArrayUnaccessData(parray);
 //       SafeArrayDestroy(parray);
    } else {

        s = " unavailable";

    }
    return s;
}


