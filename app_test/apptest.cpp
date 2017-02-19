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
#include <ht_vkcommandpool.h>
#include <ht_vkdepthstencil.h>
#include <ht_vkrenderpass.h>
#include <ht_vkcommandbuffer.h>
#include <ht_vksemaphore.h>
#include <ht_vkfence.h>

#include <ht_glfwwindow.h>
#include <ht_input_singleton.h>
#include <ht_debug.h>

#include <ht_fileresource.h>

#include <array>

using namespace Hatchit::Graphics;
using namespace Hatchit::Graphics::Vulkan;
using namespace Hatchit::Game;

VKApplication* g_Application;
VKDevice*      g_Device;
VKSwapChain*   g_SwapChain;
VKCommandPool* g_CommandPool;
VKDepthStencil* g_DepthStencil;
VKRenderPass*  g_RenderPass;

void cleanup()
{
    if (g_RenderPass)
        delete g_RenderPass;
    if (g_DepthStencil)
        delete g_DepthStencil;
    if (g_CommandPool)
        delete g_CommandPool;
    if (g_SwapChain)
        delete g_SwapChain;
    if (g_Device)
        delete g_Device;
    if (g_Application)
        delete g_Application;
}

int main(int argc, char* argv[])
{
    std::atexit(cleanup);

    /**
     * Vulkan setup:
     *
     * Application instance
     * Swapchain creation
     *
     */
    g_Application = nullptr;
    g_Device = nullptr;
    g_SwapChain = nullptr;
    g_CommandPool = nullptr;
    g_DepthStencil = nullptr;
    g_RenderPass = nullptr;


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
    if (!window->Initialize())
        return -1;

    g_Application = new VKApplication;
    if (!g_Application->Initialize(window->NativeWindowHandle(), window->NativeDisplayHandle()))
        return -1;

    g_Device = new VKDevice;
    if (!g_Device->Initialize(*g_Application, 0))
        return -1;

    g_SwapChain = new VKSwapChain;
    if (!g_SwapChain->Initialize(600, 800, *g_Application, *g_Device))
        return -1;

    g_CommandPool = new VKCommandPool;
    if (!g_CommandPool->Initialize(*g_Device))
        return -1;

    g_DepthStencil = new VKDepthStencil;
    if (!g_DepthStencil->Initialize(*g_Device, 800, 600))
        return -1;

    g_RenderPass = new VKRenderPass;
    if (!g_RenderPass->Initialize(*g_Device, *g_SwapChain))
        return -1;

    while (window->IsRunning())
    {
        window->PollEvents();
    }

    Input::DeInitialize();


    return 0;
}
