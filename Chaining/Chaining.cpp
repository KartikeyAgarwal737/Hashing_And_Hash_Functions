#include "Chaining.h"

void Chaining::createAccount(std::string id, int count) {
    struct Account a;
    a.id = id;
    a.balance = count;
    int num = hash(id);
    bankStorage2d[num].push_back(a);
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> top;
    for (int i=0; i<bankStorage2d.size(); i++) {
        for (int j=0; j<bankStorage2d[i].size(); j++) {
            if (bankStorage2d[i][j].balance != 0) {
                top.push_back(bankStorage2d[i][j].balance);
            }
        }
    }
    sorting(top);
    int n_account = databaseSize();
    if (k>=n_account) {
        int dummy = n_account - top.size();
        for (int i=0; i<dummy; i++) {
            top.push_back(0);
        }
        return top;
    }
    if (k > top.size()) {
        for (int i=0; i<k-top.size(); i++) {
            top.push_back(0);
        }
        return top;
    }
    int dummy = top.size()-k;
    for (int i=0; i<dummy; i++) {
        top.pop_back();
    }
    return top;
}

int Chaining::getBalance(std::string id) {
    int num = hash(id);
    for (int i=0; i<bankStorage2d[num].size(); i++) {
        if (id == bankStorage2d[num][i].id) {
            return bankStorage2d[num][i].balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int num = hash(id);
    for (int i=0; i<bankStorage2d[num].size(); i++) {
        if (id == bankStorage2d[num][i].id) {
            bankStorage2d[num][i].balance += count;
            return;
        }
    }
    createAccount(id, count);
    return;
}

bool Chaining::doesExist(std::string id) {
    int num = hash(id);
    for (int i=0; i<bankStorage2d[num].size(); i++) {
        if (id == bankStorage2d[num][i].id) {
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int num = hash(id);
    for (int i=0; i<bankStorage2d[num].size(); i++) {
        if (id == bankStorage2d[num][i].id) {
            bankStorage2d[num].erase(bankStorage2d[num].begin()+i);
            return true;
        }
    }
    return false;
}
int Chaining::databaseSize() {
    int sz = 0;
    for (int i=0; i<317; i++) {
        sz = sz + bankStorage2d[i].size();
    }
    return sz;
}

int Chaining::hash(std::string id) {
    int num = 0;
    for (int i=0; i<4; i++) {
        num = num + (id[i]-'A');
    }
    for (int i=4; i<11; i++) {
        num = num + i*(id[i]-'0');
    }
    for (int i=12; i<22; i++) {
        num = num + i*(id[i]-'0');
    }
    num = num % 317;
    return num;
}

void Chaining::sorting(std::vector<int> &v) {
    int n=v.size();
    bool b;
    for (int i=0; i<n-1; i++) {
        b = false;
        for (int j=0; j<n-i-1; j++) {
            if (v[j] < v[j+1]) {
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                b = true;
            }
        }
        if (b==false) {
            break;
        }
    }
}