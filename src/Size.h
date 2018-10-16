#ifndef SIZE_H
#define SIZE_H

#include <stdint.h>

namespace Codingfield {
  namespace UI {
    struct Size {
      Size() : width{0}, height{0} {}
      Size(int32_t width, int32_t height) : width{width}, height{height} {}
      int32_t width;
      int32_t height;
    };
  }
}

#endif //SIZE_H