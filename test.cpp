#include "ford_fulk_alg.cpp"
using namespace std;

int main(){
    int indxr[]={0,2,3,5,6,8};
    int edg[]=   {1,2,3,1,4,5,3,5};
    double kap[]={11,12,12,1,11,19,7,4};
    _graph Gr = _graph(6,8,indxr,edg,kap);
    ford_fulkerson(Gr,0,5,false);
    Gr.~_graph();
}