#pragma once
#include<iostream>
#include<cinttypes>
#include<vector>
#include<queue>
#include<unordered_map>

class TTrie {
	struct TNode {
		TNode* Fail, * Exit, *Parent;
		std::unordered_map<uint32_t, TNode*> Childrens;
		uint32_t Symbol;
		bool End = false;
		std::vector<int> Position;

		TNode(uint32_t size) : Symbol(size), Fail(nullptr), Exit(nullptr), Parent(nullptr) {}
		~TNode() {
			for (auto& item : Childrens) {
				delete(item.second);
			}
		}

		TNode* Check(uint32_t elem) {
			std::unordered_map<uint32_t, TNode*>::iterator iter = Childrens.find(elem);
			if (iter == Childrens.end()) {
				return nullptr;
			}
			else {
				return iter->second;
			}
		}

	};
	TNode* Root;
	int CountPattern = 0;

	void AddPattern(std::vector<uint32_t>& pattern, int pos) {
		TNode* current = Root, *child;
		for (auto& elem : pattern) {
			child = current->Check(elem);
			if (child == nullptr) {
				child = new TNode(elem);
				current->Childrens.insert({elem, child});
				child->Parent = current;
			}
			current = child;
		}
		current->End = true;
		current->Position.push_back(pos);
	}
	
	void CreateLinks() {
		std::queue<TNode*> queue;
		queue.push(Root);
		TNode* current;
		while (!queue.empty()) {
			current = queue.front();
			queue.pop();
			for (auto& item : current->Childrens) {
				queue.push(item.second);
			}
			if (current == Root) {
				continue;
			}
			TNode* parent = current->Parent;
			parent = parent->Fail;
			while (parent != nullptr && parent->Check(current->Symbol) == nullptr) {
				parent = parent->Fail;
			}
			if (parent == nullptr) {
				current->Fail = Root;
			}
			else {
				current->Fail = parent->Check(current->Symbol);
			}
			if (current->Fail->End) {
				current->Exit = current->Fail;
			}
			else if(current->Fail->Exit != nullptr){
				current->Exit = current->Fail->Exit;
			}
		}
	}

public:
	TTrie() {
		Root = new TNode(0);
	}
	~TTrie() {
		delete Root;
	}

	void Create(std::vector<std::pair<int, std::vector<uint32_t>>>& patterns) {
		for (auto& item : patterns) {
			AddPattern(item.second, item.first);
		}
		CountPattern = patterns.size();
		CreateLinks();
	}

	void Find(std::vector<std::pair<uint32_t, std::pair<int, int>>>& text, std::vector<std::pair<int, int>>& output) {
		std::vector<int> check(text.size());
		int count = text.size();
		TNode* current = Root;
		for (int i = 0; i < count; ++i) {
			while (current->Fail != nullptr && current->Check(text[i].first) == nullptr) {
				current = current->Fail;
			}
			if (current->Check(text[i].first) != nullptr) {
				current = current->Check(text[i].first);
			}
			if (current->End) {
				for (auto& item : current->Position) {
					if (i - item >= 0) {
						check[i - item]++;
					}
				}
			}
			if (current->Exit != nullptr) {
				TNode* cur_ex = current->Exit;
				while (cur_ex != nullptr) {
					for (auto& item : cur_ex->Position) {
						if (i - item >= 0) {
							check[i - item]++;
						}
					}
					cur_ex = cur_ex->Exit;
				}
			}
		}

		for (int i = 0; i < count; ++i) {
			if (check[i] == CountPattern) {
				output.push_back(text[i].second);
			}
		}
	}

};
