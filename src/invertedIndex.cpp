#include "invertedIndex.h"

void InvertedIndex::inputDoc(std::string input, int iDoc){
    docs.push_back(input);
    std::stringstream checkDocs(input);
    std::string subStr;
    Entry entry;
    entry.doc_id = iDoc;
    while(std::getline(checkDocs, subStr, ' ')){
        if(subStr.size() > 0){
            auto itMap = freqDictionary.find(subStr);
            if(itMap != freqDictionary.end()){
                bool checkBoolDocs = true;
                for(int i = 0; i < itMap->second.size(); i++){
                    if(itMap->second[i].doc_id == iDoc){
                        itMap->second[i].count++;
                        checkBoolDocs = false;
                        break;
                    }
                }
                if(checkBoolDocs){
                    entry.count = 1;
                    itMap->second.push_back(entry);
                }
            }
            else{
                entry.count = 1;
                freqDictionary[subStr].push_back(entry);
            }
        }
    }
}


void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs){
    std::vector<std::thread> threads(inputDocs.size());
    for(int iDoc = 0; iDoc < inputDocs.size(); iDoc ++){
        docs.push_back(inputDocs[iDoc]);
        threads[iDoc] = std::thread([=](){
            std::stringstream checkDocs(inputDocs[iDoc]);
            std::string subStr;
            Entry entry;
            entry.doc_id = iDoc;
            
            while(std::getline(checkDocs, subStr, ' ')){
                if(subStr.size() > 0){
                    auto itMap = freqDictionary.find(subStr);
                    if(itMap != freqDictionary.end()){
                        bool checkBoolDocs = true;
                        for(int i = 0; i < itMap->second.size(); i++){
                            if(itMap->second[i].doc_id == iDoc){
                                itMap->second[i].count++;
                                checkBoolDocs = false;
                                break;
                            }
                        }
                        if(checkBoolDocs){
                            entry.count = 1;
                            itMap->second.push_back(entry);
                        }
                    }
                    else{
                        entry.count = 1;
                        freqDictionary[subStr].push_back(entry);
                    }
                }
            }
        });
    }
    for(auto& th : threads){
        th.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
    auto itMap = freqDictionary.find(word);
    if(itMap != freqDictionary.end()){
        return itMap->second;
    }
    return std::vector<Entry>();
}
