
#include <string>
#include <dlfcn.h>

#include <testngpp/Error.h>
#include <testngpp/ExceptionKeywords.h>

#include <testngpp/runner/DLModuleLoader.h>


TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct DLModuleLoaderImpl
{
    DLModuleLoaderImpl();
    ~DLModuleLoaderImpl();

    const char* addSearchingPaths(
        const std::list<std::string>& searchingPaths);

    void load(const std::string& modulePath);
    void loadUnderPaths( \
       const std::list<std::string>& searchingPaths, \
       const std::string& modulePath);

    void unload();

    void* findSymbol(const std::string& symbol);

    void* handle;
};

////////////////////////////////////////////////////////
DLModuleLoaderImpl::DLModuleLoaderImpl()
    : handle(0)
{
}
////////////////////////////////////////////////////////
DLModuleLoaderImpl::~DLModuleLoaderImpl()
{
    if(handle != 0)
    {
        ::dlclose(handle);
        handle = 0;
    }
}

/////////////////////////////////////////////////////////////////
namespace
{
   std::string getFullPath( const std::string& path
                           , const std::string& modulePath)
   {
      std::string fullPath(path);

      if(fullPath.at(fullPath.length()-1) != '/')
      {
         fullPath += "/";
      }

      fullPath += modulePath;

      return fullPath;
   }

   void* openModule(const std::string& modulePath)
   {
      std::string module = modulePath + ".so";
      return ::dlopen(module.c_str(), RTLD_LAZY);
   }
}

/////////////////////////////////////////////////////////////////
void
DLModuleLoaderImpl::
DLModuleLoaderImpl::loadUnderPaths \
                 ( const std::list<std::string>& searchingPaths
                 , const std::string& modulePath)
{
   std::list<std::string>::const_iterator i = searchingPaths.begin();
   for(; i != searchingPaths.end(); i++)
   {
      handle = openModule(getFullPath(*i, modulePath));
      if(handle != 0)
      {
         return;
      }
   }

   handle = openModule(modulePath);
   if(handle == 0)
   {
      throw Error(::dlerror());
   }
}

////////////////////////////////////////////////////////
void
DLModuleLoaderImpl::load(const std::string& modulePath)
{
    handle = ::dlopen(modulePath.c_str(), RTLD_LAZY);
    if(handle == 0)
    {
        throw Error(::dlerror());
    }
}

////////////////////////////////////////////////////////
void
DLModuleLoaderImpl::unload()
{
    if(handle != 0)
    {
        ::dlclose(handle);
    }
}

////////////////////////////////////////////////////////
void*
DLModuleLoaderImpl::findSymbol(const std::string& symbol)
{
    if(handle == 0)
    {
        throw Error("module has not been loaded yet");
    }

    void* ptr = (void*) ::dlsym(handle, symbol.c_str());
    if(ptr == 0)
    {
        throw Error(::dlerror());
    }

    return ptr;
}

////////////////////////////////////////////////////////
DLModuleLoader::DLModuleLoader()
    : This(new DLModuleLoaderImpl())
{
}

////////////////////////////////////////////////////////
DLModuleLoader::~DLModuleLoader()
{
    delete This;
}

////////////////////////////////////////////////////////
void
DLModuleLoader::load(const std::string& modulePath)
{
    This->load(modulePath);
}

////////////////////////////////////////////////////////
void
DLModuleLoader::loadUnderPaths( \
       const std::list<std::string>& searchingPaths, \
       const std::string& modulePath)
{
    This->loadUnderPaths(searchingPaths, modulePath);
}

////////////////////////////////////////////////////////
void
DLModuleLoader::unload()
{
    This->unload();
}

////////////////////////////////////////////////////////
void*
DLModuleLoader::findSymbol(const std::string& symbol)
{
   return This->findSymbol(symbol);
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END
