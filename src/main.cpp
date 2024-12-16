#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"

int main(){
    ConverterJSON converterJSON;
    InvertedIndex invertedIndex;
    std::vector <std::string> fileText;
    std::vector <std::string> requests;

    try{
        fileText = converterJSON.GetTextDocuments();
        maxResponses = converterJSON.GetResponsesLimit();
        requests = converterJSON.GetRequests();
    }
    catch(std::string& er){
        std::cout << er;
        return 1;
    }
    
    std::cout << "Sending text file documents.\n";

    invertedIndex.UpdateDocumentBase(fileText);



    SearchServer searchServer(invertedIndex);

    std::vector<std::vector<Entry>> expected;

    auto answers = searchServer.search(requests);
    std::vector<std::vector<std::pair<int, float>>> newAnswers;

    for(int x = 0; x < answers.size(); x++){
        std::vector<std::pair<int, float>> vectorAnswers;
        for(int y = 0; y < answers[x].size(); y++){
            std::pair<int, float> pairAnswers;
            pairAnswers = std::make_pair(answers[x][y].doc_id, double(int(answers[x][y].rank * 1000) / 1000.0));
            vectorAnswers.push_back(pairAnswers);
        }
        newAnswers.push_back(vectorAnswers);
    }
    
    converterJSON.putAnswers(newAnswers);
}