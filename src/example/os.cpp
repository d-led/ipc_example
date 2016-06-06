#include "os.h"

bool os::windows() {
#if defined(_WINNT) || defined(_WIN32)
    return true;
#else
    return false;
#endif
}
