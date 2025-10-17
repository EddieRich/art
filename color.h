#ifndef __COLOR__
#define __COLOR__

#include <iostream>
#include "vec3.h"

using color = vec3;

std::ostream& operator<<(std::ostream& out, color& color);

#endif // __COLOR__
