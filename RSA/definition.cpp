#include "rsa.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

bool RSA::isPrime(int n){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int RSA::randomPrime(){
    const int min = 11;    
    const int max = 97;    
    int num = min + (rand() % (max - min + 1));
    
    while (!isPrime(num)) {
        num++;
        if (num > max) {
            num = min;
        }
    }
    return num;
}

RSA::RSA() {
    srand(time(nullptr));  
    p = randomPrime();
    q = randomPrime();
    
    mult = p * q;
    decryptionExp = (p-1) * (q-1);
    encryptionExp = gPublic(decryptionExp);
    d = modInverse(encryptionExp, decryptionExp);
}

int RSA::gPublic(int n) {
    int random = rand()%n;
    int gcd = std::gcd(random,n);
    while(gcd != 1 || random < 1){
        random +=1;
        gcd = std::gcd(random,n);
    }
    return random;
}

int RSA::modInverse(int encrypt, int decrypt) {
    int m0 = decrypt;
    int y = 0, x = 1;

    while (encrypt > 1) {
        int q = encrypt / decrypt;
        int t = decrypt;

        decrypt = encrypt % decrypt;
        encrypt = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;
    return x;
}

int RSA::modPow(int base, int exp, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp & 1)
            result = (1LL * result * base) % modulus;
        base = (1LL * base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

void RSA::encrypt(std::ifstream& input, std::ofstream& output) {
    char text;
    output << mult << " ";
    while(input.get(text)){
        int charToAscii = modPow(static_cast<int>(text), encryptionExp, mult);
        output << charToAscii;
        if(text == ' '){output << " @ ";}
        else if(text == '\n'){output << " # ";}
        else{output << ' ';}
    }
}

int RSA::getProduct(std::ifstream& input) {
    std::string text;
    if(input >> text) {
        try {
            return std::stoi(text);
        } catch(const std::invalid_argument& e) {
            std::cout << "Invalid file" << std::endl;
            return -1;
        }
    }
    std::cout << "Empty file" << std::endl;
    return -1;
}

int RSA::decrypt(std::ifstream& input, std::ofstream& output, int privateKey) {
    std::string text;
    int n = getProduct(input);
    if(n == -1){std::cout<<"Invalid file,decryption failed" << std::endl; return -1;}

    while(input >> text){
        if(text == "@"){
            continue;
            //output << " ";
        }
        else if(text == "#"){
            continue;
            // output << '\n';
        }
        else{
            int intValue = std::stoi(text);
            int decrypted = modPow(intValue, privateKey, n);
            output << static_cast<char>(decrypted);
        }
    }
    std::cout << "Decryption Done" << std::endl;
    return 0;
}
