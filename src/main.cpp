// Copyright 2026 Shchekina

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "textgen.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::string inputFile = "input.txt";
    std::vector<std::string> words = readFile(inputFile);
    if (words.size() < static_cast<size_t>(NPREF)) {
        std::cout << "Not enough words" << std::endl;
        std::string originalText;
        for (size_t i = 0; i < words.size(); ++i) {
            if (i != 0) originalText += " ";
            originalText += words[i];
        }
        saveFile("gen.txt", originalText);
        return 0;
    }
    statetab stab;
    prefix firstPrefix;
    createTable(words, stab, firstPrefix);
    std::string generated = generateText(stab, firstPrefix, MAXGEN);
    if (saveFile("gen.txt", generated))
        std::cout << "Text is saved in gen.txt" << std::endl;
    else
        std::cerr << "Error writing to gen.txt" << std::endl;
    return 0;
}
