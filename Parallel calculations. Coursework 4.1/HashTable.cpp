#include "HashTable.h"
#include <iostream>

template <typename Key, typename Value>
HashTable<Key, Value>::Node::Node(Key k, Value v) : word(k), fileNames(v) {}

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size) : m_size(size) {
    m_table.resize(size);
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Insert(const Key& word, const Value& fileNames) {
    size_t index = HashFunctional(word);
    m_table[index].push_back(Node(word, fileNames));
}

template <typename Key, typename Value>
Value& HashTable<Key, Value>::Search(const Key& word) {
    size_t index = HashFunctional(word);

    for (auto& node : m_table[index]) {
        if (node.word == word) {
            return node.fileNames;
        }
    }

    m_table[index].emplace_back(word, Value{});
    return m_table[index].back().fileNames;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::PrintAll() const {
    for (auto list : m_table) {
        for (auto node : list) {
            std::cout << "Word: " << node.word << " Files where this word is found: ";
            for (auto& file : node.fileNames) {
                std::cout << file << " ";
            }
            std::cout << std::endl;
        }
    }
}

template <typename Key, typename Value>
void HashTable<Key, Value>::ShowFileName(const Key& word) const {
    size_t index = HashFunctional(word);

    for (const auto& node : m_table[index]) {
        if (node.word == word) {
            std::cout << "Word: " << word << " Files where this word is found: ";
            for (const auto& file : node.fileNames) {
                std::cout << file << " ";
            }
            std::cout << std::endl;
            return;
        }
    }
    std::cout << "Word not found: " << word << std::endl;
}

template <typename Key, typename Value>
size_t HashTable<Key, Value>::HashFunctional(const Key& word) const {
    return std::hash<Key>()(word) % m_size;
}

template class HashTable<std::string, std::vector<std::string>>;
