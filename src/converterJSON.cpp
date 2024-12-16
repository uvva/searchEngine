#include "converterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments(){
    streamFile.open(configName);
    if(!streamFile.is_open()){
        throw "Config file is missing.";
    }

    std::ifstream testFile(configName);

    if(!(nlohmann::json::accept(testFile))){
        throw "Incorrect config file.";
    }
    testFile.close();
        
    streamFile >> streamJson;
        
    auto checkConfig = streamJson.find("config");
    if(checkConfig == streamJson.end()){
        throw "Config file is empty.";
    }
    auto checkConfigVersion = streamJson["config"].find("version");
    auto checkConfigName = streamJson["config"].find("name");
    auto checkConfigResp = streamJson["config"].find("max_responses");
    if(checkConfigVersion == streamJson["config"].end() | checkConfigName == streamJson["config"].end() | checkConfigResp == streamJson["config"].end()){
        throw "Config file is empty.";
    }

    if ((streamJson["config"]["version"].get<std::string>()) != version){
        throw "Config.json has incorrect file version.";
    }

    auto checkFile = streamJson.find("files");
    if(checkFile == streamJson.end()){
        throw "No information about files in Config.json.";
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
        throw "Request file is missing.";
    }

    std::ifstream testFile(requestName);

    if(!(nlohmann::json::accept(testFile))){
        throw "Incorrect request file.";
    }

    testFile.close();

    streamFile >> streamJson;

    auto checkConfig = streamJson.find("requests");
    if(checkConfig == streamJson.end()){
        throw "Request file is empty.";
    }
    std::vector<std::string> request;

    streamJson.at("requests").get_to(request);

    streamFile.close();
    return request;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>answers){
    std::string answer = "{\n\t\"answers\": {";
    
    for(int i = 0; i < answers.size(); i ++){
        if(i > 0){
            answer += ',';
        }
        std::string numRequest = ("\n\t\t\"request" + std::string(3 - (std::to_string(i)).size(), '0') +  std::to_string(i+1) + "\": {");
        answer += numRequest;
        if(answers[i].empty()){
            answer += "\n\t\t\t\"result\": \"false\"";
        }
        else{
            answer += "\n\t\t\t\"result\": \"true\",";
            if(answers[i].size() ==  1){
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(3) << answers[i][0].second;
                std::string formatedRank = oss.str();
                answer += "\n\t\t\t\"docid\": " + std::to_string(answers[i][0].first) + ", \"rank\": " + formatedRank;
            }
            else{
                answer += "\n\t\t\t\"relevance\": {";
                for(int iI = 0; iI < answers[i].size(); iI ++){
                    if(iI > 0){
                        answer += ',';
                    }
                    std::ostringstream oss;
                    oss << std::fixed << std::setprecision(3) << answers[i][iI].second;
                    std::string formatedRank = oss.str();
                    answer += "\n\t\t\t\t\"docid\": " + std::to_string(answers[i][iI].first) + ", \"rank\": " + formatedRank;
                }
                answer += "\n\t\t\t}";
            }
        }
        answer += "\n\t\t}";
    }
    answer += "\n\t}\n}";
    std::ofstream createJson;
    createJson.open("answers.json");
    createJson << std::setw(1) << answer;
    createJson.close();
}