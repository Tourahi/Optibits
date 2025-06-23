#ifndef OPTI_MODULE_H
#define OPTI_MODULE_H

// OPTI
#include "Exception.h"
#include "Knot.h"

namespace opti
{
  class Module : public Knot
  {
    public:
      static opti::Type type;

      enum ModuleType
      {
        M_UNKNOWN = -1,
        M_TIMER,
        M_MAX_ENUM
      };

      Module(ModuleType moduleType, const char *name);
      virtual ~Module();

      /**
      * Gets the base type of the module.
      **/
      ModuleType getModuleType() const { return moduleType; }

      /**
       * Gets the name of the module. This is used in case of errors
       * and other messages.
       *
       * @return The full name of the module, eg. opti.graphics.opengl.
       **/
      const char *getName() const { return name.c_str(); }

      /**
       * Retrieve module instance from internal registry. May return NULL
       * if module not registered.
       * @param name The full name of the module.
       * @return Module instance or NULL if the module is not registered.
       */
      static Module *getInstance(const std::string &name);

      /**
       * Retrieve module instance from the internal registry using the base
       * module type. May return null if the module is not registered.
       * @param type The base type of the module.
       **/
      template <typename T>
      static T *getInstance(ModuleType type)
      {
          return type != M_UNKNOWN ? (T *) instances[type] : nullptr;
      }

    private:
      static void registerInstance(Module *instance);

      ModuleType moduleType;
      std::string name;

      static Module *instances[M_MAX_ENUM];

  };
}

#endif
