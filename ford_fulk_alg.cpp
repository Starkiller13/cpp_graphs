#include "data_struct/_graph.cpp"
#include "data_struct/stack.c"
#include <stdio.h>
#include <iostream>
#include <string.h>

int ford_fulkerson(_graph G, int s, int t, bool verbose);
int ford_fulkerson_alg(int s, int t, int n);
void print_help();
struct exec {
    int * a_p1, ap_size;
    int * a_p2, n_size;
    double *k;
    double * k_p;
    double *flow_x;
    bool verbose;
    int num_iter;
    bool opt;
    double delta;
} FF;
struct stack Q;
int i,fr,to,*x,*y, *pred, pp, tmp;
double max_flow, *k, *e;

int main(int argc, char * argv[]){
    if(argc == 0){
        printf("\nNothing to do here, for help use tag --help or -h");
    }
    
    if(argc == 2 && (!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h")) ){
        print_help();
    }
    else if(argc == 4){
        try{
            int s,t;
            s = atoi(argv[1]);
            t = atoi(argv[2]);
            _graph cc = _graph(argv[3]);
            ford_fulkerson(cc,s,t,false);
        }catch(exception &e){
            cerr << "Exception caught, input file does not contain a flow network!\n" << e.what() << "\n";
            return -1;
        }
    }else if(argc == 5){
        try{
            if(strcmp(argv[1],"-v")){
                printf("\n-- !Invalid input format, use --help or -h! -- \n");
                return -1;
            }
            int s,t;
            s = atoi(argv[2]);
            t = atoi(argv[3]);
            _graph cc = _graph(argv[4]);
            ford_fulkerson(cc,s,t,true);
        }catch(exception &e){
            cerr << "Exception caught, input file does not contain a flow network!\n" << e.what() << "\n";
            return -1;
        }
    }else{
        printf("\n-- !Invalid input format, use --help or -h! -- \n");
        return -1;
    }
    return 0;
}

void print_help(){
    printf("\nProgram takes in input in this format: [-v (not mandatory)] [source node INT] [terminal node INT] [flow network file .txt]");
    printf("\nDefine a flow network file in star notation as follows:\n");
    printf("\n line1 -> [# of vertex] + space + [# of edges] ");
    printf("\n line2 -> [index array of star notation (start with 0)] ");
    printf("\n line3 -> [edges array] ");
    printf("\n line4 -> [capacity of edges array]\n");
    printf("\n Remember that this program works with flow networks, \n  not any kind of graph");
    printf("\nVerbose can be shown putting tag -v before the actual inputs \n");
    printf("\nExamples can be found in  folder 'ff_examples/' \n\n");
}
int ford_fulkerson(_graph G, int s, int t, bool verbose){
    FF.verbose = verbose;
    FF.ap_size = G.num_edges();
    int * w1 = G.exp_edges();
    int * w2 = G.edg();
    x = new int[FF.ap_size];
    y = new int[FF.ap_size];
    for(i=0;i<FF.ap_size;i++){
        x[i] = w1[i];
        y[i] = w2[i];
    }
    free(w1);
    free(w2);
    FF.a_p1 = new int[FF.ap_size*2];
    FF.a_p2 = new int[FF.ap_size*2];
    k = G.capacities();
    FF.k = new double[FF.ap_size];
    FF.flow_x = new double[G.num_edges()];
    for(i=0;i<FF.ap_size;i++) FF.flow_x[i]=0;
    FF.k_p = new double[2*FF.ap_size];
    for(i=0;i<FF.ap_size;i++){
        FF.a_p1[2*i] = x[i];
        FF.a_p2[2*i] = y[i];
        FF.a_p1[2*i+1] = y[i];
        FF.a_p2[2*i+1] = x[i];
        FF.k[i] = k[i];
    }
    Q = stack(G.num_nodes());
    pred = new int[G.num_nodes()];
    e = new double[G.num_nodes()];
    if(ford_fulkerson_alg(s,t,G.num_nodes())==-1){
        printf("\n--Error performing Ford Fulkerson Algorithm!--");
    }
    else{
        printf("\n---- <Results> ----\n\nOptimal flow x: ");
        for(i=0;i<FF.ap_size;i++){ 
            if(i%5==0) printf("\n");
            printf(" x(%d, %d): %.2f ",x[i],y[i],FF.flow_x[i]);
        }
        printf("\n* Max Flow Value: %.3f", max_flow);
        printf("\n* # of iterations: %d\n", FF.num_iter);
    }
}

int ford_fulkerson_alg(int s, int t, int n){
    FF.num_iter = 0;
    FF.opt = false;
    while(!FF.opt){
        FF.num_iter++;
        //e vector initialized
        for(i=0;i<n;i++)e[i]=1e7; 
        //k_p value update
        for(i=0;i<FF.ap_size;i++){
            FF.k_p[2*i] = FF.flow_x[i];
            FF.k_p[2*i+1] = k[i]-FF.flow_x[i];
            FF.k[i] = k[i];
        }
        //Verbose info for every iteration
        if(FF.verbose==true) printf("\n----- Iteration #%d -----\n",FF.num_iter);
        if(FF.verbose==true) printf("\n   -- a_p1: ");
        for(i=0;i<2*FF.ap_size;i++) if(FF.verbose==true) printf("%d    ", FF.a_p1[i]);
        if(FF.verbose==true) printf("\n   -- a_p2: ");
        for(i=0;i<2*FF.ap_size;i++) if(FF.verbose==true) printf("%d    ", FF.a_p2[i]);
        if(FF.verbose==true) printf("\n   -- k_p : ");
        for(i=0;i<2*FF.ap_size;i++) if(FF.verbose==true) printf("%.2f ", FF.k_p[i]);
        //refresh of predecessor vec
        for(i=0;i<n;i++) pred[i]=-1;
        pp = s;
        tmp = 0;
        while(pp!=null){
            for(i=0;i<FF.ap_size;i++){
                tmp = FF.a_p1[2*i];
                if(pp==tmp && FF.k_p[2*i]< FF.k[i]){
                    if(pred[FF.a_p2[2*i]]==-1){
                        pred[FF.a_p2[2*i]]=pp;
                        push(&Q,FF.a_p2[2*i]);
                    }
                    if(e[pp] > FF.k[i]-FF.k_p[2*i]){
                        e[FF.a_p2[2*i]] = FF.k[i]-FF.k_p[2*i];
                    }else{
                        e[FF.a_p2[2*i]] = e[pp];
                    }
                }
            }
            for(i=0;i<FF.ap_size;i++){
                tmp = FF.a_p1[2*i+1];
                if(pp==tmp && FF.k_p[2*i+1]<FF.k[i]){
                    if(pred[FF.a_p2[2*i+1]]==-1){
                        pred[FF.a_p2[2*i+1]]=pp;
                        push(&Q,FF.a_p2[2*i+1]);
                    }
                    if(e[pp] > FF.k_p[2*i+1] && FF.k_p[2*i+1]> 0){
                        e[FF.a_p2[2*i+1]] = FF.k_p[2*i+1];
                    }else{
                        e[FF.a_p2[2*i+1]] = e[pp];
                    }
                }
            }  
            pp = pop(&Q);
        }
        FF.delta = e[t];
        if(pred[t]!=-1){
            if(FF.verbose==true) printf("\n  -> Delta: %f",FF.delta);
            max_flow+=FF.delta;
            fr = t;
            if(FF.verbose==true) printf("\nPath: %d ",t);
            while(fr!=s){
                to = pred[fr];
                if(FF.verbose==true) printf(" <- %d ",to);
                if(to>=0){
                    for(i=0;i<2*FF.ap_size;i++)
                        if(FF.a_p1[i]==fr && FF.a_p2[i]==to)
                            FF.flow_x[i/2] += FF.delta;
                }
                fr=to;
            }
            if(FF.verbose==true) printf("\n---> Actual flow_x: ");
            for(i=0;i<FF.ap_size;i++)
                if(FF.verbose==true) printf("%.2f ", FF.flow_x[i]);
        }
        else
            FF.opt = true;
        if(FF.verbose==true) printf("\n\n");
    }
    return 0;
}

