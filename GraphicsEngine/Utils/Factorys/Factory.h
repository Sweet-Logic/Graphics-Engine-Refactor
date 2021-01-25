#ifndef _FACTORY_H_
#define _FACTORY_H_

// T is the interface that is used
template <class T>
class Factory
{
    Factory() {};
    ~Factory() {};

public:
    T Create() = 0;
};


#endif // !_FACTORY_H_