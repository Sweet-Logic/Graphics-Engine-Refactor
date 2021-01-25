#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <type_traits>
// Code from user Martin York (12/09/2020): https://stackoverflow.com/questions/86582/singleton-how-should-it-be-used

template <class T>
class Singleton
{
protected:
    Singleton() {};
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;
public:
    static T& GetInstance()
    {
		
		static_assert(std::is_base_of<Singleton, T>::value, "The base class provided is not a singleton"); // Assert if the template class is a singleton
        static T instance;

        return instance;
    }
};

#endif // _SINGLETON_H_