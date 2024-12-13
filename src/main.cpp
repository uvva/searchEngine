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
    catch(int& e){
        switch (e)
        {
        case 1:
            std::cout << "Config file is missing.";
            break;
        case 2:
            std::cout << "Incorrect config file.";
            break;
        case 3:
            std::cout << "Config file is empty.";
            break;
        case 4:
            std::cout << "Config.json has incorrect file version.";
            break;
        case 5:
            std::cout << "No information about files in Config.json.";
            break;
        case 6:
            std::cout << "Request file is missing.";
            break;
        case 7:
            std::cout << "Incorrect request file.";
            break;
        case 8:
            std::cout << "Request file is empty.";
            break;
        default:
            std::cout << "Unknow error.";
            break;
        }
        return 1;
    }
    
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