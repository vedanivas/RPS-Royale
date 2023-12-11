#include <bits/stdc++.h>
using namespace std;

vector<int> in[30];
vector<vector<int>> out(1000, vector<int> (3));
vector<char> in_s;
vector<char> out_s;
vector<set<int>> state_s;

int s_n = 0;

int max(set<int> r, set<int> p, set<int> s)
{
  int size_r = r.size();
  int size_p = p.size();
  int size_s = s.size();

  if(size_r >= size_p && size_r >= size_s) return 0;
  if(size_p >= size_r && size_p >= size_s) return 1;
  if(size_s >= size_p && size_s >= size_r) return 2;
  return -1;
}

char c_ret(char a)
{
  if (a == 'R') return 'P';
  if (a == 'P') return 'S';
  if (a == 'S') return 'R';
  return '\0';
}

char c_ret_i(int a)
{
  if (a == 0) return 'P';
  if (a == 1) return 'S';
  if (a == 2) return 'R';
  return '\0';
}

int i_ret(char a)
{
  if (a == 'R') return 0;
  if (a == 'P') return 1;
  if (a == 'S') return 2;
  return -1;
}

int find_s(set<int> st)
{
  int i = 0, f = 0;
  for (auto it : state_s)
  {
    if (it == st) 
    {
      f = 1;
      break;
    }
    i++;
  }
  
  return f == 1 ? i : -1;
}

int visit(int in_i, int out_i, int n)
{
  int vis[n];
  for (auto &it : vis) it = 0;
  
  int tran_i = in[in_i - 1][i_ret(out_s[out_i - 1])];
  out_s.push_back(c_ret(in_s[tran_i - 1]));
  s_n++;
  out[out_i - 1][i_ret(in_s[in_i - 1])] = s_n;
  
  in_i = tran_i;
  out_i = s_n;
  vis[in_i - 1] = out_i;
  while(1)
  {
    tran_i = in[in_i - 1][i_ret(out_s[out_i - 1])];
    if (vis[tran_i - 1]) break;
    out_s.push_back(c_ret(in_s[tran_i - 1]));
    s_n++;
    out[out_i - 1][i_ret(in_s[in_i - 1])] = s_n;
    in_i = tran_i;
    out_i = s_n;
    vis[in_i - 1] = out_i;
  }
  out[out_i - 1][i_ret(in_s[in_i - 1])] = vis[tran_i - 1];
  
  state_s.clear();

  return 0;
}

int recur(int out_i, int n, set<int> st)
{
  if (st.empty()) return 0;
  if (st.size() == 1)
  {
    visit(*(st.begin()), out_i, n);
    return 0;
  }
  
  set<int> set_s[3];
  auto it = st.begin();
  int a, b;
  while(it != st.end())
  {
    a = *(it);
    b = in[a - 1][i_ret(out_s[out_i - 1])];
    set_s[i_ret(in_s[b - 1])].insert(b);
    it++;
  }

  int max_s = max(set_s[0], set_s[1], set_s[2]);
  
  int ind = find_s(set_s[max_s]);
  if (ind != -1) 
  {
    out[out_i - 1][i_ret(in_s[*(st.begin()) - 1])] = s_n - (state_s.size() - ind - 1);

    state_s.clear();

    return 0;
  }

  out_s.push_back(c_ret_i(max_s));
  s_n++;
  out_i = s_n;
  for (int i = 0; i < 3; i++)
  {  
    if (!set_s[(max_s + i) % 3].empty()) 
    {
      out[out_i - 1][(max_s + i) % 3] = s_n + 1;

      state_s.push_back(set_s[(max_s + i) % 3]);
      recur(out_i, n, set_s[(max_s + i) % 3]);
    }
  }
  
  return 0;
}

int main(void)
{ 
  srand(time(0));

  int n, x, n_r = 0, n_p = 0, n_s = 0;
  cin >> n;

  char ch;

  set<int> set_s[3];
  for (int i = 0; i < n; i++)
  {
    cin >> ch;
    in_s.push_back(ch);
    if (ch == 'R') set_s[0].insert(i + 1);
    if (ch == 'P') set_s[1].insert(i + 1);
    if (ch == 'S') set_s[2].insert(i + 1);
    for (int j = 0; j < 3; j++)
    {
      cin >> x;
      in[i].push_back(x);
    }
  }
  
  int max_s = max(set_s[0], set_s[1], set_s[2]);
  out_s.push_back(c_ret_i(max_s));
  s_n++;
  for (int i = 0; i < 3; i++)
  {  
    if (!set_s[(max_s + i) % 3].empty()) 
    {
      out[0][(max_s + i) % 3] = s_n + 1;

      state_s.push_back(set_s[(max_s + i) % 3]);
      recur(1, n, set_s[(max_s + i) % 3]);
    }
  }

  cout << s_n << endl;
  for (int i = 0; i < s_n; i++)
  {;
    int b = out[i][0];
    if (!b) b = (rand() % s_n) + 1;
    int c = out[i][1];
    if (!c) c = (rand() % s_n) + 1;
    int d = out[i][2];
    if (!d) d = (rand() % s_n) + 1;
  
    cout << out_s[i] << " " << b << " " << c << " " << d << endl;
  }
}
