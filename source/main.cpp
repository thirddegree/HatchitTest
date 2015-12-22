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
#include <ht_inireader.h>
#include <ht_iniwriter.h>

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
        file.Open("test2.ini", FileMode::WriteText);

        INIWriter writer;
        writer.SetValue("CHARACTER", "iStrength", 600);
        writer.SetValue("CHARACTER", "bCanSwim", true);
        writer.SetValue("CHARACTER", "fScale", 2.5);
        writer.SetValue("CHARACTER", "dHealth", 35.5);
        
        writer.Write(&file);

        file.Close();

        file.Open("test2.ini", FileMode::ReadText);

        INIReader reader;
        reader.Load(&file);

        bool    canSwim = reader.GetValue("CHARACTER", "bCanSwim", false);
        int     strength = reader.GetValue("CHARACTER", "iStrength", 0);
        float   scale = reader.GetValue("CHARACTER", "fScale", 0.0f);
        double  health = reader.GetValue("CHARACTER", "dHealth", 0.0);

        DebugPrintF("CanSwim: %d\n", canSwim);
        DebugPrintF("Strength: %d\n", strength);
        DebugPrintF("Scale: %.2f\n", scale);
        DebugPrintF("Health: %.2f\n", health);
    }
    catch (std::exception& e)
    {
        DebugPrintF("%s\n", e.what());
    }


    return 0;
}
