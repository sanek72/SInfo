#include "InitializesCOM.h"


//https://docs.microsoft.com/ru-ru/windows/win32/wmisdk/example-creating-a-wmi-application?redirectedfrom=MSDN
bool InitializesCOM::Initialize(string _objectPath, string _wql, vector<string> _properties, DataWork &_dataWork){

    if (_properties.size() == 0) {
        return false;
    }

    HRESULT hresult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    //HRESULT hresult = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (FAILED(hresult)) {
        cout << "Failed to initialize COM library. " << endl;
        return false;
    }

    hresult = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

    if (FAILED(hresult)) {
        cout << "Failed to initialize security. " << endl;
        return false;
    }

    IWbemLocator* pLocator = NULL;

    hresult = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_ALL, IID_IWbemLocator, (LPVOID*)&pLocator);
    if (FAILED(hresult)) {
        cout << "Failed to create IWbemLocator object. " << endl;
        ::CoUninitialize();
        return false;
    }

    IWbemServices* pService = NULL;

    _bstr_t objectPath = _objectPath.c_str();

    hresult = pLocator->ConnectServer(objectPath, NULL, NULL, NULL, NULL, NULL, NULL, &pService);

    if (hresult != S_OK) {
        cout << "The COM library is already initialized on this thread. " << endl;
        ::CoUninitialize();
        return false;

    }

    IEnumWbemClassObject* pEnum;

    _bstr_t wql = _wql.c_str();

    hresult = pService->ExecQuery(_bstr_t(L"WQL"), wql, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, 0, &pEnum);
    if (FAILED(hresult)) {
        cout << "Query for operating system name failed." << endl;
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

        size_t len = _properties.size();

        _dataWork.data_count++;

        for (string p : _properties) {

            temp = _dataWork.convertStringToBSTR(p);

            hresult = pObject->Get(temp, NULL, &v, NULL, NULL);
            
            if(SUCCEEDED(hresult)){

                int vType = v.vt;

                switch (vType) {

                case VBSTRING_TYPE:
                    _dataWork.setDataBSTR(p,  v.bstrVal);
                    VariantClear(&v);
                    
                    break;
                //case VBARRAY_TYPE + VBSTRING_TYPE:

                //    VariantClear(&v);
                //    break;

                //case VBARRAY_TYPE + VBLONG_TYPE:


                //    VariantClear(&v);
                //    break;

                case VBBOOLEAN_TYPE:
                    _dataWork.setDataBoolean(p, v.boolVal);
                    VariantClear(&v);
                    break;

                case VBINTEGER_TYPE:

                    VariantClear(&v);
                    break;

                case VBBYTE_TYPE:

                    VariantClear(&v);
                    break;

                case VBLONG_TYPE:
                      
                    _dataWork.setDataLong(p, v.uintVal);

                    VariantClear(&v);
                    break;

                case VTNULL_TYPE:


                    VariantClear(&v);
                    break;

                default:
                    //cout << typeid(InitializesCOM).name() << "p ropertie[" + p + "] = " "The VARTYPE " + to_string(vType) + " is unknown." << endl;
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
