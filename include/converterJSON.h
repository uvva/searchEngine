#pragma once

#include <fstream>
#include <iostream>
#include <cmath>

#include <iomanip>
#include <sstream>

#include "nlohmann/json.hpp"

#define configName "config.json"
#define version "0.2"
#define requestName "requests.json"

class ConverterJSON {
private:
    std::ifstream streamFile;
    nlohmann::json streamJson;
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);
};