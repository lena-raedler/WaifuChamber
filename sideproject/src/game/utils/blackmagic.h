//
// Created by auki on 17.01.20.
//

#ifndef WAIFU_BLACKMAGIC_H
#define WAIFU_BLACKMAGIC_H


#include <type_traits>
#include <iostream>
template<typename T, typename K, class = void>
struct collide_compatible : public std::false_type {};

template<typename T, typename K>
struct collide_compatible<T,
        K,
        std::void_t<decltype(std::declval<T>().collide(std::declval<K>()))>
> : public std::true_type {};

template<typename T, typename K>
constexpr bool collide_compatible_v = collide_compatible<T, K>::value;

namespace blackmagic{
    template<typename T, typename K>
    bool collide(T t, K k) {
        if constexpr (collide_compatible_v<T, K>){
            return t.collide(k);
        }
        else if constexpr (collide_compatible_v<K, T>){
            return k.collide(t);
        }
        return false;
    }
}

#endif //WAIFU_BLACKMAGIC_H
