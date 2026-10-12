// Build & run from tests/:
//   g++ -std=c++17 -fsanitize=address,undefined -Wall change_directory_test.cpp -o /tmp/change_directory && /tmp/change_directory
#include "../solution.cpp"

static int checks = 0, fails = 0;
#define CHECK(cond) do {                                              \
    ++checks;                                                         \
    if (!(cond)) { ++fails;                                           \
        printf("FAIL line %d: %s\n", __LINE__, #cond); }              \
} while (0)

int main() {
    // cd
    unordered_map<string, string> links = {{"/home/bugs/lola", "/home/lola"}, {"/a", "/b"}, {"/b", "/c"}, {"/c", "/a"},
                                           {"/x/y", "/z"}, {"/p", "/q"}, {"/q", "/r/s"}};
    CHECK(ChangeDirectory::cd("/home/bugs", ".") == "/home/bugs");
    CHECK(ChangeDirectory::cd("/home/bugs", "../daffy") == "/home/daffy");
    CHECK(ChangeDirectory::cd("/", "../../x") == "/x");
    CHECK(ChangeDirectory::cd("/a/b", "") == "/a/b");
    CHECK(ChangeDirectory::cd("/home/bugs", "lola/../basketball", links) == "/home/basketball");
    CHECK(ChangeDirectory::cd("/x", "y/file", links) == "/z/file");
    CHECK(ChangeDirectory::cd("/", "p/t", links) == "/r/s/t");
    bool loop = false;
    try { ChangeDirectory::cd("/", "a", links); } catch (const exception&) { loop = true; }
    CHECK(loop);

    printf("\n%d checks, %d failed.\n", checks, fails);
    return fails ? 1 : 0;
}
