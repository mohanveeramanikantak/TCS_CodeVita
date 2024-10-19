#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;
struct Cell 
{
    int x, y, dist;
};
bool isValid(int x, int y, int M, int N, vector<vector<int>>& grid, vector<vector<bool>>& visited) 
{
    return (x >= 0 && x < M && y >= 0 && y < N && grid[x][y] == 0 && !visited[x][y]);
}
int bfs(int M, int N, vector<vector<int>>& grid, pair<int, int> src, pair<int, int> dest, pair<int, int> moveRule) {
    vector<pair<int, int>> directions = {
        {moveRule.first, moveRule.second},
        {moveRule.second, -moveRule.first},
        {-moveRule.second, moveRule.first},
        {-moveRule.first, -moveRule.second}
    };

    queue<Cell> q;
    vector<vector<bool>> visited(M, vector<bool>(N, false));

    q.push({src.first, src.second, 0});
    visited[src.first][src.second] = true;

    while (!q.empty()) 
    {
        Cell current = q.front();
        q.pop();

        if (current.x == dest.first && current.y == dest.second) 
        {
            return current.dist;
        }

        for (auto dir : directions) 
        {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            if (isValid(newX, newY, M, N, grid, visited)) 
            {
                visited[newX][newY] = true;
                q.push({newX, newY, current.dist + 1});
            }
        }
    }
    return -1;
}
int main() 
{
    int M, N;
    cin >> M >> N;
    vector<vector<int>> grid(M, vector<int>(N));
    for (int i = 0; i < M; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cin >> grid[i][j];
        }
    }
    pair<int, int> src, dest;
    cin >> src.first >> src.second;
    cin >> dest.first >> dest.second;
    pair<int, int> moveRule;
    cin >> moveRule.first >> moveRule.second;
    int result = bfs(M, N, grid, src, dest, moveRule);
    cout << result << endl;
    return 0;
}

