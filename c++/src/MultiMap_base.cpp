#include "MultiMap.h"


template<typename K, typename D>
MultiMapCustom<K,D>::MultiMapCustom() {
}
template<typename K, typename D>
MultiMapCustom<K,D>::~MultiMapCustom() {
}


template<typename K, typename D>
size_t MultiMapCustom<K,D>::is_empty() const {
    return tree_size == 0;
}
template<typename K, typename D>
size_t MultiMapCustom<K,D>::size() const {
    return tree_size;
}
