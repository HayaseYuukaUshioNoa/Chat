#pragma once

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

    template<typename... Args>
    static std::shared_ptr<T> instance(Args &&... args);
};

template<typename T>
template<typename... Args>
std::shared_ptr<T> Singleton<T>::instance(Args &&... args)
{
    std::call_once(flag_, [](Args &&... args) {
        if (!instance_) {
            instance_ = std::shared_ptr<T>(new T(std::forward<Args>(args)...));
        }
    }, std::forward<Args>(args)...);
    return instance_;
}

template<typename T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

template<typename T>
std::once_flag Singleton<T>::flag_;