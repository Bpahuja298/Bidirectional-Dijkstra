#include<bits/stdc++.h>
using namespace std;

#define adj vector<vector<vector<int>>>

#define ll long long

// Vector of two priority queues for forward and backward searches.
#define pq  vector<priority_queue<pair<ll, int>,vector<pair<ll,int>>,greater<pair<ll,int>>>>

#define INF INT_MAX

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adjList_[0] and cost_[0] correspond to the initial graph,
    // adjList_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding to nodes.
    // adjacency list itself is stored in adjList_, and the corresponding edge costs are stored in cost_.
    adj adjList_;
    adj cost_;
    // distance_[0] stores distances for the forward search, and distance_[1] stores distances for the backward search.
    vector<vector<ll>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True if the node was visited
    // either by forward or backward search.
    vector<bool> visited_;

public:
    Bidijkstra(int n, adj adjList, adj cost)
        : n_(n), adjList_(adjList), cost_(cost), distance_(2, vector<ll>(n, INF)), visited_(n)
    { workset_.reserve(n); }	

    // Initialize the data structures before new query, clear the changes made by the previous query.
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INF;
            visited_[v] = false;
        }
        workset_.clear();
    }

    // Processes visit of either forward or backward search (determined by value of side), to node v trying to relax the current distance by dist.
    void visit(pq& q, int side, int v, ll dist) {
        if ( distance_[side][v] > dist) {
			distance_[side][v] = dist;
			q[side].push({distance_[side][v], v});
			workset_.push_back(v);
		}
    }
		
		int extractMin(pq& q, int side) {
		pair<ll,int> p = q[side].top();
		q[side].pop();
		return p.second;
	}
	
	void Process(pq& q, int side, int u, vector<vector<int>> &adjList, const vector<vector<int>> &cost) {
		for (int i = 0; i < adjList[u].size(); ++i) {
				int v = adjList[u][i];
				int w = cost[u][i];
				visit(q, side, v, distance_[side][u] + w);
		}	
	}
	
	ll ShortestPath(int v) {
		ll dist = INF;
		for(int u: workset_) {
			if (distance_[0][u] + distance_[1][u] < dist) {
				dist = distance_[0][u] + distance_[1][u];
			}
		}
		if (dist == INF)
			return -1;
		return dist;
	}
		
    // Returns the distance from s to t in the graph.
    ll query(int s, int t) {
        clear();
        pq q(2);
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
       
		while (!q[0].empty() && !q[1].empty()) {
				int v = extractMin(q, 0);
				Process(q, 0, v, adjList_[0], cost_[0]);
				if (visited_[v] == true)
                    return ShortestPath(v);
				visited_[v] = true;
				
				int v_r = extractMin(q, 1);
				Process(q, 1, v_r, adjList_[1], cost_[1]);
				if (visited_[v_r] == true)
                    return ShortestPath(v_r);
				visited_[v_r] = true;
			}
        return -1;
    }
};

int main() {
    int n, m;
    // input n as number of nodes and m as number of edges
    cout << "Enter number of nodes then the number of edges ypu want in a graph" << endl;
    cin >> n >> m;
    
    adj adjList(2, vector<vector<int>>(n));
    adj cost(2, vector<vector<int>>(n));
    
    cout << "Enter " << m << " triplets of directed edges and their cost" << endl;
    int u, v, c;
    for (int i=0; i<m; ++i) { 
        // input (u,v) as directed edge from u to v with a cost of c.
        cin >> u >> v >> c;
        adjList[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adjList[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }
	
	//object of Bidijkstra
    Bidijkstra biDijkstra(n, adjList, cost);

    int t;
    cout << "Enter number of queries you want to ask" << endl; 
    cin >> t;
    for (int i=0; i<t; i++) {
        int u, v;
        cout << "Enter directed edges you want to find the shortest distance between them" << endl;  
        cin >> u >> v;
        cout << "Your Answer:  "<< biDijkstra.query(u-1, v-1) << endl;
    }
    return 0;
}
