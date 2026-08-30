#pragma once

#include "../core/Station.h"

class Component
{
    public:
    virtual void solve(
        const Station& inlet, 
        Station& outlet) = 0;
    
};