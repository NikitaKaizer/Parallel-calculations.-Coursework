#include <vector>
#include <list>
#include <functional>

template <typename Key, typename Value>
class HashTable {
private:
    struct Node {
        Key word;
        Value fileNames;
        Node(Key k, Value v);
    };

    size_t m_size;
    std::vector<std::list<Node>> m_table;

    size_t HashFunctional(const Key& word) const;

public:
    HashTable(size_t size = 5);
    void Insert(const Key& word, const Value& fileNames);
    Value& Search(const Key& word);
    void PrintAll() const;
    void ShowFileName(const Key& word) const;
};
