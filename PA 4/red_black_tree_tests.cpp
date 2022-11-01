#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
#include "red_black_tree.h"

using std::cout, std::stringstream;
using std::invalid_argument;

#define black   "\033[30m"
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define reset   "\033[m"

#define END_TEST bool this_test_passed = test_passed;\
test_passed = true;\
return this_test_passed;

#define expect(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << "\n";\
    test_passed = false;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
}

#define assert(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << "\n";\
    test_passed = false;\
    END_TEST;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
  END_TEST;\
}

#define expect_throw(X,E) {\
  bool threw_expected_exception = false;\
  try { X; }\
  catch(const E& err) {\
    threw_expected_exception = true;\
  } catch(...) {\
    std::cout << blue << "  [help] " << #X << " threw an incorrect exception." << reset << "\n";\
  }\
  if (!threw_expected_exception) {\
    std::cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<"\n";\
    test_passed = false;\
  }\
}

#define expect_no_throw(X) {\
  try { X; }\
  catch(...) {\
    std::cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << reset << "\n";\
    test_passed = false;\
  }\
}

#define test(x) if (test_##x()) { std::cout << green << "[PASS] "; pass_cnt++; }\
else { std::cout << red << "[FAIL] "; fail_cnt++; }\
std::cout << #x << reset << "\n";
#define skip(x) std::cout << yellow << "[SKIP] " << #x << reset << "\n"; skip_cnt++;

namespace {
    bool test_passed = true;
}

bool test_create() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);


    END_TEST;
}

bool test_insert() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    END_TEST;
}

bool test_insert_duplicate() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    END_TEST;
}

bool test_insert_right() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    for (int i = 0; i <= 64; ++i) {
        rbt.insert(i);
    }

    END_TEST;
}

bool test_insert_left() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    for (int i = 64; i > -1; --i) {
        rbt.insert(i);
    }

    END_TEST;
}

bool test_insert_in2out() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    for (int i = 0; i <= 64; ++i) {
        int num = i % 2 ? -i : i;
        rbt.insert(num);
    }

    END_TEST;
}

bool test_insert_out2in() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    for (int i = 64; i > -1; --i) {
        int num = i % 2 ? -i : i;
        rbt.insert(num);
    }

    END_TEST;
}

bool test_contains() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    {
        assert(rbt.contains(0));
        assert(rbt.contains(1));
        assert(rbt.contains(2));
        assert(rbt.contains(3));
        assert(rbt.contains(4));
        assert(rbt.contains(5));
        assert(rbt.contains(6));
        assert(rbt.contains(7));
        assert(rbt.contains(8));
        assert(rbt.contains(9));
        assert(rbt.contains(10));
        assert(rbt.contains(11));
        assert(rbt.contains(12));
        assert(rbt.contains(13));
        assert(rbt.contains(14));
        assert(!rbt.contains(15));
    }

    END_TEST;
}

bool test_remove_leaf() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    rbt.remove(14);


    rbt.remove(12);


    rbt.remove(10);


    rbt.remove(8);


    rbt.remove(6);


    rbt.remove(4);


    rbt.remove(2);


    rbt.remove(0);


    rbt.remove(13);


    rbt.remove(9);


    rbt.remove(5);


    rbt.remove(1);


    rbt.remove(11);


    rbt.remove(3);


    rbt.remove(7);


    END_TEST;
}

bool test_remove_middle() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);

    rbt.remove(13);

    rbt.remove(14);

    rbt.remove(8);
    rbt.remove(9);

    rbt.remove(1);
    rbt.remove(2);

    rbt.remove(4);
    rbt.remove(5);

    END_TEST;
}

bool test_remove_root() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    rbt.remove(7);


    rbt.remove(8);


    rbt.remove(9);


    END_TEST;
}

bool test_remove_root_l() {
    RedBlackTree<int> rbt;

    rbt.insert(1);
    rbt.insert(0);

    rbt.remove(1);

    END_TEST;
}

bool test_remove_root_r() {
    RedBlackTree<int> rbt;

    rbt.insert(0);
    rbt.insert(1);

    rbt.remove(0);

    END_TEST;
}

bool test_remove_empty() {
    RedBlackTree<int> rbt;

    assert(rbt.get_root() == nullptr);

    expect_no_throw(rbt.remove(0));
    assert(rbt.get_root() == nullptr);

    END_TEST;
}

bool test_remove_invalid() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    expect_no_throw(rbt.remove(100));


    END_TEST;
}

bool test_find_min() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);

    assert(rbt.find_min() == 0);

    END_TEST;
}

bool test_find_min_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);
    expect_throw(rbt.find_min(), invalid_argument);

    END_TEST;
}

bool test_find_max() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);

    assert(rbt.find_max() == 14);

    END_TEST;
}

bool test_find_max_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);
    expect_throw(rbt.find_max(), invalid_argument);

    END_TEST;
}

bool test_copy() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    RedBlackTree<int> a(rbt);
    {
        const RedBlackTree<int>::Node* root = a.get_root(), * rooot = rbt.get_root();
        assert(root != rooot);
        assert(root->value == rooot->value);
    }

    END_TEST;
}

bool test_copy_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    RedBlackTree<int> a(rbt);
    assert(a.get_root() == nullptr);

    END_TEST;
}

bool test_copy_oper() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    RedBlackTree<int> a;
    assert(a.get_root() == nullptr);

    a.insert(6);
    a.insert(2);
    a.insert(10);
    a.insert(0);
    a.insert(5);
    a.insert(8);
    a.insert(12);
    a.insert(-1);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(7);
    a.insert(9);
    a.insert(11);
    a.insert(13);

    {
        const RedBlackTree<int>::Node* root = a.get_root(), * rooot = rbt.get_root();
        assert(root != rooot);
        assert(root->value != rooot->value);
    }

    a = rbt;

    END_TEST;
}

bool test_copy_oper_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    RedBlackTree<int> a;
    assert(a.get_root() == nullptr);

    a.insert(6);
    a.insert(2);
    a.insert(10);
    a.insert(0);
    a.insert(5);
    a.insert(8);
    a.insert(12);
    a.insert(-1);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(7);
    a.insert(9);
    a.insert(11);
    a.insert(13);

    a = rbt;
    assert(a.get_root() == nullptr);

    END_TEST;
}

bool test_self_assignment() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);


    const RedBlackTree<int>::Node* old_root = rbt.get_root();
    rbt = rbt;

    assert(old_root == rbt.get_root());

    END_TEST;
}

bool test_node() {
    RedBlackTree<int>::Node node = RedBlackTree<int>::Node(INT32_MAX, static_cast<RedBlackTree<int>::Color>(4));
    assert(node.parent == nullptr);
    assert(node.left == nullptr);
    assert(node.right == nullptr);
    assert(node.sibling() == nullptr);
    stringstream ss;
    ss << node;
    cout << ss.str() << "\n";

    END_TEST;
}

bool test_print() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);

    stringstream ss;
    expect_no_throw(rbt.print_tree(ss));
    cout << ss.str() << "\n";

    END_TEST;
}

bool test_print_empty() {
    RedBlackTree<int> rbt;
    stringstream ss;
    expect_no_throw(rbt.print_tree(ss));
    assert(ss.str() == "<empty>\n");

    END_TEST;
}

bool test_random() {
    int nums[256] = {244, 63, 164, 66, 95, 33, 248, 214, 20, 35, 183, 197, 134, 73, 36, 19, 30, 109, 195, 151, 162, 240, 59, 215, 119, 145, 209, 12, 78, 106, 221, 238, 208, 135, 26, 139, 219, 232, 181, 108, 144, 251, 180, 98, 117, 255, 83, 87, 62, 234, 68, 43, 233, 196, 142, 75, 182, 88, 204, 32, 47, 254, 122, 173, 184, 86, 242, 125, 79, 93, 150, 163, 16, 31, 253, 69, 76, 100, 148, 192, 25, 82, 247, 72, 94, 141, 6, 53, 157, 48, 4, 74, 237, 131, 202, 186, 50, 27, 46, 80, 39, 8, 246, 193, 77, 45, 116, 200, 13, 218, 3, 191, 171, 55, 166, 216, 137, 107, 37, 231, 210, 91, 158, 90, 224, 2, 174, 172, 65, 136, 124, 211, 199, 160, 146, 0, 54, 189, 14, 149, 56, 1, 112, 228, 126, 24, 168, 102, 21, 153, 140, 10, 67, 132, 118, 104, 155, 89, 11, 178, 177, 190, 99, 167, 194, 105, 222, 7, 143, 236, 212, 111, 128, 249, 185, 71, 176, 243, 250, 138, 245, 15, 121, 179, 187, 18, 52, 130, 113, 42, 207, 188, 44, 114, 230, 223, 133, 22, 34, 129, 170, 203, 226, 201, 92, 101, 85, 51, 61, 115, 64, 220, 97, 217, 154, 70, 96, 110, 120, 206, 60, 29, 175, 213, 241, 17, 23, 161, 152, 103, 38, 156, 9, 41, 147, 235, 40, 252, 5, 58, 229, 169, 127, 225, 81, 205, 165, 198, 123, 28, 49, 239, 57, 159, 84, 227};
    RedBlackTree<int> rbt;

    for (const int& num : nums)
        rbt.insert(num);


    for (const int& num : nums) {
        // cout << "Remove " << num << "\n";
        rbt.remove(num);
    }

    END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(create);
    test(insert);
    test(insert_duplicate);
    test(insert_right);
    test(insert_left);
    test(insert_in2out);
    test(insert_out2in);
    test(random);
    test(contains);
    test(remove_leaf);
    test(remove_middle);
    test(remove_root);
    test(remove_root_l);
    test(remove_root_r);
    test(remove_empty);
    test(remove_invalid);
    test(find_min);
    test(find_min_empty);
    test(find_max);
    test(find_max_empty);
    test(copy);
    test(copy_empty);
    test(copy_oper);
    test(copy_oper_empty);
    test(self_assignment);
    test(node);
    test(print);
    test(print_empty);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}