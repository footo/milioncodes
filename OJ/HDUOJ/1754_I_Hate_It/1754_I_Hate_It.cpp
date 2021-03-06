#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))
#define PB push_back
#define GU(a, b) if ((a)>(b)) (b)=(a);
#define SU(a, b) if ((a)<(b)) (b)=(a);
#define MID(a, b) (((a)+(b))>>1)

const int N = 200005;

struct Tree {
	int l, r, maxa;
	int ch[2];
	void init(int *a, int l0, int r0) {
		l=l0; r=r0;
		ch[0]=ch[1]=0;
		maxa=(l==r)?a[l]:0;
	}
	void push_up();
} mem[N*4];

int root, cnt;

void Tree::push_up() {
	maxa=max(mem[ch[0]].maxa,mem[ch[1]].maxa);
}

int build(int T, int *a, int l, int r) {
	mem[T=cnt++].init(a, l, r);
	Tree &tr = mem[T];
	int m = MID(l, r);
	if (l<r) {
		tr.ch[0]=build(tr.ch[0], a, l, m);
		tr.ch[1]=build(tr.ch[1], a, m+1, r);
		tr.push_up();
	}
	return T;
}

int query(int T, int l, int r) {
	Tree &tr = mem[T];
	if (tr.l>=l&&tr.r<=r) return tr.maxa;
	int m = MID(tr.l, tr.r), ret=0;
	if (l<=m) ret=max(ret, query(tr.ch[0], l, r));
	if (r>m) ret=max(ret, query(tr.ch[1], l, r));
	return ret;
}

void modify(int T, int x, int val) {
	Tree &tr = mem[T];
	if (tr.l==tr.r) tr.maxa=val;
	else {
		if (x>MID(tr.l, tr.r)) modify(tr.ch[1], x, val);
		else modify(tr.ch[0], x, val);
		tr.push_up();
	}
}

int a[N];
char op[3];

int main() {
	int n, q;
	while (scanf("%d%d", &n, &q)!=EOF) {
		cnt=1; root=0;
		FOREQ(i, 1, n) scanf("%d", &a[i]);
		root=build(root, a, 1, n);
		REP(i, q) {
			scanf("%s", op);
			int x, y; scanf("%d%d", &x, &y);
			if (op[0]=='Q') printf("%d\n", query(root, x, y));
			else modify(root, x, y);
		}
	}
	return 0;
}
