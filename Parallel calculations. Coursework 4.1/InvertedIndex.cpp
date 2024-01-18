#include "InvertedIndex.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

void InvertedIndex::IndexDirectory(const std::string& directoryPath, size_t numofstreams) {
    SimpleThreadPool pool(numofstreams);

    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            pool.Enqueue(std::bind(&InvertedIndex::ProcessFile, this, entry.path()));
        }
    }
}

void InvertedIndex::ShowIndex() const {
    m_hashTable.PrintAll();
}

void InvertedIndex::ShowFileName(const std::string& word) const {
    m_hashTable.ShowFileName(word);
}

void InvertedIndex::ProcessFile(const fs::path& filePath) {
    FileContent fileContent = { filePath.filename().string(), ReadFileContent(filePath) };
    AddFile(fileContent);
}

std::vector<std::string> InvertedIndex::ReadFileContent(const fs::path& filePath) {
    std::ifstream fileStream(filePath);
    std::vector<std::string> words;

    if (fileStream.is_open())
    {
        std::string word, processedWord;
        while (fileStream >> word)
        {
            processedWord.clear();
            for (size_t i = 0; i < word.length(); ++i)
            {
                char ch = word[i];
                unsigned char uch = static_cast<unsigned char>(ch);
                // Перевірте наявність буквено-цифрових символів або внутрішніх апострофів
                if (isalpha(uch) || isdigit(uch) || (ch == '\'' && i > 0 && i < word.length() - 1))
                {
                    processedWord.push_back(tolower(uch));
                }
            }
            if (!processedWord.empty())
            {
                words.push_back(processedWord);
            }
        }
        fileStream.close();
    }
    else
    {
        std::cout << "Неможливо відкрити файл: " << filePath << std::endl;
    }
    return words;
}

void InvertedIndex::AddFile(const FileContent& fileContent) {
    
    for (const auto& word : fileContent.content) {
        std::lock_guard<std::mutex> lock(mutex);
        if (!word.empty()) {
            auto& fileList = m_hashTable.Search(word);
            if (std::find(fileList.begin(), fileList.end(), fileContent.filename) == fileList.end()) {
                fileList.push_back(fileContent.filename);
            }
        }
    }
}
