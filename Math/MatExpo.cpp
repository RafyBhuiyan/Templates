#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9+7;

struct Matrix{
    vector<vector<long long>> val;
    int row, col;

    Matrix(int _r, int _c){
        row = _r;
        col = _c;
        val.assign(row, vector<long long>(col));
    }

    explicit Matrix(const vector<vector<long long>>& values) :
        val(values), row(values.size()), col(row ? values.front().size() : 0) {
        for (const auto &line : val) assert((int)line.size() == col);
    }
    Matrix operator+(const Matrix &b) const {
        assert(row == b.row && col == b.col);
        Matrix r(row,col);
        for (int i=0;i<row;i++) for (int j=0;j<col;j++)
            r.val[i][j] = (val[i][j] + b.val[i][j]) % mod;
        return r;
    }
    Matrix operator-(const Matrix &b) const {
        assert(row == b.row && col == b.col);
        Matrix r(row,col);
        for (int i=0;i<row;i++) for (int j=0;j<col;j++)
            r.val[i][j] = (val[i][j] - b.val[i][j] + mod) % mod;
        return r;
    }
    bool operator==(const Matrix &b) const { return row==b.row && col==b.col && val==b.val; }
    bool operator!=(const Matrix &b) const { return !(*this==b); }
    Matrix& operator+=(const Matrix &b) { return *this = *this + b; }
    Matrix& operator-=(const Matrix &b) { return *this = *this - b; }
    Matrix& operator*=(const Matrix &b) { return *this = *this * b; }
    Matrix operator*(const Matrix &other) const {
        assert(col == other.row);
        Matrix result(row, other.col);
        for(int i = 0; i<row; i++){
            for(int j = 0; j<other.col; j++){
                for(int k = 0; k<col; k++){
                    result.val[i][j] += val[i][k] * other.val[k][j];
                    result.val[i][j] %= mod;
                }
            }
        }

        return result;
    }

    void print(){
        for(int i = 0; i<row; i++){
            for(int j = 0; j<col; j++){
                cout<<val[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

Matrix Matexpo(Matrix X, long long n){
    assert(n >= 0 && X.row == X.col);
    Matrix Y(X.row, X.col);
    if(n == 0){
        for(int i = 0; i<X.row; i++)
            Y.val[i][i] = 1;

        return Y;
    }
    Y = Matexpo(X, n/2);
    Y = Y * Y;

    if(n % 2 == 1){
        Y = Y * X;
    }

    return Y;
}

int main(){

    long long n;
    cin>>n;

    Matrix F(2, 1);

    F.val[0][0] = 0;
    F.val[1][0] = 1;


    Matrix M(2, 2);
    M.val[0][0] = 0, M.val[0][1] = 1;
    M.val[1][0] = 1, M.val[1][1] = 1;

    M = Matexpo(M, n);

    F = M * F;

    cout<<F.val[0][0]<<endl;

    return 0;
}
