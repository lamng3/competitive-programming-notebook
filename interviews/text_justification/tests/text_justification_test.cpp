// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall text_justification_test.cpp -o /tmp/text_justification && /tmp/text_justification
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // 68: the LeetCode examples
    {
        vector<string> w1 = {"This", "is", "an", "example", "of", "text", "justification."};
        CHECK(Solution().fullJustify(w1, 16) == vector<string>({"This    is    an", "example  of text", "justification.  "}));
        vector<string> w2 = {"What", "must", "be", "acknowledgment", "shall", "be"};
        CHECK(Solution().fullJustify(w2, 16) == vector<string>({"What   must   be", "acknowledgment  ", "shall be        "}));
    }

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
