//
// Created by tom on 25-10-2.
//

#ifndef GATESERVER_SINGLETON_H
#define GATESERVER_SINGLETON_H

#include <mutex>
#include <memory>
#include <utility>

template<typename T>
class Singleton {
private:
    static std::shared_ptr<T> instance_;
    static std::once_flag flag_;
protected:
    Singleton() = default;

    virtual ~Singleton() = default;

public:
    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

    static std::shared_ptr<T> instance();
};

template<typename T>
std::shared_ptr<T> Singleton<T>::instance()
{
    std::call_once(flag_, []() {
        if (!instance_) {
            instance_ = std::shared_ptr<T>(new T());
        }
    });
    return instance_;
}

template<typename T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

template<typename T>
std::once_flag Singleton<T>::flag_;


#endif //GATESERVER_SINGLETON_H