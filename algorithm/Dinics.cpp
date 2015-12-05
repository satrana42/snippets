// Taken from http://shygypsy.com/tools/flow2.cpp
#include <bits/stdc++.h>
using namespace std;
// the maximum number of vertices
#define NN 5005

// adjacency matrix (fill this up)
// If you fill adj[][] yourself, make sure to include both u->v and v->u.
int cap[NN][NN], deg[NN], adj[NN][NN];

// BFS stuff
int q[NN], prv[NN];

int dinic( int n, int s, int t ){	
	 // init the adjacency list adj[][] from cap[][]
    memset( deg, 0, sizeof( deg ) );
    for( int u = 0; u < n; u++ )
        for( int v = 0; v < n; v++ ) if( cap[u][v] || cap[v][u] )
            adj[u][deg[u]++] = v;

    int flow = 0;

    while(true){
        // find an augmenting path
        memset( prv, -1, sizeof( prv ) );
        int qf = 0, qb = 0;
        prv[q[qb++] = s] = -2;
        while( qb > qf && prv[t] == -1 )
            for( int u = q[qf++], i = 0, v; i < deg[u]; i++ )
                if( prv[v = adj[u][i]] == -1 && cap[u][v] )
                    prv[q[qb++] = v] = u;

        // see if we're done
        if( prv[t] == -1 ) break;

        // try finding more paths
        for( int z = 0; z < n; z++ ) if( cap[z][t] && prv[z] != -1 ){
            int bot = cap[z][t];
            for( int v = z, u = prv[v]; u >= 0; v = u, u = prv[v] )
                bot = min(bot, cap[u][v]);
            if( !bot ) continue;

            cap[z][t] -= bot;
            cap[t][z] += bot;
            for( int v = z, u = prv[v]; u >= 0; v = u, u = prv[v] )
            {
                cap[u][v] -= bot;
                cap[v][u] += bot;
            }
            flow += bot;
        }
    }

    return flow;
}

int main()
{
    // read a graph into cap[][]
    memset( cap, 0, sizeof( cap ) );
    int n, m;
    scanf( " %d %d", &n, &m );
    while( m-- ){
        int u, v, c; scanf( " %d %d %d", &u, &v, &c );
        u--; v--; cap[u][v] += c; cap[v][u] += c;
    }

    printf( "%d\n", dinic( n, 0, n-1 ) );
    return 0;
}