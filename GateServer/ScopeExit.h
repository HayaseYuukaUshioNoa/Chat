//
// Created by tom on 25-10-15.
//

#ifndef GATESERVER_SCOPEEXIT_H
#define GATESERVER_SCOPEEXIT_H

#include <functional>

class ScopeExit {
private:
    std::function<void()> func_;
    bool on_destruction_;
public:
    ScopeExit(std::function<void()> &&f);

    ScopeExit(const ScopeExit &) = delete;

    ScopeExit &operator=(const ScopeExit &) = delete;

    ~ScopeExit();

    void release();
};


#endif //GATESERVER_SCOPEEXIT_H
