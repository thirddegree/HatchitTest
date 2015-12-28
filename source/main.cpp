/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/


#include <ht_application.h>
#include <ht_debug.h>
#include <HatchitTest.h>
using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Game;

int main(int argc, char* argv[])
{
    INIReader settings;

    File file;
    try
    {
        file.Open("HatchitTest.ini", FileMode::ReadText);
        settings.Load(&file);
    }
    catch (std::exception& e)
    {
        DebugPrintF("%s\n", e.what());
        DebugPrintF("No .ini file found for: %s\nUsing defaults.\n", HT_SFY_(HatchitTest_TITLE));
    }

    Application app(&settings);


    return app.Run();
}