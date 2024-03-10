#include <Optibits/Platform.hpp>
#include <Optibits/Version.hpp>
#include <string>

using namespace std;

const string Optibits::VERSION = to_string(OPTIBITS_MAJOR_VERSION) + '.' +
                                 to_string(OPTIBITS_MINOR_VERSION) + '.' +
                                 to_string(OPTIBITS_POINT_VERSION);
