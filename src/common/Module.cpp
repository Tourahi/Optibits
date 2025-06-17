// OPTI
#include "Module.h"
#include "Exception.h"

// std
#include <map>
#include <utility>
#include <string>

namespace
{
  typedef std::map<std::string, opti::Module*> ModuleRegistry;

  ModuleRegistry *registry = nullptr;

  ModuleRegistry &registryInstance()
  {
    if (!registry)
      registry = new ModuleRegistry;

    return *registry;
  }

  void freeEmptyRegistry()
  {
    if (registry && registry->empty())
    {
      delete registry;
      registry = nullptr;
    }
  }
} // anon namespace

namespace opti
{

  opti::Type Module::type("Module", &Knot::type);
  Module *Module::instances[] = {};

  Module::Module(Module::ModuleType moduleType, const char *name)
	: moduleType(moduleType)
	, name(name)
  {
    registerInstance(this);
  }

  Module::~Module()
  {
    ModuleRegistry &registry = registryInstance();

    // We can't use the overridden Module::getName() in this destructor.
    for (auto it = registry.begin(); it != registry.end(); ++it)
    {
      if (it->second == this)
      {
        registry.erase(it);
        break;
      }
	}

    for (int i = 0; i < (int) M_MAX_ENUM; i++)
	{
      if (instances[i] == this)
        instances[i] = nullptr;
	}

    freeEmptyRegistry();
  }

  Module *Module::getInstance(const std::string &name)
  {
    ModuleRegistry &registry = registryInstance();

    auto it = registry.find(name);

    if (registry.end() == it)
      return nullptr;

    return it->second;
  }

  void Module::registerInstance(Module *instance)
  {
    if (instance == nullptr)
      throw Exception("[Module::registerInstance] Module instance is null.");

    std::string name(instance->getName());

    ModuleRegistry &registry = registryInstance();

    auto it = registry.find(name);

    if (it != registry.end())
    {
      if (it->second == instance)
        return;
      throw Exception("[Module::registerInstance] Module %s already registered!", instance->getName());
    }

    registry.insert(make_pair(name, instance));

    ModuleType mtype = instance->getModuleType();

    if (mtype != M_UNKNOWN)
	{
      if (instances[mtype] != nullptr)
      {
        printf("[Module::registerInstance] Warning: overwriting module instance %s with new instance %s\n",
          instances[mtype]->getName(), instance->getName());
      }

      instances[mtype] = instance;
	}
  }
}
