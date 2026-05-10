// Copyright 2026 Shchekina

#include "textgen.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        return {};
    std::vector<std::string> words;
    for (std::string word; file >> word; words.push_back(word)) {}
    return words;
}

void createTable(const std::vector<std::string>& words,
    statetab& stab, prefix& firstPrefix) {
    if (words.size() < static_cast<size_t>(NPREF))
        return;
    prefix current;
    for (int i = 0; i < NPREF; ++i)
        current.push_back(words[i]);
    firstPrefix = current;
    for (size_t i = NPREF; i < words.size(); ++i) {
        const std::string& suffix = words[i];
        stab[current].push_back(suffix);
        current.pop_front();
        current.push_back(suffix);
    }
}

std::string generateText(const statetab& stab,
    const prefix& firstPrefix, int maxgen) {
    if (maxgen <= 0) return "";
    std::vector<std::string> result;
    for (const auto& w : firstPrefix)
        result.push_back(w);
    if (result.empty()) return "";
    prefix current = firstPrefix;

    while (result.size() < static_cast<size_t>(maxgen)) {
        auto it = stab.find(current);
        if (it == stab.end() || it->second.empty())
            break;

        const std::vector<std::string>& suffixes = it->second;
        int idx = std::rand() % suffixes.size();
        const std::string& next = suffixes[idx];

        result.push_back(next);

        current.pop_front();
        current.push_back(next);
    }

    std::string text;
    for (size_t i = 0; i < result.size(); ++i) {
        if (i != 0) text += " ";
        text += result[i];
    }
    return text;
}

bool saveFile(const std::string& filename, const std::string& text) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }
    out << text;
    return true;
}
