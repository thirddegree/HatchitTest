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
#include <ht_bitmap.h>
#include <HatchitTest.h>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Image;
using namespace Hatchit::Game;

int main(int argc, char* argv[])
{
    File file;
    Bitmap* bitmap;
    try
    {
        file.Open(os_exec_dir() + "croissant.png", FileMode::ReadBinary);

        bitmap = Bitmap::Load(&file, Bitmap::Channels::RGBA);

        DebugPrintF("%d %d %d\n", bitmap->GetWidth(), bitmap->GetHeight(), bitmap->GetChannels());
    }
    catch (std::exception& e)
    {
#ifdef _DEBUG
        DebugPrintF("%s\n", e.what());
#endif
    }


    return 0;
}
