#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include "../include/interface.h"

class MenuInterface : Interface
{
public:
    MenuInterface();

    void run() override;

    ~MenuInterface();
};

#endif
