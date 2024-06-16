#include <algorithm>
#include <cmath>
#include <ctype.h>
#include <iostream>
#include <vector>

std::pair<int, int> getPQ(int);
int getPhi(int, int);
int gcd(int, int);
int getInverseMod(int, int);
int powMod(int, int, int);
char decode(int);

int main() {
    int e, n, m, p, q, phi_n, d, value;
    std::pair<int, int> pq;
    std::vector<int> inputValues;
    std::vector<int> outputValues;
    std::vector<char> message;
   
    std::cin >> e >> n >> m;
    if (!std::cin || e <= 1 || n <= 1 || m <= 0) { 
        throw std::runtime_error("invalid input");
    }

    pq = getPQ(n);
    p = pq.first;
    q = pq.second;
    phi_n = getPhi(p, q);
    d = getInverseMod(e, phi_n);

    for (int i = 0; i < m; ++i) {
        std::cin >> value;
        inputValues.push_back(value);
    }

    if (gcd(e, phi_n) != 1 || p == q) {
        std::cout << "Public key is not valid!";
        return 0;
    }

    for (int i = 0; i < inputValues.size(); ++i) {
        int decodedInt = powMod(inputValues.at(i), d, n);
        outputValues.push_back(decodedInt);
        char decodedChar = decode(decodedInt);
        if (decodedChar == '$') {
            throw std::runtime_error("error decoding");
        }
        message.push_back(decodedChar);
    }

    std::cout << p << " " << q << " " << phi_n << " " << d << std::endl;

    for (int i = 0; i < outputValues.size(); ++i) {
        std::cout << outputValues.at(i) << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < message.size(); ++i) {
        std::cout << message.at(i);
    }

    return 0;
}

std::pair<int, int> getPQ(int n) {
    std::pair<int, int> pq;
    std::vector<int> primeFactors;
    int N = n;

    for (int i = 2; i <= N; ++i) {
        while (N % i == 0) {
            primeFactors.push_back(i);
            N /= i;
        }
    }

    primeFactors.erase(std::unique(primeFactors.begin(), primeFactors.end()), primeFactors.end());

    for (int i = 0; i < primeFactors.size() - 1; ++i) {
        for (int j = i + 1; j < primeFactors.size(); ++j) {
            if (primeFactors.at(i) * primeFactors.at(j) == n) {
                pq.first = primeFactors.at(i);
                pq.second = primeFactors.at(j);
                return pq;
            }        
        }
    }

    return pq;
}

int getPhi(int p, int q) {
    return (p - 1) * (q - 1);
}

int getInverseMod(int e, int phi_n) {
	int d = 0;
	while (d < phi_n) {
		if (1 == (e * d % phi_n)) {
			return d;
		}
		++d;
	}
	return d;
}

int gcd(int n1, int n2) {
    while (n2 != 0) {
        int t = n2;
        n2 = n1 % n2;
        n1 = t;
    }
    return n1;
}

int powMod(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

char decode(const int x) {
    if (x >= 7 && x <= 32) {
        return static_cast<char>(x + 65 - 7);
    }
    switch (x) {
        case 33: return ' ';
        case 34: return '"';
        case 35: return ',';
        case 36: return '.';
        case 37: return '\'';
    }
    return '$';
}

// int encode(const char& c) {
//     switch (std::toupper(c)) {
//         case 'A': return 7;
//         case 'B': return 8;
//         case 'C': return 9;
//         case 'D': return 10;
//         case 'E': return 11;
//         case 'F': return 12;
//         case 'G': return 13;
//         case 'H': return 14;
//         case 'I': return 15;
//         case 'J': return 16;
//         case 'K': return 17;
//         case 'L': return 18;
//         case 'M': return 19;
//         case 'N': return 20;
//         case 'O': return 21;
//         case 'P': return 22;
//         case 'Q': return 23;
//         case 'R': return 24;
//         case 'S': return 25;
//         case 'T': return 26;
//         case 'U': return 27;
//         case 'V': return 28;
//         case 'W': return 29;
//         case 'X': return 30;
//         case 'Y': return 31;
//         case 'Z': return 32;
//         case ' ': return 33;
//         case '"': return 34;
//         case ',': return 35;
//         case '.': return 36;
//         case '\'': return 37;
//     }
//     return -1;
// }