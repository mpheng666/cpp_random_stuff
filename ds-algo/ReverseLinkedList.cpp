// Implement an API to reverse a singly linked list
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// implement solution in this class
class Solution {
public:
    ListNode* reverse(ListNode* list) {
        if (list == nullptr) {
            std::cout << "Curr node val: nullptr" << '\n';
            return list;
        }
        if (list->next == nullptr) {
            std::cout << "Curr node val: " << list->val << '\n';
            return list;
        }
        ListNode* curr_node = list;
        ListNode* prev_node = nullptr;
        ListNode* next_node = curr_node->next;

        while (curr_node != nullptr) {
            std::cout << "Curr node val: " << curr_node->val << " ";
            next_node = curr_node->next;
            curr_node->next = prev_node;
            prev_node = curr_node;
            curr_node = next_node;
        }

        std::cout << '\n';

        return prev_node;
    }
};

int main(void) {
    // write a test code here
    // Input: 1->2->3->4->5->NULL
    // Output:5->4->3->2->1->NULL
    // Besides, the solution shall be in a time complexity of O(n) and memory
    // complexity of O(1).
    ListNode* input_list1 = new ListNode(1);
    ListNode* input_list2 = new ListNode(2);
    ListNode* input_list3 = new ListNode(3);
    ListNode* input_list4 = new ListNode(4);
    ListNode* input_list5 = new ListNode(5);
    input_list1->next = input_list2;
    input_list2->next = input_list3;
    input_list3->next = input_list4;
    input_list4->next = input_list5;
    ListNode* input = input_list1;
    ListNode* input_null = nullptr;

    while (input_list1) {
        std::cout << "input val: " << input_list1->val << ' ';
        input_list1 = input_list1->next;
    }

    std::cout << '\n';

    Solution solution;
    ListNode* output_list = solution.reverse(nullptr);

    while(output_list)
    {
        std::cout << "output_list val: " << output_list->val << ' ';
        output_list = output_list->next;
    }
    std::cout << '\n';

    delete input_list1;
    delete input_list2;
    delete input_list3;
    delete input_list4;
    delete input_list5;

    return 0;
}