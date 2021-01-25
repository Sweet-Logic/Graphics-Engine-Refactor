#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <Windows.h>
#include "../utils/Singleton.h"
#include "../Utils/SystemTypes.h"

template <class T>
class System : public Singleton<T>
{
    E_SYSTEM_TYPE m_systemType = E_SYSTEM_TYPE::E_None;
public:
    virtual HRESULT Initialise() = 0;
    virtual void Update() = 0;

    virtual void Release() = 0;
};

#endif //_SYSTEM_H_