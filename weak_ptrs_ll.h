#include <memory>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
std::ostream & operator<<(std::ostream & os, std::shared_ptr<T> & p) {
    return os << p.get() << " shared_ptr count: [" << p.use_count() << "]" ;
}

template <typename T>
std::ostream & operator<<(std::ostream & os, std::weak_ptr<T> & p) {
    T * raw = nullptr;
    {
    auto sp = p.lock();
    raw = sp.get();
    }
    return os << raw
              << "weak_ptr to shared_ptr count: [" << p.use_count() << "]" ;
}

struct LinkedList {
    public:
        struct Node {
            int data;
            shared_ptr<Node> next;
            Node() {};
            Node(Node * node) : data{node->data}, next{node->next} { };
            Node(int data, shared_ptr<Node> ptr) : data{data}, next{ptr} {};
        };
        struct CopyNode {
            weak_ptr<Node> weak_node_ptr;
            CopyNode() {};
        };
        /* Builds the linked list of shared_ptrs */
        void build_node_list(int k);
        /* Builds weak_ptrs to linked-list nodes */
        void build_copyNodes_weak_ptrs();
        /* Deletes the linked list of shared_ptrs */
        void delete_node_shared_ptr_list();
        /* Prints a linked list of shared_ptrs */
        void print_node_list_shared_ptrs();
        /* Prints a linked list of weak_ptrs */
        void print_node_array_weak_ptrs();

        int get_data_at_idx(int idx);
        
        LinkedList();
        ~LinkedList();

    private:
        shared_ptr<Node> root;
        vector<CopyNode> copy_node_array;
        int nodeCount;
};