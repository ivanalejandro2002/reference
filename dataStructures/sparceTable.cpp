//C++20+ -> bit_width
//#define bit_width(S) 64-__builtin_clzll(S)
struct SparseTable{
    vector<vector<long long> > st;
    int n;
    long long nul_v;
    int K;

    long long f(long long a, long long b){
        return a + b;
    }

    SparseTable(vector<long long> &data, long long _nullv = 0){
        n = data.size();
        nul_v = _nullv;
        st.resize(bit_width((unsigned long)n),vector<long long>(n));

        K = bit_width((unsigned long)n) -1;
        copy(data.begin(),data.end(),st[0].begin());
        for(int i = 1; i <= K; ++i)
            for(int j = 0; j + (1 << i) <= n; ++j)
                st[i][j] = f(st[i-1][j], st[i-1][j + (1 << (i-1))]);
    }

    //op == 0 hace la consulta O(log(n)= para operaciones que no representan el patrón RMQ
    //op == 1 permite las queries en O(1) solo cuando hay operaciones de tipo RMQ
    long long query(int l, int r, bool op = 0){
        if(op){
            int i = bit_width((unsigned long)(r - l) + 1) - 1;
            return f(st[i][l], st[i][r - (1 << i) + 1]);
        }else{
            long long s = nul_v;

            for(int i = K; i >= 0; --i){
                if((1 << i) <= r - l + 1){
                    s = f(s, st[i][l]);
                    l += 1<<i;
                }
            }
            return s;
        }
    }

};