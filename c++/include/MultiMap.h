#ifndef __MULTI_MAP_CUSTOM_HEADER___
#define __MULTI_MAP_CUSTOM_HEADER___

#include <utility>


template<typename K, typename D>
class MultiMapCustom {
    #define __MIN_DEFAULT_SIZE__ 0
    
    using Pair = std::pair<K,D>;

    private:
        /* Tree Node Definition */
        class TreeNode {
            private:
                size_t index;
                K key;
                D data;
            public:

        };
    
    private:
        /* Forward Iterator Definition */
        class Forwards_Iterator {

        };
        /* Backward Iterator Definition */
        class Backwards_Iterator {

        };
    
    private:
        /* MultiMapCustom Private Methods Definition */
        void resize_memory(size_t new_size) {

        }
    private:
        /* MultiMapCustom Private Variable Definition */
        size_t size = 0, memory_size = 8;
        bool has_root;

        TreeNode *tree_memory;
    
    public:
        /* MultiMapCustom Public Methods Definition */

};

#endif
