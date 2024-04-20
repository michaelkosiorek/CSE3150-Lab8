#include "weak_ptrs_ll.h"

void LinkedList::build_node_list(int k) {

    nodeCount = k;
    if (k==0) return; //nah

    shared_ptr<Node> new_root(new Node);
    root = new_root;
    root->data=0;
    new_root.reset();

    if (k==1) {
        root->next = nullptr;
        print_node_list_shared_ptrs();
        return;
    }

    shared_ptr<Node> current_node = root;
    for (int node_num=1; node_num < k; node_num++) {
        shared_ptr<Node> next_node(new Node);
        current_node->next = next_node;
        next_node->data = node_num;
        next_node.reset();
        current_node = current_node->next;
    }

    current_node.reset();

}

void LinkedList::build_copyNodes_weak_ptrs() {
    if (nodeCount==0) return;
    CopyNode copy_node_to_add;
    copy_node_to_add.weak_node_ptr = root;
    //rcout << copy_node_to_add.weak_node_ptr << endl;
    copy_node_array.push_back(copy_node_to_add);
    //cout << copy_nodes[0].weak_node_ptr << endl;

    shared_ptr<Node> current_node = root->next;
    for (int i=1; i < nodeCount; i++) {
        copy_node_to_add.weak_node_ptr = current_node;
        copy_node_array.push_back(copy_node_to_add);
        current_node = current_node->next;
    }
}

void LinkedList::delete_node_shared_ptr_list() {
    if (nodeCount==0) return;
    shared_ptr<Node> node_to_delete;
    shared_ptr<Node> next_node = root->next;
    root.reset();

    for (int i=1; i < nodeCount; i++) {
        node_to_delete = next_node;
        next_node = node_to_delete->next;
        node_to_delete.reset();
    }

    next_node.reset();
    nodeCount=0;
}

/* Prints a linked list of shared_ptrs */
void LinkedList::print_node_list_shared_ptrs() {
    if (nodeCount==0) return;
    cout << "Shared ptrs data: [";
    shared_ptr<Node> current_node = root;
    cout << root->data << " ";

    current_node = root->next;
    for (int i=1; i < nodeCount; i++) {
        cout << current_node->data << " ";
        // cout << current_node->data << "<-pt'd by " << current_node.use_count() << " shared_ptr's." << endl;
        current_node = current_node->next;
    }

    /*
    cout << "Root use count: " << root.use_count() << endl;
    cout << "Root->next use count:" << root->next.use_count() << endl;
    */

    cout << "]" << endl;
}

/* Prints a linked list of weak_ptrs */
void LinkedList::print_node_list_weak_ptrs() {
    cout << "Weak ptrs data: [";
    for(auto node : copy_node_array) {
        try_print_node_weak_ptr(node.weak_node_ptr);
        cout << " ";
    }
    cout << "]" << endl;
}

int LinkedList::get_data_at_idx(int idx) {
    if (idx > nodeCount-1 || idx < 0) return -1;
    
    shared_ptr<Node> current_node = root;
    if (idx==0) {
        current_node.reset();
        return root->data;
    }

    current_node = root->next;
    for (int i=1; i < idx; i++) current_node = current_node->next;

    int return_val = current_node->data;
    current_node.reset();
    return return_val;
}

bool LinkedList::try_print_node_weak_ptr(weak_ptr<LinkedList::Node> &node_wp) {
    shared_ptr<LinkedList::Node> node_sp = node_wp.lock();
    if (node_sp) {
        cout << node_sp->data;
        return true;
    } else {
        return false;
    }
}

weak_ptr<LinkedList::Node> LinkedList::get_weak_ptr_at_idx(int idx) {
    return copy_node_array[idx].weak_node_ptr;
}

int LinkedList::try_get_node_weak_ptr_data(weak_ptr<LinkedList::Node> &node_wp) {
    shared_ptr<LinkedList::Node> node_sp = node_wp.lock();
    if (node_sp) {
        return node_sp->data;
    } else {
        return -444;
    }
}

bool LinkedList::weak_ptr_points_to_existing_node(weak_ptr<LinkedList::Node> &node_wp) {
    shared_ptr<LinkedList::Node> node_sp = node_wp.lock();
    if (node_sp) {
        return true;
    } else {
        return false;
    }
}

bool LinkedList::weak_ptrs_all_valid() {
    for (auto copy_node : copy_node_array) {
        if (!weak_ptr_points_to_existing_node(copy_node.weak_node_ptr))
            return false;
    }
    return true;
}

bool LinkedList::any_weak_ptr_valid() {
    for (auto copy_node : copy_node_array) {
        if (weak_ptr_points_to_existing_node(copy_node.weak_node_ptr))
            return true;
    }
    return false;
}
        
LinkedList::LinkedList() {

}

LinkedList::~LinkedList() {
    
}