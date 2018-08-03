//
// Created by David Oyeka on 8/3/18.
//

#ifndef STONEFALL_UTILITY_H
#define STONEFALL_UTILITY_H

#include <memory>

template <typename T>
bool isUninitialized(std::weak_ptr<T> const &weak) {
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

#endif //STONEFALL_UTILITY_H
