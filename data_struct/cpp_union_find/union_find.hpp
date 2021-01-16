int comp, *id, *sz;
class Un_Find{
    Un_Find(int n);
    ~Un_Find();
    int find(int v);
    void merge(int x, int y);
    bool connected(int x, int y);
    int count();
};

