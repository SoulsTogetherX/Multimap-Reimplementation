#ifndef __MULTI_MAP_CUSTOM_HEADER___
#define __MULTI_MAP_CUSTOM_HEADER___

#include <cstddef>
#include <utility>


template<typename K, typename D>
class MultiMapCustom {
    enum NODE_COLOR {
        BLACK = false,
        RED = true
    };

    private:
        /* Tree Node Definition */
        class TreeNode {
            private:
                size_t descendants;
                K key;
                D data;
                NODE_COLOR color;

                TreeNode *left, *right, *parent;
            public:
                TreeNode(K, D);
        };
        static constexpr size_t NODE_SIZE = sizeof(TreeNode);
    
    private:
        /* Forward Iterator Definition */
        class Forwards_Iterator {

        };
        /* Backward Iterator Definition */
        class Backwards_Iterator {

        };

    private:
        /* MultiMapCustom Helper Method Definitions */
        void left_rotate(const TreeNode *);
        void right_rotate(const TreeNode *);

        void insert_node(const TreeNode *);
        void delete_node(const TreeNode *);

    private:
        /* MultiMapCustom Private Variable Definitions */
        size_t tree_size;
        TreeNode *root;
    
    public:
        /* MultiMapCustom Constructor/Destructor Definitions */
        MultiMapCustom();
        ~MultiMapCustom();

    public:
        /* MultiMapCustom Capacity Method Definitions */
        size_t is_empty() const;
        size_t size() const;
    
    public:
        /* MultiMapCustom Iterator Method Definitions */
    
    public:
        /* MultiMapCustom Modifiers Method Definitions */
    
    public:
        /* MultiMapCustom Operations Method Definitions */
};

#endif
