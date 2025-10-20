//
// Created by tom on 25-10-15.
//

#include "ScopeExit.h"

ScopeExit::ScopeExit(std::function<void()> &&f) : func_(std::move(f)), on_destruction_(true)
{

}

ScopeExit::~ScopeExit()
{
    if (on_destruction_) {
        if (func_) {
            func_();
        }
    }
}

void ScopeExit::release()
{
    on_destruction_ = false;
}