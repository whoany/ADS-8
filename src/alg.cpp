// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "File error!" << std::endl;
		return;
	}

	std::string word;
	int ch;
	while ((ch = file.get()) != EOF) {
		if (std::isalpha(static_cast<unsigned char>(ch))) {
			word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
		}
		else if (!word.empty()) {
			tree.add(word);
			word.clear();
		}
	}
	if (!word.empty())
		tree.add(word);

	file.close();
}

void printFreq(BST<std::string>& tree) {
	std::vector<std::pair<std::string, int>> items;
	tree.inorder([&items](const std::string& key, int count) {
		items.emplace_back(key, count);
		});

	std::sort(items.begin(), items.end(),
		[](const std::pair<std::string, int>& a,
			const std::pair<std::string, int>& b) {
				if (a.second != b.second)
					return a.second > b.second;
				return a.first < b.first;
		});

	std::ofstream out("result/freq.txt");
	for (const auto& item : items) {
		std::cout << item.first << ' ' << item.second << std::endl;
		if (out)
			out << item.first << ' ' << item.second << std::endl;
	}
}
