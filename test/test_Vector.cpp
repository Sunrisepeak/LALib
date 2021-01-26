#include <iostream>
#include <Vector.hpp>

using namespace std;

int main() {
    Matrix::Vector<int> v1(3, 1), v2(3, 2);
    auto v3 = v1 + v2;
    v3 = Matrix::Vector<int>(4, 2) + Matrix::Vector<int, vector<int>>(4, -3);
    for (Matrix::Vector<int, vector<int>>::sizeType i = 0; i < v3.size(); i++) {
        cout << v3[i] << " ";
    }
    cout << "\ntest pt: " << v3 << endl;
    cout << "test * : " << v1 * v2 << endl;
    v2[2] = 1;
    cout << v1 << endl << v2 << endl;
    cout << "test X : " << (v1.operatorX(v2)) << endl;
    return 0;
}