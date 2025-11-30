#include <iostream>
using namespace std;

#define INF 999999

int n;
int adj[20][20];

void bfs(int start) {
    int q[20], front = 0, rear = 0;
    int visited[20];
    for (int i = 0; i < n; i++) visited[i] = 0;

    visited[start] = 1;
    q[rear++] = start;

    cout << "BFS: ";
    while (front < rear) {
        int u = q[front++];
        cout << u << " ";
        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0 && visited[v] == 0) {
                visited[v] = 1;
                q[rear++] = v;
            }
        }
    }
    cout << endl;
}

void dfsUtil(int u, int visited[]) {
    visited[u] = 1;
    cout << u << " ";
    for (int v = 0; v < n; v++) {
        if (adj[u][v] != 0 && visited[v] == 0)
            dfsUtil(v, visited);
    }
}

void dfs(int start) {
    int visited[20];
    for (int i = 0; i < n; i++) visited[i] = 0;
    cout << "DFS: ";
    dfsUtil(start, visited);
    cout << endl;
}

void primMST() {
    int selected[20];
    int no_edge = 0;
    for (int i = 0; i < n; i++) selected[i] = 0;

    selected[0] = 1;
    cout << "Prim MST edges:\n";
    while (no_edge < n - 1) {
        int min = INF;
        int x = -1, y = -1;
        for (int i = 0; i < n; i++) {
            if (selected[i] == 1) {
                for (int j = 0; j < n; j++) {
                    if (selected[j] == 0 && adj[i][j] != 0 && adj[i][j] < min) {
                        min = adj[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }
        if (x == -1) break;
        cout << x << " " << y << " " << adj[x][y] << "\n";
        selected[y] = 1;
        no_edge++;
    }
}

int findParent(int parent[], int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int parent[], int x, int y) {
    int px = findParent(parent, x);
    int py = findParent(parent, y);
    parent[px] = py;
}

void kruskalMST() {
    struct Edge { int u, v, w; };
    Edge edges[400];
    int e = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j] != 0) {
                edges[e].u = i;
                edges[e].v = j;
                edges[e].w = adj[i][j];
                e++;
            }
        }
    }

    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - 1 - i; j++) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int parent[20];
    for (int i = 0; i < n; i++) parent[i] = i;

    cout << "Kruskal MST edges:\n";
    int count = 0;
    int k = 0;
    while (count < n - 1 && k < e) {
        int u = edges[k].u;
        int v = edges[k].v;
        int w = edges[k].w;
        int pu = findParent(parent, u);
        int pv = findParent(parent, v);
        if (pu != pv) {
            cout << u << " " << v << " " << w << "\n";
            unionSet(parent, pu, pv);
            count++;
        }
        k++;
    }
}

void dijkstra(int src) {
    int dist[20];
    int visited[20];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int c = 0; c < n - 1; c++) {
        int u = -1;
        int min = INF;
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0 && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0 && visited[v] == 0) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    cout << "Dijkstra distances from " << src << ":\n";
    for (int i = 0; i < n; i++) {
        cout << i << " " << dist[i] << endl;
    }
}

int main() {
    int i, j, start;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter adjacency matrix:\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    cout << "Enter start vertex: ";
    cin >> start;

    bfs(start);
    dfs(start);
    primMST();
    kruskalMST();
    dijkstra(start);

    return 0;
}
