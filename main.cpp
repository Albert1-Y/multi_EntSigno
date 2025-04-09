//
//  main.cpp
//  multi_EntSigno
//
//  Created by Albert Yerem Caceres Marca on 8/04/25.
//
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// decimal a binario (C2)
vector<int> decToBin(int num, int bits) {
    vector<int> bin(bits, 0);
    bool neg = num < 0;

    if (neg) num = -num - 1;

    for (int i = bits - 1; i >= 0 && num > 0; --i) {
        bin[i] = num % 2;
        num /= 2;
    }

    if (neg) {
        for (int& bit : bin) bit = !bit;
    }

    return bin;
}

// binario (C2) a decimal
int binToDec(const vector<int>& bin) {
    int dec = 0;
    bool neg = bin[0] == 1;

    if (neg) {
        vector<int> temp = bin;
        for (int& bit : temp) bit = !bit;
        int carry = 1;
        for (int i = temp.size() - 1; i >= 0 && carry; --i) {
            int sum = temp[i] + carry;
            temp[i] = sum % 2;
            carry = sum / 2;
        }
        for (int bit : temp) dec = dec * 2 + bit;
        dec = -dec;
    }
    else {
        for (int bit : bin) dec = dec * 2 + bit;
    }

    return dec;
}

vector<int> binAdd(const vector<int>& a, const vector<int>& b) {
    vector<int> res(a.size());
    int carry = 0;

    for (int i = a.size() - 1; i >= 0; --i) {
        int sum = a[i] + b[i] + carry;
        res[i] = sum % 2;
        carry = sum / 2;
    }

    return res;
}

vector<int> binSub(const vector<int>& a, const vector<int>& b) {
    vector<int> negB = b;
    for (int& bit : negB) bit = !bit;
    vector<int> one(b.size(), 0); one.back() = 1;
    negB = binAdd(negB, one);
    return binAdd(a, negB);
}

void arithShift(vector<int>& a, vector<int>& q, int& q_1) {
    q_1 = q.back();
    for (int i = q.size() - 1; i > 0; --i) q[i] = q[i - 1];
    q[0] = a.back();
    for (int i = a.size() - 1; i > 0; --i) a[i] = a[i - 1];
}

// Imprime
void printRow(const vector<int>& a, const vector<int>& q, int q_1,
    const vector<int>& m, const string& op, int cycle) {
    cout << "| ";
    for (int bit : a) cout << bit;
    cout << " | ";
    for (int bit : q) cout << bit;
    cout << " |  " << q_1 << "  | ";
    if (cycle == 0) {
        for (int bit : m) cout << bit;
        cout << " | ";
    }
    else {
        cout << "     | ";
    }
    cout << left << setw(14) << op << " | " << setw(6) << cycle << " |" << endl;
}

vector<int> boothMult(int x, int y, int bits) {
    vector<int> M = decToBin(x, bits);
    vector<int> Q = decToBin(y, bits);
    vector<int> A(bits, 0);
    int Q_1 = 0;
    int cycles = bits;

    cout << "\n| A     | Q     | Q-1 | M     | Operacion      | Ciclo  |" << endl;
    cout << "|-------|-------|-----|-------|----------------|--------|" << endl;
    printRow(A, Q, Q_1, M, "Inicial", 0);

    for (int i = 1; i <= cycles; ++i) {
        int Q0 = Q.back();
        string op = "";

        if (Q0 == 1 && Q_1 == 0) {
            A = binSub(A, M);
            op = "A = A-M";
        }
        else if (Q0 == 0 && Q_1 == 1) {
            A = binAdd(A, M);
            op = "A = A+M";
        }
        else {
            op = "No op";
        }

        if (op != "No op") printRow(A, Q, Q_1, M, op, i);

        arithShift(A, Q, Q_1);
        printRow(A, Q, Q_1, M, "Shift", i);
    }

    vector<int> res;
    res.insert(res.end(), A.begin(), A.end());
    res.insert(res.end(), Q.begin(), Q.end());

    return res;
}

int main() {
    int op, num, bits;
    bool running = true;

    while (running) {
        cout << "\n=== MENU PRINCIPAL ===" << endl;
        cout << "1. Convertir decimal a C2" << endl;
        cout << "2. Convertir C2 a decimal" << endl;
        cout << "3. Multiplicacion Booth" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
        case 1: {
            cout << "Numero decimal: ";
            cin >> num;
            cout << "Cantidad de bits: ";
            cin >> bits;
            vector<int> bin = decToBin(num, bits);
            cout << "Binario (C2): ";
            for (int bit : bin) cout << bit;
            cout << endl;
            break;
        }
        case 2: {
            string binStr;
            cout << "Numero binario (C2): ";
            cin >> binStr;
            vector<int> bin;
            for (char c : binStr) bin.push_back(c - '0');
            int dec = binToDec(bin);
            cout << "Decimal: " << dec << endl;
            break;
        }
        case 3: {
            int x, y, b;
            cout << "Multiplicando: ";
            cin >> x;
            cout << "Multiplicador: ";
            cin >> y;
            cout << "Bits: ";
            cin >> b;
            vector<int> res = boothMult(x, y, b);
            cout << "\nResultado binario: ";
            for (int bit : res) cout << bit;
            int decRes = binToDec(res);
            cout << "\nResultado decimal: " << decRes;
            cout << "\nVerificacion: " << x << " * " << y << " = " << x * y << endl;
            break;
        }
        case 4:
            running = false;
            break;
        default:
            cout << "Opcion invalida!" << endl;
        }
    }

    return 0;
}