#ifndef _MANAGER_H_
#define _MANAGER_H_

struct Manager
{
    virtual void Initialise() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Release() = 0;
};

#endif //!_MANAGER_H_