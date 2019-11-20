#include <iostream>
#include "CmdArgsMgr.h"

CmdArgsMgr CmdArgsMgr::instance;

using namespace std;

int main()
{
    CmdArgsMgr &mgr = CmdArgsMgr::manager();
    return 0;
}
