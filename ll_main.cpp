#include "weak_ptrs_ll.h"
#include <vector>

int main() {

    LinkedList ll;
    ll.build_node_list(6);
    ll.build_copyNodes_weak_ptrs();
    ll.print_node_list_shared_ptrs();
    ll.print_node_array_weak_ptrs();
    //cout << ll.get_data_at_idx(5) << endl;
    //ll.delete_node_shared_ptr_list();
    //ll.print_node_list_shared_ptrs();
    
    

    return 0;
}