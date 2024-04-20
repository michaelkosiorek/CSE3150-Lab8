#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "weak_ptrs_ll.h"

TEST_CASE("smart ll") {

    SUBCASE("reg shared_ptr ll") {
        LinkedList ll;
        int ll_size = 6;
        ll.build_node_list(ll_size);

        CHECK_EQ(ll.get_node_count(), ll_size);

        // value at index is assigned index #
        for (int i=0; i < ll.get_node_count(); i++) {
            CHECK_EQ(ll.get_data_at_idx(i), i);
        }
    };

    SUBCASE("empty ll") {
        LinkedList ll;
        int ll_size = 0;
        ll.build_node_list(ll_size);

        CHECK_EQ(ll.get_node_count(), ll_size);

        // value at index is assigned index #
        for (int i=0; i < ll.get_node_count(); i++) {
            CHECK_EQ(ll.get_data_at_idx(i), i);
        }
    };

    SUBCASE("test if weak_ptrs valid before + after") {
        LinkedList ll;
        int ll_size = 15;
        ll.build_node_list(ll_size);
        CHECK_EQ(ll.get_node_count(), ll_size);

        ll.build_copyNodes_weak_ptrs();
        CHECK_EQ(ll.weak_ptrs_all_valid(), true);
        ll.delete_node_shared_ptr_list();
        // deleting the shared_ptrs should make the weak_ptrs_invalid;
        CHECK_EQ(ll.weak_ptrs_all_valid(), false);
        CHECK_EQ(ll.any_weak_ptr_valid(), false);
    };

    SUBCASE("test if weak_ptrs data is valid") {
        LinkedList ll;
        int ll_size = 50;
        ll.build_node_list(ll_size);
        CHECK_EQ(ll.get_node_count(), ll_size);

        ll.build_copyNodes_weak_ptrs();
        for (int i=0; i < ll_size; i++) {
            weak_ptr<LinkedList::Node> temp_weak_ptr = ll.get_weak_ptr_at_idx(i);
            CHECK_EQ(ll.try_get_node_weak_ptr_data(temp_weak_ptr), ll.get_data_at_idx(i));
        }

        ll.delete_node_shared_ptr_list();
        for (int i=0; i < ll_size; i++) {
            weak_ptr<LinkedList::Node> temp_weak_ptr = ll.get_weak_ptr_at_idx(i);
            CHECK_EQ(ll.try_get_node_weak_ptr_data(temp_weak_ptr), -444);
        }
    };

    SUBCASE("build weak ptr vec when no shared ptrs") {
        LinkedList ll;
        int ll_size = 0;
        ll.build_node_list(ll_size);

        CHECK_EQ(ll.get_node_count(), ll_size);

        ll.build_copyNodes_weak_ptrs();
        CHECK_EQ(ll.get_num_copy_nodes(), ll_size);
    }

}