#include <bits/stdc++.h>

template <class Info, class Merge = std::plus<Info>>
struct SegmentTree {
	const int n;
	const Merge merge;
	std::vector<Info> val;
	SegmentTree() = default;
	SegmentTree(const std::vector<Info>& init): n(init.size()), merge(Merge()), val(4 << std::__lg(n)) {
		const auto build = [&](const auto& build, int i, int l, int r) -> void {
			if (l + 1 == r) {
				val[i] = init[l];
				return;
			}
			int m = (l + r) / 2;
			build(build, i * 2, l, m);
			build(build, i*2+1, m, r);
			val[i] = merge(val[i * 2], val[i*2+1]);
		};
		build(build, 1, 0, n);
	}
	Info query(int i, int l, int r, int ql, int qr) {
		if (ql <= l and r <= qr) return val[i];
		int m = (l + r) / 2;
		if (qr <= m) return query(i * 2, l, m, ql, qr);
		if (m <= ql) return query(i*2+1, m, r, ql, qr);
		return merge(query(i * 2, l, m, ql, qr), query(i*2+1, m, r, ql, qr));
	}
	Info query(int ql, int qr) {
		return query(1, 0, n, ql, qr);
	}
};

namespace BinaryJumping {

std::vector<int> dep;
std::vector<std::vector<int>> jmp;

void dfs(const std::vector<std::vector<int>>& adj, const int& u, const int& p) {
  jmp[0][u] = p;
  for (const int& v : adj[u]) {
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    dfs(adj, v, u);
  }
}

void init(const std::vector<std::vector<int>>& adj) {
	int N = adj.size();
  dep.assign(N, 0);
  jmp.emplace_back(N, 0);
  dfs(adj, 1, 1);
  for (int l = 1; (1 << l) < N; ++l) {
    jmp.emplace_back(N + 1, 0);
    for (int i = 1; i < N; ++i) {
      jmp[l][i] = jmp[l - 1][jmp[l - 1][i]];
    }
  }
}

int get_lca(int u, int v) {
  if (dep[u] < dep[v]) std::swap(u, v);
  for (int l = jmp.size() - 1, d = dep[u] - dep[v]; l >= 0; --l)
    if (d >> l & 1) u = jmp[l][u];
  if (u == v) return u;

  for (int l = jmp.size() - 1; l >= 0; --l) {
    if (jmp[l][u] != jmp[l][v]) {
      u = jmp[l][u];
      v = jmp[l][v];
    }
  }
  return jmp[0][u];
}

int get_dis(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
}

int go(int u, int v, int step) {
  int lca = get_lca(u, v);
  int dis = dep[u] + dep[v] - 2 * dep[lca];
  if (step > dep[u] - dep[lca]) {
    std::swap(u, v);
    step = dis - step;
  }
  for (int l = jmp.size() - 1; l >= 0; --l)
    if (step >> l & 1) u = jmp[l][u];
  return u;
}

} // namespace BinaryJumping

namespace Virus {

struct Virus {
	int v, t;
	Virus(const int& _v = 0, const int& _t = 0):
		v(_v), t(_t) {}
};

Virus operator + (Virus a, Virus b) {
	if (a.t > b.t) std::swap(a, b);
	int dis = BinaryJumping::get_dis(a.v, b.v);
	int dt = b.t - a.t;
	if (dt >= dis) return b;

	a.v = BinaryJumping::go(a.v, b.v, dt);
	a.t += dt;
	dis -= dt;

	if ((a.v & 1) and !(b.v & 1)) {
		a.v = BinaryJumping::go(a.v, b.v, 1);
		a.t += 1;
		dis -= 1;
	}
	if ((b.v & 1) and !(a.v & 1)) {
		b.v = BinaryJumping::go(b.v, a.v, 1);
		b.t += 1;
		dis -= 1;
	}

	Virus res(BinaryJumping::go(a.v, b.v, dis / 2), a.t + dis / 2);
	return res;
}

} // namespace Virus

namespace CentroidDecomp {

std::vector<bool> mark;
std::vector<int> size;
std::vector<int> par_cen;
std::vector<std::vector<int>> count, count_par;
std::vector<std::vector<int>> distance;

void get_size(int u, int p, const std::vector<std::vector<int>>& adj, int dep, std::vector<int>& tmp) {
	if (tmp.size() <= dep) tmp.emplace_back(0);
	tmp[dep] += 1 - (u & 1);
	size[u] = 1;
	for (const int& v: adj[u]) {
		if (v == p or mark[v]) continue;
		get_size(v, u, adj, dep + 1, tmp);
		size[u] += size[v];
	}
}

int get_centroid(int u, int p, int s, const std::vector<std::vector<int>>& adj) {
	for (const int& v: adj[u])
		if (v != p and !mark[v] and size[v] * 2 > s)
			return get_centroid(v, u, s, adj);
	return u;
}

void get_distance(int u, int dep_cen, int p, int dep, int cen, const std::vector<std::vector<int>>& adj) {
	assert(distance[u].size() == dep_cen);
	distance[u].emplace_back(dep);

	if (count[cen].size() <= dep) count[cen].emplace_back(0);
	count[cen][dep] += 1 - (u & 1);

	for (const int& v: adj[u])
		if (v != p and !mark[v])
			get_distance(v, dep_cen, u, dep + 1, cen, adj);
}

void centroid_decomp(int u, int dep_cen, int p, const std::vector<std::vector<int>>& adj) {
	std::vector<int> tmp(1, 0);
	get_size(u, p, adj, 1, tmp);
	int cen = get_centroid(u, p, size[u], adj);
	get_distance(cen, dep_cen, cen, 0, cen, adj);

	par_cen[cen] = p;
	mark[cen] = true;
	std::swap(tmp, count_par[cen]);
	for (const int& v: adj[cen])
		if (!mark[v]) centroid_decomp(v, dep_cen + 1, cen, adj);
}

void init(const std::vector<std::vector<int>>& adj) {
	int N = adj.size();
	mark.assign(N, false);
	size.assign(N, 0);
	par_cen.assign(N, 0);
	count.assign(N, std::vector<int>());
	count_par.assign(N, std::vector<int>());
	distance.assign(N, std::vector<int>());
	centroid_decomp(1, 0, 1, adj);

	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < count[i].size(); ++j)
			count[i][j] += count[i][j - 1];
		for (int j = 1; j < count_par[i].size(); ++j)
			count_par[i][j] += count_par[i][j - 1];
	}
}

int query(int u, int dis) {
	int ans = 0;
	for (int p = u, dep = distance[u].size() - 1; dep >= 0; --dep, p = par_cen[p]) {
		int d = std::min((int) count[p].size() - 1, dis - distance[u][dep]);
		if (d >= 0) ans += count[p][d];
		if (dep > 0) {
			d = std::min((int) count_par[p].size() - 1, dis - distance[u][dep - 1]);
			if (d >= 0) ans -= count_par[p][d];
		}
	}
	return ans;
}

} // namespace CentroidDecomp

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, Q;
  std::cin >> N >> Q;

  std::vector adj(2 * N + 1, std::vector<int>());
  for (int u, v, i = 1; i < N; ++i) {
    std::cin >> u >> v;
    adj[u * 2].push_back(i * 2 - 1);
    adj[v * 2].push_back(i * 2 - 1);
    adj[i * 2 - 1].push_back(u * 2);
    adj[i * 2 - 1].push_back(v * 2);
  }

  BinaryJumping::init(adj);

	std::vector<Virus::Virus> viruses;
	std::vector<std::tuple<int, int, int>> queries;
	for (int type, v, t, l, r, i = 0; i < Q; ++i) {
		std::cin >> type;
		if (type == 1) {
			std::cin >> v >> t;
			viruses.emplace_back(v * 2, 2 * t);
		} else {
			std::cin >> l >> r >> t;
			queries.emplace_back(l, r, 2 * t);
		}
	}

	SegmentTree<Virus::Virus> virus_sgt(viruses);
	CentroidDecomp::init(adj);

	for (const auto& [ql, qr, qt]: queries) {
		Virus::Virus virus = virus_sgt.query(ql - 1, qr);
		std::cout << CentroidDecomp::query(virus.v, qt - virus.t) << '\n';
	}

  return 0;
}

