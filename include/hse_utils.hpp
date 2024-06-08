#ifndef HSE_UTILS_HPP_
#define HSE_UTILS_HPP_
#include <SFML/Graphics.hpp>
#include <exception>
#include <stdexcept>
#include <string>
#include "hse_exceptions.hpp"
#include "hse_texture.hpp"

namespace super_hse {

bool is_level_available(int num);

static inline int all_levels = 4;

}  // namespace super_hse

#endif
