#include <string>
#include <vector>
#include <mutex>
#include <filesystem>
#include "HashTable.h"
#include "SimpleThreadPool.h"

namespace fs = std::filesystem;

struct FileContent {
    std::string filename;
    std::vector<std::string> content;
};

class InvertedIndex {
public:
    void IndexDirectory(const std::string& directoryPath, size_t numofstreams);
    void ShowIndex() const;
    void ShowFileName(const std::string& word) const;

private:
    mutable std::mutex mutex;
    HashTable<std::string, std::vector<std::string>> m_hashTable;

    void ProcessFile(const fs::path& filePath);
    std::vector<std::string> ReadFileContent(const fs::path& filePath);
    void AddFile(const FileContent& fileContent);
};
