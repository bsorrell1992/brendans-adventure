#include "utilities.h"

namespace utils {
    int sgn(int x) {
        if (x == 0) return 0;

        return (x < 0) ? -1 : 1;
    }
}