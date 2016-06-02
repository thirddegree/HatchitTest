/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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
#include <ht_file.h>
#include <HatchitTest.h>
#include <ht_os.h>
#include <ht_http.h>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Game;
using namespace Hatchit::Network;

int main(int argc, char* argv[])
{
    bool success = Network::Initialize();
    if (!success)
    {
        HT_ERROR_PRINTF("Failed to initialize Network subsystem\n");
    }
    else
    {
        HTTPResponse response;
        success = HTTP::GET("http://catfacts-api.appspot.com/api/facts", response);
        if (success)
            HT_DEBUG_PRINTF(response.GetBody());
        else
            HT_ERROR_PRINTF("Failed to get cat facts :(\n");
    }

    INISettings settings;

    File file;
    try
    {
        file.Open(os_exec_dir() + "HatchitTest.ini", File::FileMode::ReadText);
        settings.Load(file);
    }
    catch (std::exception& e)
    {
        HT_ERROR_PRINTF("%s\n", e.what());
        HT_ERROR_PRINTF("Error in loading .ini file for: %s\nUsing defaults.\n", HT_SFY_(HatchitTest_TITLE));
    }

    Application app(&settings);


    return app.Run();
}
