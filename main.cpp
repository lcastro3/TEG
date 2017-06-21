#include "graph.h"

int main(){
  int v;
  string archiveName;
  cout<<"Digite o numero de vertices do grafo"<<endl;
  cin>>v;
  graph g(v);
  cout<<"Digite o nome do arquivo que deseja abrir"<<endl;
  g.getEdgesFromFile("entrada.txt");
  while(v!=-1){
    cout<<"digite 1 para ver as arestas"<<endl;
    cout<<"digite 2 para ver os graus dos vertices"<<endl;
    cout<<"digite 3 para ver vertices visitados"<<endl;
    cout<<"digite 4 para ver Best Path"<<endl;
    cout<<"digite 5 sair"<<endl;
    cin>>v;
    if(v==1){
      g.showEdges();
    }else if(v==2){
      g.showDegree();
    }else if(v==3){
      g.showVisited();
    }else if(v==4){
      g.showBP();
    }else if(v==5){
      return 0;
    }
  }
}
