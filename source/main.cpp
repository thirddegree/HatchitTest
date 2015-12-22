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

#include <ht_debug.h>
#include <ht_version.h>
#include <ht_file.h>

using namespace Hatchit;
using namespace Hatchit::Core;

int main(int argc, char* argv[])
{
    DebugPrintF("Hatchit Engine: v%d.%d.%d\n",
                                HatchitEngine_VERSION_MAJOR,
                                HatchitEngine_VERSION_MINOR,
                                HatchitEngine_VERSION_BUILD);

    File file;
    try
    {
        file.Open("tet.txt", FileMode::ReadText);
    }
    catch (FileException& e)
    {
        DebugPrintF("%s\n", e.what());
    }

    return 0;
}
