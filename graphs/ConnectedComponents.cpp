//#define all(S) S.begin(),S.end()
struct ConnectedComponents{
    vector<int> vis;
    vector<pair<int,int> > order;
    vector<int> dagComponent;
    stack<int> stored;
    int count;
    int act;

    ConnectedComponents(vector<vector<int> > &adj){
        vis.resize(adj.size());
        order.resize(adj.size());
        dagComponent.resize(adj.size());
        count = 0;
        act = 0;
    }

    //Si se requiere uno para grafos bidirigidos
    //añadir padre y checar si no es el padre cuando procesa v
    void tarjan(int nodo, vector<vector<int> > &adj){
        if(vis[nodo] > 0)return;

        vis[nodo] = 1;
        order[nodo].first = order[nodo].second = ++act;
        stored.push(nodo);

        for(int v: adj[nodo]){
            if(!vis[v]){
                tarjan(v, adj);
                order[nodo].second = min(order[nodo].second, order[v].second);
            }else{
                if(vis[v] == 1)
                    order[nodo].second = min(order[nodo].second, order[v].first);
            }
        }

        int current;
        if(order[nodo].first == order[nodo].second){
            count ++;
            do{
                current = stored.top();
                stored.pop();
                dagComponent[current] = count;
                vis[current] = 2;
            }while(current != nodo);
        }
    }

    //indexed indica si el arreglo es 0 indexado o 1 indexado (0 -> 0 indexado) (1 -> 1 indexado)
    //retorna lista de adjacencia 1 indexada
    vector<vector<int> > compress(vector<vector<int> > &adj, bool indexed = 1){
        for(int i = indexed; i<adj.size(); ++i)
            tarjan(i, adj);
        
        vector<vector<int> > compressed(count + 1);
        for(int u = indexed; u < adj.size(); ++u)
            for(int v: adj[u])
                if(dagComponent[u] != dagComponent[v])
                    compressed[dagComponent[u]].push_back(dagComponent[v]);
        
        for(int i = 1; i <= count; ++i){
            auto last = std::unique(all(compressed[i]));
            sort(all(compressed[i]));
            last = unique(all(compressed[i]));
            compressed[i].erase(last, compressed[i].end());
        }

        return compressed;
    }
};