#include "converterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments(){
    streamFile.open(configName);
    if(!streamFile.is_open()){
        throw 1;
    }

    std::ifstream testFile(configName);

    if(!(nlohmann::json::accept(testFile))){
        throw 2;
    }
    testFile.close();
        
    streamFile >> streamJson;
        
    auto checkConfig = streamJson.find("config");
    if(checkConfig == streamJson.end()){
        throw 3;
    }
    auto checkConfigVersion = streamJson["config"].find("version");
    auto checkConfigName = streamJson["config"].find("name");
    auto checkConfigResp = streamJson["config"].find("max_responses");
    if(checkConfigVersion == streamJson["config"].end() | checkConfigName == streamJson["config"].end() | checkConfigResp == streamJson["config"].end()){
        throw 3;
    }

    if ((streamJson["config"]["version"].get<std::string>()) != version){
        throw 4;
    }

    auto checkFile = streamJson.find("files");
    if(checkFile == streamJson.end()){
        throw 5;
    }

    std::cout << "Initializing the engine " << streamJson["config"]["name"] << '\n';
    std::vector<std::string> fileName;
    std::vector<std::string> fileText;
    streamJson.at("files").get_to(fileName);

    streamFile.close();
    for(const auto& name : fileName){
        std::string text;
        streamFile.open(name);
        if(!streamFile.is_open()){
            std::cout << "No file at address: " << name << '\n';
        }
        else{
            char nil = '\0';
            std::getline(streamFile, text, nil);
            fileText.push_back(text);
            streamFile.close();
        }
    }

    return fileText;
}

int ConverterJSON::GetResponsesLimit(){
    return streamJson["config"]["max_responses"].get<int>();
}

std::vector<std::string> ConverterJSON::GetRequests(){
    streamFile.open(requestName);
    if(!streamFile.is_open()){
        throw 6;
    }

    std::ifstream testFile(requestName);

    if(!(nlohmann::json::accept(testFile))){
        throw 7;
    }

    testFile.close();

    streamFile >> streamJson;

    auto checkConfig = streamJson.find("requests");
    if(checkConfig == streamJson.end()){
        throw 8;
    }
    std::vector<std::string> request;

    streamJson.at("requests").get_to(request);

    streamFile.close();
    return request;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>answers){
    nlohmann::json answer;
    nlohmann::json requests;
    nlohmann::json relevance;
    nlohmann::json docidRank = {{"docid", "rank"}};

    answer["answers"] = {};
    
    for(int i = 0; i < answers.size(); i ++){
        std::string numRequest = ("Request" + std::string(3 - (std::to_string(i)).size(), '0') +  std::to_string(i+1));
        answer["answers"][numRequest] = {};
        if(answers[i].empty()){
            answer["answers"][numRequest]["result"] = "false";
        }
        else{
            answer["answers"][numRequest]["result"] = "true";
            if(answers[i].size() ==  1){
                answer["answers"][numRequest]["docid"] = answers[i][0].first;
                answer["answers"][numRequest]["rank"] = std::round(answers[i][0].second * 1000) / 1000;
            }
            else{
                answer["answers"][numRequest]["relevance"] = {};
                for(int iI = 0; iI < answers[i].size(); iI ++){
                    nlohmann::json newEntry;
                    newEntry["docid"] = answers[i][iI].first;
                    newEntry["rank"] = answers[i][iI].second;
                    answer["answers"][numRequest]["relevance"].push_back(newEntry);
                }
            }
        }
    }
    std::ofstream createJson;
    createJson.open("answers.json");
    createJson << std::setw(4) << answer;
}