#include "rsa.hpp"

int main(int argc, char* argv[]) {
    // if(argc < 3) {
    //     std::cout << "Provide filename and instruction(d/e)" << std::endl;
    //     return 1;
    // }

    std::ifstream file(argv[1]);
    RSA rsa;
    if(argc == 2) {
        std::ofstream output("EN.txt");
        rsa.encrypt(file, output);
        std::cout << "Private Key: " << rsa.getPrivateKey() << std::endl;
    }
    else if(*argv[2] == 'd' || *argv[2] == 'D') {
        if(argc < 4) {
            std::cout << "Provide private key" << std::endl;
            return 1;
        }
        std::ofstream output("DE.txt");
        int key = std::stoi(argv[3]);
        rsa.decrypt(file, output, key);
    }
    return 0;
}