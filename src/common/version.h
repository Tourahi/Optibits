#ifndef OPTI_VERSION_H
#define OPTI_VERSION_H

namespace opti
{

// Version
#define OPTI_VERSION_STRING "0.1"
static const int VERSION_MAJ = 0;
static const int VERSION_MIN = 1;
static const int VERSION_REV = 0;

static const char *VERSION = OPTI_VERSION_STRING;
static const char *VERSION_COMPATIBILITY[] = {VERSION, 0};
static const char *VERSION_CODENAME = "fearless learner";

} // opti


#endif // OPTI_VERSION_H
