#include "searchServer.h"

int maxResponses = 5;

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput){
    std::vector<std::vector<RelativeIndex>> searchIndex;
    for(const std::string& oneInput : queriesInput){
        std::stringstream checkInput(oneInput);
        std::string subStrInput;
        std::vector<Entry> entry;
        std::vector<RelativeIndex> vectorRelativeIndex;
        while(std::getline(checkInput, subStrInput, ' ')){
            if(subStrInput.size() > 0){
                std::vector<Entry> oneEntry = _index.GetWordCount(subStrInput);
                if(entry.size() == 0){
                    entry = oneEntry;
                }
                else{
                    for(int iOne = 0; iOne < oneEntry.size(); iOne++){
                        bool check = false;
                        for(int i = 0; i < entry.size(); i++){
                            if(oneEntry[iOne].doc_id == entry[i].doc_id){
                                entry[i].count += oneEntry[iOne].count;
                                check = true;
                            }
                        }
                        if(!check){
                            entry.push_back(oneEntry[iOne]);
                        }
                    }
                }
            }

        }
        if(entry.size() > 0){
            int max = 0;
            for(int i = 0; i < entry.size(); i++){
                if(max < entry[i].count){
                    max = entry[i].count;
                }
            }
            for(int i = 0; i < (std::min(entry.size(), (size_t)maxResponses)); i++){
                RelativeIndex relativeIndex;
                relativeIndex.doc_id = entry[i].doc_id;
                relativeIndex.rank = (float)entry[i].count / (float)max;
                vectorRelativeIndex.push_back(relativeIndex);
            }
        }
        std::sort(vectorRelativeIndex.begin(), vectorRelativeIndex.end(), [] (const RelativeIndex& x, const RelativeIndex& y){
            return (x.rank > y.rank);
        });
        searchIndex.push_back(vectorRelativeIndex);
    }
    if(searchIndex.size() > 0){
        return searchIndex;
    }
    return std::vector<std::vector<RelativeIndex>> ();
}