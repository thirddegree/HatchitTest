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

#include <ht_winrt_filesystem.h>
#include <ht_debug.h>
#include <ht_os.h>

#include <ppltasks.h>

using namespace Hatchit;
using namespace Hatchit::Core;

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	HT_DEBUG_PRINTF("[LOCAL_FOLDER] : %s\n", WinRT::Directory::LocalFolder());
	HT_DEBUG_PRINTF("[LOCAL_CACHE_FOLDER] : %s\n", WinRT::Directory::LocalCacheFolder());
	HT_DEBUG_PRINTF("[ROAMING_FOLDER] : %s\n", WinRT::Directory::RoamingFolder());
	HT_DEBUG_PRINTF("[SHARED_LOCAL_FOLDER] : %s\n", WinRT::Directory::SharedLocalFolder());
	HT_DEBUG_PRINTF("[TEMP_FOLDER] : %s\n", WinRT::Directory::TemporaryFolder());

	Debug::CloseOutputStream();
	
	return 0;
}
