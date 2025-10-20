#ifndef SIGLETON_H
#define SIGLETON_H

#include <memory>
#include <mutex>

template <typename T>
class Singleton{
private:
    static std::shared_ptr<T> instance_;
    static std::once_flag flag;
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
public:
    static std::shared_ptr<T> instance();
};

template <typename T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

template <typename T>
std::once_flag Singleton<T>::flag;

template<typename T>
std::shared_ptr<T> Singleton<T>::instance()
{
    std::call_once(flag, [](){
        if(!instance_){
            instance_ = std::shared_ptr<T>(new T);
        }
    });
    return instance_;
}

#endif // SIGLETON_H
