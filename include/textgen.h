// Copyright 2026 Shchekina

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <vector>
#include <string>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

const int NPREF = 2;
const int MAXGEN = 1000;

std::vector<std::string> readFile(const std::string& filename);
void createTable(const std::vector<std::string>& words,
	statetab& stab, prefix& firstPrefix);
std::string generateText(const statetab& stab,
	const prefix& firstPrefix, int maxgen);
bool saveFile(const std::string& filename, const std::string& text);

#endif //INCLUDE_TEXTGEN_H_
