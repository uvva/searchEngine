#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "invertedIndex.h"

extern int maxResponses;

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx){ };

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
    InvertedIndex _index;
};