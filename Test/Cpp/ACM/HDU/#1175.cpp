//dfs 

#include <iostream>
#include <cstring>
using namespace std;
#define max 1000

int mp[max][max], vis[max][max];
int n, m, asr, x1, y1, x2, y2;

bool ck(int x, int y)
{
    if (x>=0 && x<n && y>=0 && y<m)
        return true;
    else return false;
}

void dfs(int x, int y, int t, int ag)
{
    if (ag>2) return;
    if (x!=x1 || y!=y1)
    {
        if ((x!=x2 || y!=y2) && mp[x][y]!=0) return;
        if (ag==2 && x!=x2 && y!=y2) return;
    }
    if (x==x2 && y==y2)
    {
        asr = 1;
        return;
    }
    int next[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    for (int i=0; i<4; i++)
    {
        int nx, ny;
        nx = x + next[i][0];
        ny = y + next[i][1];
        if (ck(nx, ny) && !vis[nx][ny])
        {
            if (x==x1 && y==y1)
            {
                vis[nx][ny] = 1;
                dfs(nx, ny, i, ag);
                vis[nx][ny] = 0;
            }
            else
            {
                vis[nx][ny] = 1;
                if (t!=i)
                    dfs(nx, ny, i, ag+1);
                else
                    dfs(nx, ny, i, ag);
                vis[nx][ny] = 0;
            }
        }
    }
}

int main()
{
    while (cin>>n>>m)
    {
        if (0==n || 0==m)
        {
            break;
        }
        else
        {
            for (int i = 0; i<n; i++)
            {
                for (int j = 0; j<m; j++)
                {
                    cin >> mp[i][j];
                } 
            }

            int q;
            cin >> q;
            for (int i = 0; i<q; i++)
            {
                asr = 0;
                memset(vis, 0, sizeof(vis));
                cin >> x1 >> y1 >> x2 >> y2;
                x1--; y1--; x2--; y2--;
                if (mp[x1][y1]==mp[x2][y2] && mp[x1][y1]!=0)
                {
                    dfs(x1, y1, 0, 0);
                    if(asr)
                    {
                        cout << "YES" << endl;
                    }
                    else
                    {
                        cout << "NO" << endl;
                    }
                }
                else cout << "NO" << endl;
            }
        }
    }    
    return 0;
}
