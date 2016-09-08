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

#include <ht_vkapplication.h>
#include <ht_vkdevice.h>
#include <ht_vkswapchain.h>

#include <ht_glfwwindow.h>
#include <ht_input_singleton.h>
#include <ht_debug.h>

using namespace Hatchit::Graphics;
using namespace Hatchit::Graphics::Vulkan;
using namespace Hatchit::Game;

int main(int argc, char* argv[])
{
    Input::Initialize();

    WindowParams wp = {};
    wp.x = 0;
    wp.y = 0;
    wp.width = 800;
    wp.height = 600;
    wp.debugWindowEvents = false;
    wp.displayFPS = false;
    wp.displayMouse = false;
    wp.title = "Application Test";

    GLFWWindow* window = new GLFWWindow(wp);
    if (!window->VInitialize())
        return -1;

    VKApplication app;
    if (!app.Initialize(window->VNativeWindowHandle(), window->VNativeDisplayHandle()))
        return -1;

    VKDevice device;
    if (!device.Initialize(app, 0))
        return -1;

    VKSwapChain swapChain;
    if (!swapChain.Initialize(app, device))
        return -1;

    

    while (window->VIsRunning())
    {
        window->VPollEvents();
    }

    Input::DeInitialize();

    return 0;
}