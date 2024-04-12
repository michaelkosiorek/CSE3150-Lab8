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
    vector<CopyNode> copy_nodes(nodeCount);
    weak_ptr<Node> weak_root(root);
    CopyNode copy_node_to_add;
    copy_node_to_add.weak_node_ptr = weak_root;
    copy_nodes.push_back(copy_node_to_add);

    shared_ptr<Node> current_node = root->next;
    for (int i=1; i < nodeCount; i++) {
        weak_ptr<Node> weak_root(root);
        copy_node_to_add.weak_node_ptr = weak_root;
        copy_nodes.push_back(copy_node_to_add);
    }
    copy_node_array = copy_nodes;
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
    shared_ptr<Node> current_node = root;
    cout << root->data << " ";

    current_node = root->next;
    for (int i=1; i < nodeCount; i++) {
        cout << current_node->data << " ";
        // cout << current_node->data << "<-pt'd by " << current_node.use_count() << " shared_ptr's." << endl;
        current_node = current_node->next;
    }

    cout << endl;
}

/* Prints a linked list of weak_ptrs */
void LinkedList::print_node_array_weak_ptrs() {
    cout << copy_node_array[3].weak_node_ptr << endl;
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
        
LinkedList::LinkedList() {

}

LinkedList::~LinkedList() {
    
}