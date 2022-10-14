//
// Created by Aihua on 2020-08-13.
//

#include "RandomNumberGeneration.h"

namespace myRand {
    extern std::mt19937_64 mersenne{ static_cast<std::mt19937_64::result_type>(std::time(nullptr)) };
}