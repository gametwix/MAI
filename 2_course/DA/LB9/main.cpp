#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>


uint64_t Deikstra(int s, int f, std::vector<std::map<int,int>> &graph){
    std::map<uint64_t,int> priority_queue;
    priority_queue.emplace(std::make_pair(0,s));
    std::unordered_set<int> visited;
    std::map<int,uint64_t> visited_cost;
    visited.insert(s);
    visited_cost[s] = 0;
    while(!priority_queue.empty()){
        //int node_cost = priority_queue.begin()->first;
        int node = priority_queue.begin()->second;
        priority_queue.erase(priority_queue.begin());
        if(node == f){
            break;
        }
        //if(visited.count(node) >= 1){
        //    if(node_cost > visited_cost[node]){
        //        continue;
        //    }
        //}
        for(auto &i:graph[node]){
            if(visited.count(i.first) == 0 || visited_cost[node] + i.second < visited_cost[i.first]){
                priority_queue.emplace(std::make_pair(visited_cost[node] + i.second,i.first));
                visited_cost[i.first] = visited_cost[node] + i.second;
                visited.insert(i.first);
            }
        }
    }
    if(visited.count(f) == 0)
        return -1;
    else
        return visited_cost[f];
}



int main(){
    int n,m,s,f;
    std::cin >> n >> m >> s >> f;
    --s;
    --f;
    std::vector<std::map<int,int>> graph(n);
    for(int i = 0; i < m; ++i){
        int a, b, cost;
        std::cin >> a >> b >> cost;
        graph[a-1][b-1] = cost;
        graph[b-1][a-1] = cost;
    }
    uint64_t ans = Deikstra(s,f,graph);
    if(ans == -1){
        std::cout << "No solution" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }
}

