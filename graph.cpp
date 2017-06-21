#include "graph.h"


graph::graph(int v){//Construtor da classe graph.
  vertex = v;//numero de vertices.
  degree = (int*)malloc(sizeof(int)*v);//grau dos vertices do atuais no grafo
  visited = (int*)malloc(sizeof(int)*v);//graus visitados pela BFS
  bpAux = new list<int>[v];//lista auxiliar da best path
  bfs = new list<int>[v];//lista auxiliar da BFS
  bp = new queue<int>;//Fila de armazenamento do Best Path
  for(int i=0;i<v;i++){//zerando o vetor de graus e visitados
    degree[i]=0;
    visited[i]=0;
  }
}

void graph::addEdge(int to,int from){//to e from são os dois vertices que formam a aresta
  adjMtx.push_back(make_pair(to,from));//adiciona um vertice manualmente
}

void graph::showEdges(){//mostra as arestas atuais no grafo na maneira "1-2"
  int vectorSize = adjMtx.size();//pega o tamanho do vetor de arestas
  for(int i=0;i<vectorSize;i++){//percorre o vetor de arrestas inteiro
    cout<<adjMtx[i].first<<"-"<<adjMtx[i].second<<endl;
    /*Como o vetor armazena as arestas num par o indicador first e second
    nativos da linguagem c++*/
  }
}

void graph::calcEdgeDegree(){/*calcula o grau da dos vertices, somando para cada +1
  para cada vez que encontra o vertice no vetor de arestas*/
  for(int i=0;i<vertex;i++){//zera o vetor de graus
    degree[i]=0;
  }
  int vectorSize = adjMtx.size();
  for(int i=0;i<vectorSize;i++){//soma +1 para cada vez que encontra
    degree[adjMtx[i].first]+=1;
    degree[adjMtx[i].second]+=1;
  }
}

void graph::showDegree(){//mostra os graus na tela
  calcEdgeDegree();//caso o array de graus ainda não esteja setado
  for(int i=0;i<vertex;i++){
    cout<<i<<":"<<degree[i]<<endl;
  }
}

void graph::runBFS(int v){//roda a bfs a partir do vertice v
  int vectorSize = adjMtx.size();//pega o tamanho do vector usado para matrix adjacente
  queue<int> thatFila;//fila auxiliar
  for(int i=0;i<vectorSize;i++){
    bfs[adjMtx[i].first].push_back(adjMtx[i].second);
  }
  list<int>::iterator itBFS;
  visited[v]=1;
  while(true){//loop "infinito" para percorrer toda os membros disponiveis
    for(itBFS=bfs[v].begin();itBFS!=bfs[v].end();itBFS++){//percorre todos os vertices adjacentes do vertice determinado
      if(visited[*itBFS]==0){
          visited[*itBFS] = 1;//marca o vertice como visitado
          thatFila.push(*itBFS);//coloca na fila a posição marcada
      }
    }
    if(!thatFila.empty()){//se a fila não estiver vazia
      v=thatFila.front();//pega o topo da fila e seta para v
      thatFila.pop();//tira o mesmo elemento da fila//
    }else{
      break;//caso a fila estiver vazia, sai do loop "infinito"
    }
  }
}

void graph::showVisited(){//mostra os vertices visitados pela bfs
  runBFS(0);
  for(int i=0;i<vertex;i++){
    cout<<i<<"-"<<visited[i]<<endl;
  }
}
int graph::testConnected(int calc,int start){//testa se o grafo é conexo a partir do start
  runBFS(start);//roda a bfs
  if(calc == 1){//se for necessario recalcular os graus antes da execução
    calcEdgeDegree();
  }
  for(int i=0;i<vertex;i++){
    if((degree[i]>0)&&(visited[i]==0)){//se o vertice for valido ou seja ainda tiver arestas e não for visitado o grafo esta disconexo
            return 0;
    }
  }
    return 1;
}

int graph::testBridge(int to,int from){//testa se a aresta to e from formam uma ponte
  int i;
  int vectorSize = adjMtx.size();
  for(i=0;i<vectorSize;i++){
    if((adjMtx[i].first == to)&&(adjMtx[i].second == from)){//localiza a aresta em questão
      break;
    }
  }
  //calcEdgeDegree();//remove when test best path.
  adjMtx.erase(adjMtx.begin()+i);//apaga a aresta teste
  if(testConnected(0,to)==0){//verifica se o grafo fica desconexo
    //cout<<"ponte"<<endl;
    adjMtx.push_back(make_pair(to,from));//devolve a aresta pro vetor
    return 1;//retorna que é ponte
  }else{
  //  cout<<"so aresta"<<endl;
    adjMtx.push_back(make_pair(to,from));//devolve a aresta pro vetor
    return 0;//retorna que é só mais uma aresta em meio de muitas
  }

}
void graph::getEdgesFromFile(string archiveName){//metodo de leitura das arestas pelo arquivo de texto
  ifstream file(archiveName.c_str());
  if(!file.is_open()){
    cout<<"erro ao abrir arquivo"<<endl;
    return;
  }
  char c;
  string fullnumber = "";
  int to = -1;
  int from = -1;
  while((file.good())&&(file.get(c))){
    if((to == -1)&&(isdigit(c))){
      fullnumber = c;
    }else if(c==':'){
      istringstream(fullnumber)>>to;
      fullnumber="";
    }
    if((to != -1)&&(isdigit(c))){
      fullnumber += c;
    }
    if((to != -1)&&((c==' ')||(c=='\n'))&&(fullnumber!="")){
      istringstream(fullnumber)>>from;
      adjMtx.push_back(make_pair(to,from));
      fullnumber="";
    }
    if((c =='\n')&&(fullnumber=="")){
      to = -1;
      from = -1;
    }
  }
}
int graph::testAllEven(){//testa se todos os vertices são pares
    for(int i=0;i<vertex;i++){
      if(degree[i]%2!=0){
        return 0;
      }
    }
    return 1;
}
void graph::deleteEdge(int to, int from){//deleta determinada aresta do vetor
  vector<pair<int,int> >::iterator itDelete;
  for(itDelete=adjMtx.begin();itDelete!=adjMtx.end();itDelete++){
    if((itDelete->first==to)&&(itDelete->second==from)){
      adjMtx.erase(itDelete);
      return;
    }
  }
  calcEdgeDegree();
}


void graph::makeListBp(){//monta a lista auxiliar do best path
  vector<pair<int,int> >::iterator itbpAux;
  for(int i=0;i<vertex;i++){
    bpAux[i].clear();
  }
  for(itbpAux=adjMtx.begin();itbpAux!=adjMtx.end();itbpAux++){
    bpAux[itbpAux->first].push_back(itbpAux->second);
  }
}

void graph::invertEdge(int v){//inverte o to - from para a percorrer melhor o grafo
  vector<pair<int,int> >::iterator it;
  for(it=adjMtx.begin();it!=adjMtx.end();it++){
    if(it->second == v){
      it->second = it->first;
      it->first = v;
    }
  }
}

void graph::bpAuxRec(int start,int finalStart){//metodo recursivo para percorrer o grafo armazanando o caminho na Fila
  calcEdgeDegree();
  int degrees=0;
  for(int i=0;i<vertex;i++){
    degrees += degree[i];
  }
  bp->push(start);
  if((degrees==0)&&(start==finalStart)){//condição de parada do metodo
    cout<<"Finished With Sucess"<<endl;
    return;
  }else{
    invertEdge(start);
    makeListBp();
    list<int>::iterator itbpList;
    /*for(int i=0;i<vertex;i++){
      for(itbpList=bpAux[i].begin();itbpList!=bpAux[i].end();itbpList++){
          cout<<i<<"-"<<*itbpList<<endl;
        }
      }*/
      int thisDegree = degree[start];
      int next = -1;
      if(thisDegree > 1){
        for(itbpList=bpAux[start].begin();itbpList!=bpAux[start].end();itbpList++){
          if((next == -1)&&(testBridge(start,*itbpList)==0)){
            next = *itbpList;
          }else if((degree[next]<degree[*itbpList])&&(testBridge(start,*itbpList)==0)){
            next = *itbpList;
          }
        }
        deleteEdge(start,next);
        bpAuxRec(next,finalStart);
      }else if(thisDegree == 1){
        itbpList = bpAux[start].begin();
        next = *itbpList;
        deleteEdge(start,next);
        bpAuxRec(next,finalStart);
      }else{
        return;
      }
  }
}

void graph::runBestPath(int start){//preparação dos para rodar o best path
  cout<<"iniciando pre testes"<<endl;
  if(testConnected(1,0)==0){//testa se o grafo é conexo
    cout<<"O Grafo precisa ser conexo para o BEST PATH funcionar!"<<endl;
    return;
  }
  if(testAllEven()==0){//testa se todos os vertices são grau par
    cout<<"Todos os Vertices precisam ter grau para o BEST PATH funcionar!"<<endl;
    return;
  }
  cout<<"pre testes concluidos..."<<endl;
  cout<<"INICIANDO"<<endl;
  bpAuxRec(start,start);//começa a percorrer o grafo pelo melhor caminho,segundo PCC com o começo setado pelo usuario
}

void graph::showBP(){//usa uma pilha auxiliar para mostrar o caminho percorrido para o best path
  queue<int> aux;
  int v;
  if(bp->empty()){
    runBestPath(1);
    while(!bp->empty()){
      v = bp->front();
      aux.push(v);
      bp->pop();
    }
    while(!aux.empty()){
      v = aux.front();
      cout<<v<<"-";
      bp->push(v);
      aux.pop();
    }
    cout<<"FIM"<<endl;
  }else{
    while(!bp->empty()){
      v = bp->front();
      aux.push(v);
      bp->pop();
    }
    while(!aux.empty()){
      v = aux.front();
      bp->push(v);
      cout<<v<<"-";
      aux.pop();
    }
    cout<<"FIM"<<endl;
  }
}
