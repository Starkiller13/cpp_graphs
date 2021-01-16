#include "union_find.hpp"

Un_Find::Un_Find(int n){
    comp = n;
    id = new int[n];
    sz = new int[n];
    for (int i = 0; i<n; i++)  id[i] = i, sz[i] = 1;
}
Un_Find::~Un_Find(){
    delete[] id; 
    delete[] sz; 
}

int Un_Find::find(int v){
    int root = v;
    while (root != id[root])    
        root = id[root];
    while (v != root){ 
        int newp = id[v]; 
        id[v] = root; 
        v = newp; }
    return root;
}

void Un_Find::merge(int x, int y) {
    int i = find(x); int j = find(y); if (i == j) return;
    // make smaller root point to larger one
    if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
    else { id[j] = i, sz[i] += sz[j]; }
    comp--;
}

bool Un_Find::connected(int x, int y) { 
    return find(x) == find(y); 
}

int Un_Find::count() { 
    return comp; 
}

