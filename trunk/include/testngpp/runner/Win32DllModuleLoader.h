
#ifndef __TESTNGPP_WIN32_DLL_MODULE_LOADER_H
#define __TESTNGPP_WIN32_DLL_MODULE_LOADER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/ModuleLoader.h>


TESTNGPP_NS_START

struct Win32DllModuleLoaderImpl;

struct Win32DllModuleLoader : public ModuleLoader
{
   Win32DllModuleLoader(const SearchingPaths* searchingPaths);
   ~Win32DllModuleLoader(); 

	void load(const std::string& modulePath);

   void unload();

   void* findSymbol(const std::string& symbol);

private:

   Win32DllModuleLoaderImpl* This;
};

TESTNGPP_NS_END

#endif

