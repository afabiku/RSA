#ifndef RSA_HPP
#define RSA_HPP

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

class RSA {
public:
    RSA();
    int gPublic(int n);
    int modInverse(int e, int phi_n);
    int modPow(int base, int exp, int modulus);
    void encrypt(std::ifstream& input, std::ofstream& output);
    int decrypt(std::ifstream& input, std::ofstream& output, int privateKey);
    int getPrivateKey() const { return d; }
    int getProduct(std::ifstream&);
    int randomPrime();
    bool isPrime(int n);
    void print(){    std::cout << p << " " << q << " " << mult << " " << decryptionExp << " " << encryptionExp << " " << d << std::endl;    }
private:
    int p, q;
    int mult;
    int decryptionExp;
    int encryptionExp;
    int d;

}; 
#endif