#include <bits/stdc++.h>
using namespace std;

template<typename T, int LG>
struct Basis {
    T basis[LG];
    int basis_sz;

    void clear() {
        memset(basis, 0, sizeof(basis));
        basis_sz = 0;
    }

    Basis() {
        clear();
    }

    void insert(T x) {
        for (int i = LG - 1; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (basis[i] == 0) {
                    basis[i] = x;
                    basis_sz += 1;
                    break;
                } else {
                    x ^= basis[i];
                }
            }
        }
    }

    int size() {
        return basis_sz;
    }

    bool has_xor(T x) {
        for (int i = LG - 1; i >= 0; --i) {
            if ((x >> i) & 1) x ^= basis[i];
        }
        return (x == 0);
    }

    // max (subset ^ x); x = 0 for max subset xor
    T max_xor(T x = 0) {
        for (int i = LG - 1; i >= 0; --i) {
            if ((x >> i) & 1) continue;
            x ^= basis[i];
        }
        return x;
    }

    // kth minimum subset xor including empty subset; k 1-indexed
    T kth_subset_xor(unsigned long long k) {
        assert(k && (basis_sz >= 64 || k <= (1ULL << basis_sz)));
        --k;
        int remaining = basis_sz;

        T x = 0;
        for (int i = LG - 1; i >= 0; --i) {
            if (basis[i] == 0) continue;
            unsigned long long half = 1ULL << --remaining;
            if (k < half) {
                // [0...cnt/2-1]
                if ((x >> i) & 1) x ^= basis[i];
            } else {
                // [cnt/2...cnt-1]
                if (((x >> i) & 1) == 0) x ^= basis[i];
                k -= half;
            }

        }
        return x;
    }
    // Number of distinct subset XORs strictly below x. Up to 64 value bits.
    unsigned long long count_lt(T x) const {
        T prefix = 0;
        unsigned long long count = 0;
        int remaining = basis_sz;
        for (int i=LG-1;i>=0;--i) {
            bool want = (x >> i) & 1, have = (prefix >> i) & 1;
            if (basis[i]) {
                --remaining;
                if (want) count += 1ULL << remaining;
                if (want != have) prefix ^= basis[i];
            } else if (want != have) {
                if (want) count += 1ULL << remaining;
                break;
            }
        }
        return count;
    }
    void reduce() {
        for (int i=0;i<LG;++i) if (basis[i])
            for (int j=i+1;j<LG;++j) if ((basis[j] >> i) & 1) basis[j] ^= basis[i];
    }
};
// Record which input indices form a requested XOR (or the maximum XOR).
template<class T, int Bits, size_t Capacity>
struct WitnessBasis {
    array<T,Bits> rows{};
    array<bitset<Capacity>,Bits> ids{};
    void insert(T x, size_t id) {
        bitset<Capacity> used;
        used.set(id);
        for (int i=Bits-1;i>=0;--i) if ((x>>i)&1) {
            if (!rows[i]) { rows[i]=x; ids[i]=used; return; }
            x ^= rows[i]; used ^= ids[i];
        }
    }
    optional<bitset<Capacity>> represent(T x) const {
        bitset<Capacity> used;
        for (int i=Bits-1;i>=0;--i) if ((x>>i)&1) {
            if (!rows[i]) return nullopt;
            x ^= rows[i]; used ^= ids[i];
        }
        return used;
    }
    pair<T,bitset<Capacity>> maximize(T x=0) const {
        bitset<Capacity> used;
        for (int i=Bits-1;i>=0;--i) if ((x^rows[i]) > x) {
            x ^= rows[i]; used ^= ids[i];
        }
        return {x,used};
    }
};

template<typename T>
struct WeightedBasis {
  static constexpr int B = numeric_limits<T>::digits;
  T a[B];
  long long wt[B];
  WeightedBasis() {
    memset(a, 0, sizeof a);
    memset(wt, 0, sizeof wt);
  }
  void insert(T x, long long w) {
    for (int i = B - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (a[i] == 0) {
          a[i] = x;
          wt[i] = w;
          break;
        }
        if (wt[i] < w) {
          swap(wt[i], w);
          swap(a[i], x);
        }
        x ^= a[i];
      }
    }
  }
  // maximum sum of linearly independent vectors
  long long query() {
    long long ans = 0;
    for (int i = 0; i < B; i++) {
      ans += wt[i];
    }
    return ans;
  }
};
