#pragma once

#include <parallel_hashmap/phmap.h> // Incluye correctamente parallel-hashmap

namespace stdext {

    // Alias para utilizar flat_hash_map de phmap
    template <class Key, class Value>
    using HashMap = phmap::flat_hash_map<Key, Value>;

    // Implementación de funciones hash
    inline size_t hash_int(uint64_t x) noexcept {
        x ^= x >> 33U;
        x *= UINT64_C(0xff51afd7ed558ccd);
        x ^= x >> 33U;
        return x;
    }

    // Combina dos valores hash en uno solo
    inline void hash_union(size_t& seed, const size_t h) {
        seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    // Combina un valor hash con otro utilizando hash_union
    template <class T>
    void hash_combine(size_t& seed, const T& v) {
        std::hash<T> hasher;
        hash_union(seed, hasher(v));
    }

}
