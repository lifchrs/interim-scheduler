#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double; // or double, if TL is tight
using str = string; // yay python!

using pl = pair<ll,ll>;
using pd = pair<ld,ld>;

using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<ld>;
using vs = vector<str>;
using vpl = vector<pl>;
using vpd = vector<pd>;

// pairs
#define mp make_pair
#define f first
#define s second

#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define ins insert
#define ft front()
#define bk back()
#define pb push_back
#define eb emplace_back
#define pf push_front

#define lb lower_bound
#define ub upper_bound

#define F0R(i,a) for(ll i=0;i<a;i++)
#define FOR(i,a,b) for(ll i=a;i<b;i++)

#define nn << "\n"

vector<vl> classes(100); //the vendors that the ith needs to listen to
vector<pair<pl,vl>> groups(100); //the groups[vendor] gives the groups attending the vendor's activities.
bool needToDo[100][100];
ll doubleCheck[100];
set<ll> vens;

bool checkDone(){
  F0R(i,100) F0R(j,100) if(needToDo[i][j]) return 0;
  return 1;
}


int main(){
	ifstream cin("interim.in");
	ofstream cout("interim.out");
  str st;
  ll currVen = -1;


  vl teachersLeft(100);

  for(ll& i : teachersLeft) i = 2;

  for(auto& x : groups) x.first.first = 0;

  while(cin >> st){
    if(st == "start"){
      cin >> currVen;
      vens.ins(currVen);
    }else if(st == "end") continue;
    else{
      groups[currVen].s.pb(stoi(st));
      groups[currVen].f.s = currVen;
      groups[currVen].f.f++;
      classes[stoi(st)].pb(currVen);
      needToDo[stoi(st)][currVen] = 1;
    }
  }

  sort(rall(groups));

  /* ll cnt = 0; */
  F0R(i,100){
    if(groups[i].f.f == 0) continue;
    /* cnt++; */
    cout << groups[i].f.s << "       ";

    for(ll x : groups[i].s) cout << x << " ";
    cout nn;
  }
  /* cout << cnt nn; */
  /* The code above creates all of the groups and sorts them */

  vector<vector<vector<ll>>> timeTable; // timeTable[0][0][0] gives the first bunch of sessions, the first class, and the first interim




  /* while(!checkDone()){ */
  /*   delThis++; */
  /*   cout << delThis nn; */
  /*   vector<vl> yuh(100); */
  /*   timeTable.pb(yuh); */
  /*   for(pair<pl,vl>& grp : groups){ */
  /*     for(ll i : grp.s){ */
  /*       if(!needToDo[i][grp.f.s]) continue; */
  /*       if(teachersLeft[i] == 0) continue; */
  /*       else if(teachersLeft[i] > 0){ */
  /*         timeTable[timeRow][grp.f.s].pb(i); */
  /*         teachersLeft[i]--; */
  /*         needToDo[i][grp.f.s] = 0; */
  /*       } */
  /*     } */
  /*   } */
  /*   for(ll& i : teachersLeft) i = 2; */
  /*   timeRow++; */
  /* } */

  ll delThis = 0;

  while(delThis < 1000 && !checkDone()){
    delThis++;
    vector<vl> yuh(100);
    for(pair<pl,vl> grp : groups){
      for(ll i : grp.s){
        if(!needToDo[i][grp.f.s]) continue;
        if(teachersLeft[i] == 0) continue;
        else if(teachersLeft[i] < 0){
          cout << "SERIOUS ERROR HERE" nn;
          exit(0);
        }else{
          yuh[grp.f.s].pb(i);
          teachersLeft[i]--;
          needToDo[i][grp.f.s] = 0;
        }
      }
    }
    for(ll& i : teachersLeft) i = 2;
    timeTable.pb(yuh);
  }

  cout << "THIS : " << delThis nn;

  /* for(ll time = 1; time < sz(timeTable)+1; time++){ */
  /*   cout << time << ": " nn nn nn; */
  /*   ll v = 0; */
  /*   for(vl grp : timeTable[time-1]){ */
  /*     str b = "   "; */
  /*     if(sz(grp) == 0){ */
  /*       v++; continue; */
  /*     } */
  /*     /1* cout << b + "Vendor " << v; *1/ */
  /*     /1* cout << " meets with a teacher from the following course(s): " nn; *1/ */
  /*     cout << ","; */
  /*     b += b; */
  /*     /1* cout << b; *1/ */
  /*     for(ll i : grp) cout << i << " "; */
  /*     cout nn; */
  /*     v++; */
  /*   } */
  /* } */

  for(ll time = 1; time < sz(timeTable)+1; time++){
    cout << time << ": " nn nn nn;
    ll v = 0;
    for(vl grp : timeTable[time-1]){
      str b = "   ";
      if(sz(grp) == 0){
        v++; continue;
      }
      cout << "Vendor #" << v << ",";

      /* b += b; */
      /* /1* cout << b; *1/ */
      /* for(ll i : grp) cout << i << " "; */
      /* cout nn; */

      v++;
    }

    cout nn nn nn nn;

    for(vl grp : timeTable[time-1]){
      str b = "   ";
      if(sz(grp) == 0){
        v++; continue;
      }
      /* cout << b + "Vendor " << v; */
      /* cout << " meets with a teacher from the following course(s): " nn; */
      cout << ";";
      b += b;
      /* cout << b; */
      ll cnt = 0;
      for(ll i : grp){
        doubleCheck[i]++;
        if(doubleCheck[i] > 3){
          cout  nn nn nn nn "TOO MANY TEACHERS" nn nn nn nn nn ;
        }
        cnt++;
        if(cnt != sz(grp)) cout << i << ", "; else cout << i ;
      }
      cout nn;
      v++;

    }
    cout nn;
    for(ll& i : doubleCheck){
      cout << i << " ";
      i = 0;
    }
    cout nn;
  }



  /* cout nn nn nn; */
  /* cout << "The vendors are :"; */
  /* for(ll i : vens){ */
  /*   cout << "vendor #" << i << ", "; */
  /* } */
  /* cout nn; */


}
