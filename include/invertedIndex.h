#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <mutex>

struct Entry {
    size_t doc_id, count;
    bool operator == (const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> inputDocs);

    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs; 
    std::map<std::string, std::vector<Entry>> freqDictionary; 
    void inputDoc(std::string, int);
};
