
#ifndef OPTI_OPTIONAL_H
#define OPTI_OPTIONAL_H

namespace opti
{

  template <typename T>
  struct Optional
  {

    T value;
    bool hasValue;

    Optional()
      : value(T()),
        hasValue(false)
    {}

    Optional(T value)
      : value(value),
        hasValue(true)
    {}

    void set(T val)
    {
      value = val;
      hasValue = true;
    }

    T get(T defaultVal) const
    {
      return hasValue ? value : defaultVal;
    }

    void clear()
    {
      hasValue = false;
    }

  };

  typedef Optional<bool>   OptionalBool;
  typedef Optional<float>  OptionalFloat;
  typedef Optional<double> OptionalDouble;
  typedef Optional<int>    OptionalInt;

}
#endif
