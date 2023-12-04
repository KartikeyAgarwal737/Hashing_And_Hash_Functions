#include "LinearProbing.h"

void LinearProbing::createAccount(std::string id, int count) {
    int num = hash(id);
    int i = 0;
    while (i != 100000) {
        if (bankStorage1d[(num + i)%100000].id == "" || bankStorage1d[(num + i)%100000].id == "a") {
            bankStorage1d[(num + i)%100000].id = id;
            bankStorage1d[(num + i)%100000].balance = count;
            n_account++;
            return;
        }
        i++;
    }
}

std::vector<int> LinearProbing::getTopK(int k) {
    std::vector<int> top = {};
    for (int i=0; i<bankStorage1d.size(); i++) {
        if (bankStorage1d[i].balance != 0) {
            top.push_back(bankStorage1d[i].balance);
        }
    }
    sorting(top);
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

int LinearProbing::getBalance(std::string id) {
    int num = hash(id);
    int i = 0;
    while (i != 100000) {
        if (bankStorage1d[(num + i)%100000].id == id) {
            return bankStorage1d[(num + i)%100000].balance;
        }
        if (bankStorage1d[(num + i)%100000].id == "") {
            return -1;
        }
        i++;
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count) {
    int num = hash(id);
    int i = 0;
    while (i != 100000) {
        if (bankStorage1d[(num + i)%100000].id == id) {
            bankStorage1d[(num + i)%100000].balance += count;
            return;
        }
        if (bankStorage1d[(num + i)%100000].id == "") {
            createAccount(id, count);
            return;
        }
        i++;
    }
}

bool LinearProbing::doesExist(std::string id) {
    int num = hash(id);
    int i = 0;
    while (i != 100000) {
        if (bankStorage1d[(num + i)%100000].id == id) {
            return true;
        }
        if (bankStorage1d[(num + i)%100000].id == "") {
            return false;
        }
        i++;
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int num = hash(id);
    int i = 0;
    while (i != 100000) {
        if (bankStorage1d[(num + i)%100000].id == id) {
            bankStorage1d[(num + i)%100000].id = "a";
            bankStorage1d[(num + i)%100000].balance = 0;
            n_account--;
            return true;
        }
        if (bankStorage1d[(num + i)%100000].id == "") {
            return false;
        }
        i++;
    }
    return false;
}

int LinearProbing::databaseSize() {
    return n_account;
}

int LinearProbing::hash(std::string id) {
    int num = 0;
    for (int i=0; i<4; i++) {
        num = num + 8*(id[i]-'A');
    }
    for (int i=4; i<11; i++) {
        num = num + (i+641) * (id[i]-'0');
    }
    for (int i=12; i<22; i++) {
        num = num + (i+640) * (id[i]-'0');
    }
    num = num % 100000;
    return num;
}

void LinearProbing::sorting(std::vector<int> &v) {
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