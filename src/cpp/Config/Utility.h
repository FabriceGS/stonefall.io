//
// Created by David Oyeka on 8/3/18.
//

#ifndef STONEFALL_UTILITY_H
#define STONEFALL_UTILITY_H

#include <memory>
#include <math.h>
#include <unordered_map>
#include <unordered_set>

namespace util {
    template <typename T>
    bool isUninitialized(std::weak_ptr<T> const &weak) {
        using wt = std::weak_ptr<T>;
        return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
    }

    inline int multiplyByScoreLogistically(int cost, int score) {
        double exponent = std::exp((0.0001 * score));
        double newMultiplier = (((10 * 1.001) * exponent)
                                / (10 + 1.001 * (exponent) - 1));
        double newCost = newMultiplier * cost;
        int intCost = static_cast<int>(std::round(newCost));
        return std::round((intCost + 99) / 100) * 100;
    }

    /*
     * High performing pointer hash for varying block sizes.
     * https://stackoverflow.com/questions/20953390/what-is-the-fastest-hash-function-for-pointers
     */
    template<typename T>
    struct HighPerformanceHash {
        size_t operator()(const T* val) const {
            static const auto shift = (size_t)log2(1 + sizeof(T));
            return (size_t)(val) >> shift;
        }
    };
}

namespace ptr_dref_hash_util {
    template<typename T>
    inline size_t hash(const T& v) {
        return std::hash<T>()(v);
    }

    /* hash based off of a pointer dereference */
    template<typename T>
    struct PointerDereferenceHash {
        inline size_t operator()(const T& pointer) const {
            return hash(*pointer);
            }
    };

    /* equality based off of pointer dereference */
    template<typename T>
    struct PointerDereferenceEqualTo {
        inline bool operator()(const T& lhs, const T& rhs) const {
            return *lhs == *rhs;
        }
    };

    template<typename K,typename V>
    using unordered_pointer_dereference_map = std::unordered_map<K,V,PointerDereferenceHash<K>,PointerDereferenceEqualTo<K>>;

    template<typename K>
    using unordered_pointer_dereference_set = std::unordered_set<K, PointerDereferenceHash<K>, PointerDereferenceEqualTo<K>>;
}

#endif //STONEFALL_UTILITY_H
