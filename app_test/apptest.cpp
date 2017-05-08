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

#include <SDL.h>
#include <ht_winrt_filesystem.h>
#include <ht_debug.h>
#include <ht_os.h>

using namespace Hatchit;
using namespace Hatchit::Core;

int
main(int argc, char *argv[])
{
    HT_DEBUG_PRINTF("[LOCAL_FOLDER] : %s\n", WinRT::Directory::LocalFolder());
    HT_DEBUG_PRINTF("[LOCAL_CACHE_FOLDER] : %s\n", WinRT::Directory::LocalCacheFolder());
    HT_DEBUG_PRINTF("[ROAMING_FOLDER] : %s\n", WinRT::Directory::RoamingFolder());
    HT_DEBUG_PRINTF("[SHARED_LOCAL_FOLDER] : %s\n", WinRT::Directory::SharedLocalFolder());
    HT_DEBUG_PRINTF("[TEMP_FOLDER] : %s\n", WinRT::Directory::TemporaryFolder());
    
    Debug::CloseOutputStream();

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

                                           // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_RESIZABLE                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    //SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    bool running = true;
    while (running)
    {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_WINDOWEVENT:
        {
            SDL_WindowEvent e = event.window;
            switch (e.type)
            {
            case SDL_WINDOWEVENT_CLOSE:
                running = false;
                break;
            }
        }
        break;

        default:
            break;
        }
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}