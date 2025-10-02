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
    T kth_subset_xor(ll k) {
        --k;
        ll cnt = 1ll << basis_sz;
        assert((0 <= k) && (k < cnt));

        T x = 0;
        for (int i = LG - 1; i >= 0; --i) {
            if (basis[i] == 0) continue;
            if (k < (cnt >> 1)) {
                // [0...cnt/2-1]
                if ((x >> i) & 1) x ^= basis[i];
            } else {
                // [cnt/2...cnt-1]
                if (((x >> i) & 1) == 0) x ^= basis[i];
                k -= (cnt >> 1);
            }
            cnt >>= 1;
        }
        return x;
    }
};
