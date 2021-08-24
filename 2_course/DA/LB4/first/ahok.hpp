#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <queue>


class TAhoKarasik{
	private:
		class TElem{
			using elem_ptr = TElem*;
			public:
				long long Sym;
				bool IsLast;
				elem_ptr Suf;
				elem_ptr Stop;
				elem_ptr Parent;
				std::unordered_map<long long,elem_ptr> Childs;
				std::vector<size_t> JockerPos;
			public:
				TElem(long long S = -1,bool IsL=false):Sym(S),IsLast(IsL),Suf(nullptr),Stop(nullptr),Parent(nullptr){}
				~TElem(){
					for(auto& i: Childs)
					{
						delete(i.second);
					}
				};
				elem_ptr HaveChild(long long x)
				{
					try{ return Childs.at(x); }
					catch(std::out_of_range){ return nullptr; }
				}
		}; //TElem
		using elem_ptr = TElem*;
	public:
		TElem Root;
		~TAhoKarasik(){};
		void Push(std::vector<long long>& vect,size_t pos){
			elem_ptr cur_elem(&Root);
			size_t size_vect = vect.size();
			elem_ptr child;
			for(int i = 0;i < size_vect;++i){
				try{	
					cur_elem = cur_elem->Childs.at(vect[i]);
				}
				catch(std::out_of_range){
					child = new TElem(vect[i]);
					cur_elem->Childs.insert({vect[i],child});
					child->Parent = cur_elem;
					cur_elem = child;
				}
			}
			cur_elem->IsLast = true;
			cur_elem->JockerPos.push_back(pos);
		}

		void SearchSufPtr(){
			std::queue<elem_ptr> q;
			q.push(&Root);
			while(!q.empty()){
				elem_ptr item = q.front();
				q.pop();
				for(auto i: item->Childs){
					q.push(i.second);
				}

				long long x = item->Sym;
				elem_ptr par = item->Parent;
				if(item == &Root)
					continue;
				
				par = par->Suf;
				while((par != nullptr) && (par->HaveChild(x) == nullptr))
					par = par->Suf;
				if(par == nullptr)
					item->Suf = &Root;
				else
					item->Suf = par->Childs.at(x);
				if(item->Suf->Stop != nullptr)
					item->Stop = item->Suf->Stop;
			}
		}

		void AddLast(elem_ptr cur,std::vector<int>& vect,const size_t &pos){
			size_t size = cur->JockerPos.size();
			for(size_t i = 0;i < size;++i){
				if(pos-cur->JockerPos[i]>=0)
					++vect[pos-cur->JockerPos[i]];
			}
		}

		void Find(std::vector<long long> &text,std::vector<int> &pos){
			size_t text_size = text.size();
			elem_ptr cur = &Root;
			for(int i = 0;i < text_size;++i){
				while(cur->HaveChild(text[i])==nullptr && cur->Suf!=nullptr)
				{
					cur = cur->Suf;
				}
				if(cur->HaveChild(text[i])!=nullptr){
					cur = cur->Childs.at(text[i]);
					if(cur->Stop!=nullptr){
						AddLast(cur->Stop,pos,i);}
					if(cur->IsLast){
						AddLast(cur,pos,i);}
				}
			}
		}

}; //TAhoKarasik