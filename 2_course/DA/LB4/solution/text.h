#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<sstream>

void ReadPattern(std::vector<std::pair<int, std::vector<uint32_t>>>& patterns) {
	std::string str, token;
	int count = 0;
	std::getline(std::cin, str);
	std::stringstream strpattern(str);
	std::vector<uint32_t> pattern;
	bool inpattern = false;
	while (strpattern >> token) {
		if (token == "?" && inpattern) {
			patterns.push_back({ count - 1, pattern });
			pattern.clear();
			inpattern = false;
		}
		else if(token != "?"){
			pattern.push_back(std::stoi(token));
			inpattern = true;
		}
		count++;
	}
	if(count > 0){
	patterns.push_back({ count - 1, pattern });
	}
}

void ReadText(std::vector<std::pair<uint32_t, std::pair<int, int>>>& text) {
	int line = 1, word;
	uint32_t k;
	std::string str;
	while (std::getline(std::cin, str)) {
		std::stringstream strpattern(str);
		word = 1;
		while (strpattern >> k) {
			text.push_back({ k, {line, word} });
			word++;
		}
		line++;
	}
}
