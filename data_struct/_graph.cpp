#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class _graph{
    int v_num, a_num, *indx, *edges; 
    double *cap;
    public:
        //star representation, index starts at 0 pls
        _graph(int vN, int aN, int in[] , int ed[], double ca[]){
            v_num = vN;
            a_num = aN;
            indx = new int[vN];
            for(int i=0;i<vN;i++) indx[i] = in[i];
            edges = new int[aN];
            for(int i=0;i<aN;i++) {edges[i] = ed[i];}
            cap = new double[aN];
            for(int i=0;i<aN;i++) cap[i] = ca[i];
        }
        _graph(char * file){
            FILE * fp = fopen(file, "r");
            if(fp==NULL){
                printf("-- ERROR reading file! --");
            }
            fscanf(fp,"%d",&v_num);
            fscanf(fp,"%d",&a_num);
            for(int i = 0; i < 3; i++){
                if(i==0){
                    indx = new int[v_num];
                    for(int j=0;j<v_num;j++){
                        fscanf(fp,"%d",&indx[j]);
                    }
                }
                if(i==1){
                    edges = new int[a_num];
                    for(int j=0;j<a_num;j++){
                        fscanf(fp,"%d",&edges[j]);
                    }
                }
                if(i==2){
                    cap = new double[a_num];
                    for(int j=0;j<a_num;j++){
                        fscanf(fp,"%lf",&cap[j]);
                    }
                }
            }
            fclose(fp);
            printf("\n-- File succesfully imported! --\n");
        }
        //Returns incidence matrix of graph G as a v_num*a_num matrix
        int ** inc_matrix(){
            int inc_mat[v_num][a_num];
            for(int i = 0;i < v_num; i++){
                for(int j = 0; j < a_num ; j++){
                    if(j >= indx[i] && j < indx[i+1])
                        inc_mat[i][j] = 1;
                    else
                        inc_mat[i][j] = 0;
                }
            }
            return (int **) inc_mat;
        }

        //Returns adjacency matrix of graph G as a v_num*v_num matrix
        int ** adj_matrix(){
            int adj_mat[v_num][a_num];
            for(int i = 1;i < v_num; i++){
                for(int j = 0; j < v_num ; j++){
                    if(j >= indx[i-1] && j < indx[i])
                        adj_mat[i-1][edges[j]] = 1;
                    else
                        adj_mat[i-1][edges[j]] = 0;
                }
            }
            return (int **) adj_mat;
        }

        //Returns a a_num matrix with element [from] for every row i = 1,...,a_num
        int * exp_edges(){
            int * exp_e;
            exp_e = new int[a_num];
            //printf("\nExtended edges:\n");
            for(int i = 1;i < v_num; i++){
                for(int j = 0; j < a_num ; j++){
                    if(j >= indx[i-1] && j < indx[i]){
                        exp_e[j] = i-1;
                    }
                }
            }
            return exp_e;

        }
        double * capacities(){
            return cap;
        }

        int * edg(){
            return edges;
        }

        int num_edges(){
            return a_num;
        }

        int num_nodes(){
            return v_num;
        }

};