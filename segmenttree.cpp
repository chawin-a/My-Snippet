#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 1e5;

template<typename T>
struct SegmentTree {
	vector<T> tree;
	int n;
	T inf;
	SegmentTree(int n) : n(n) {
		tree.resize(4 * n);
	}
	SegmentTree(int n, T inf) : n(n), inf(inf) {
		tree.resize(4 * n, inf);
	}
	SegmentTree(vector<T> v, T inf) : inf(inf) {
		n = v.size();
		tree.resize(4 * n, inf);
		build(1, n, 1, v);
	}

	T combine(T a, T b) {
		return min(a, b); // compare !!! pls modify this.
	}
	void build(int s, int e, int i, vector<T> &v) {
		if(s == e) {
			tree[i] = v[s-1];
			return;
		}
		int m = s + ((e - s) >> 1);
		int child = i<<1;
		build(s, m, child, v);
		build(m+1, e, child|1, v);
		tree[i] = combine(tree[child], tree[child|1]);
	}
	T queryUtil(int l, int r, int s, int e, int i) {
		if(l>e || r<s) {
			return inf;
		}
		if(l <= s && e <= r) {
			return tree[i];
		}
		int m = s + ((e - s) >> 1);
		int child = i << 1;
		return combine(queryUtil(l, r, s, m, child), queryUtil(l, r, m+1, e, child|1));
	}
	T query(int l, int r) {
		return queryUtil(l, r, 1, n, 1);
	}
	T query(int idx) {
		return queryUtil(idx, idx, 1, n, 1);
	}
	void updateUtil(int s, int e, int i, int idx, T val) {
		if(s == e) {
			tree[i] = val;
			return;
		}
		int m = (s + e) / 2;
		if(idx <= m) update(s, m, i*2, idx, val);
		else update(m+1, e, i*2+1, idx, val);
		tree[i] = combine(tree[i*2], tree[i*2+1]);
	}
	void update(int idx, T val) {
		updateUtil(1, n, 1, idx, val);
	}
};

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int tree[4 * MAXN] = {};

void build(int s, int e, int i) {
	if(s == e) {
		tree[i] = arr[s-1];
		return;
	}
	int m = (s + e) / 2;
	build(s, m, i*2);
	build(m+1, e, i*2+1);
	tree[i] = tree[i*2] + tree[i*2+1];
}


int query(int l, int r, int s, int e, int i) {
	if(l>e || r<s) {
		return 0;
	}
	if(l <= s && e <= r) {
		return tree[i];
	}
	int m = (s + e)/2;
	return query(l, r, s, m, i*2) + query(l, r, m+1, e, i*2+1);
}
/*
  (1, 20)
 /  \ 
 (1, 10)   (11, 20)
/ \ / \
4 5 6  7
.
.
.
(1,1, i)
*/
void update(int s, int e, int i, int idx, int val) {
	if(s == e) {
		arr[idx-1] = val;
		tree[i] = val;
		return;
	}
	int m = (s + e) / 2;
	if(idx <= m) update(s, m, i*2, idx, val);
	else update(m+1, e, i*2+1, idx, val);
	tree[i] = tree[i*2] + tree[i*2+1];
}

// int query();

int main() {
	// build(1, 10, 1);
	// cout << query(1, 9, 1, 10, 1) << endl;

	// update(1, 10, 1, 5, 10);
	// cout << query(1, 10, 1, 10, 1) << endl;

	// for(int i=0;i<10;i++) {
	// 	cout << arr[i] << " ";
	// }

	// SegmentTree<int> t(vector<int>{1,3,5,6, -1, 3}, 1e9+7);
	// cout << t.query(1, 1) << "\n";
	// cout << t.query(2, 2) << "\n";
	// cout << t.query(3, 3) << "\n";
	// cout << t.query(4, 4) << "\n";
	// cout << t.query(5, 5) << "\n";
	// cout << t.query(6, 6) << "\n";
}

// 1  2   3   4
// 4  2   7   3

// 		2
// 	3		7
// 4      9   8