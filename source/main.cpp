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
#include <ht_timer.h>
#include <HatchitTest.h>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Game;

int main(int argc, char* argv[])
{
    Timer timer;

    timer.Reset();

    timer.Start();

    for (int i = 0; i < 10000000; i++)
    {
        DebugPrintF("%d\n", i);
    }

    timer.Stop();

    DebugPrintF("TotalTime: %.2f\n", timer.TotalTime());

    for (int i = 0; i < 10000000; i++)
    {
        DebugPrintF("%d\n", i);
    }

    timer.Start();

    DebugPrintF("PausedTime: %.2f\n", timer.PausedTime());

    return 0;
}
