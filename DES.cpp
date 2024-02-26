#include <iostream>
#include <string>
#include <vector>

/* Define Arrays */
int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int E[48] = { /* E bit-selection table */
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int P[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

int IP_1[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

int S[8][4][16] = { 
    { /* S1 */
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    }, 
    { /* S2 */
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}, 
    },
    { /* S3 */
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    { /* S4 */
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    { /* S5 */
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    { /* S6 */
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    { /* S7 */
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    { /* S8 */
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

std::string binaryToString(const std::string& binary) {
    std::string text = "";
    for(size_t i = 0; i < binary.size(); i += 8) {
        int byte = std::stoi(binary.substr(i, 8), nullptr, 2);
        text += static_cast<char>(byte);
    }
    return text;
}

std::string permute(const std::string& input, const int* table, int n) {
    std::string output = "";
    for(int i = 0; i < n; i++) {
        output += input[table[i] - 1];
    }
    return output;
}

std::string xorFunction(const std::string& a, const std::string& b) {
    std::string result = "";
    for (size_t i = 0; i < a.size(); i++) {
        result += (a[i] == b[i] ? '0' : '1');
    }
    return result;
}

std::string fFunction(const std::string& right, const std::string& roundKey) {
    // Expansion of right part to 48 bits using E table
    std::string expandedRight = permute(right, E, 48);
    
    std::string xored = xorFunction(expandedRight, roundKey);
    
    // S-Box substitution
    std::string sBoxResult = "";
    for (int i = 0; i < 8; i++) {
        int row = 2 * (xored[i*6] - '0') + (xored[i*6 + 5] - '0');
        int col = 8 * (xored[i*6 + 1] - '0') + 4 * (xored[i*6 + 2] - '0') + 2 * (xored[i*6 + 3] - '0') + (xored[i*6 + 4] - '0');
        int val = S[i][row][col];
        sBoxResult += std::bitset<4>(val).to_string();
    }
    
    // Permutation using P table
    std::string result = permute(sBoxResult, P, 32);
    return result;
}

std::string leftShift(const std::string& k, int shifts) {
    std::string shifted = k.substr(shifts) + k.substr(0, shifts);
    return shifted;
}

// Function to generate and print all round keys
std::vector<std::string> generateRoundKeys(const std::string& key) {
    std::vector<std::string> roundKeys;
    
    // Initial key permutation using PC-1
    std::string keyPermuted = permute(key, PC1, 56);
    
    std::string left = keyPermuted.substr(0, 28);
    std::string right = keyPermuted.substr(28, 28);
    
    // Array for shift schedule
    int shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    
    for(int i = 0; i < 16; i++) {
        left = leftShift(left, shifts[i]);
        right = leftShift(right, shifts[i]);
        
        // Combine and permute using PC-2 to get round key
        std::string combined = left + right;
        std::string roundKey = permute(combined, PC2, 48);
        roundKeys.push_back(roundKey);
        
        std::cout << "Round " << (i+1) << " Key: " << roundKey << std::endl;
    }
    
    return roundKeys;
}

std::string DESDecrypt(const std::string& ciphertext, const std::vector<std::string>& roundKeys) {
    std::string permutedText = permute(ciphertext, IP, 64);
    
    std::string left = permutedText.substr(0, 32);
    std::string right = permutedText.substr(32, 32);
    
    // 16 rounds of decryption, using the round keys in reverse order
    for (int i = 15; i >= 0; i--) {
        std::string rightExpanded = fFunction(right, roundKeys[i]);
        std::string newRight = xorFunction(left, rightExpanded);
        left = right;
        right = newRight;

        std::cout << "Round " << 16 - i << " L: " << left << " R: " << right << std::endl;
    }
    
    std::string combined = right + left;
    std::string decrypted = permute(combined, IP_1, 64);
    
    return binaryToString(decrypted);
}

int main() {
    std::string keyBin = "0100110001001111010101100100010101000011010100110100111001000100";
    std::string ciphertextBin = "1100101011101101101000100110010101011111101101110011100001110011";
    
    std::vector<std::string> roundKeys = generateRoundKeys(keyBin);
    
    std::string decryptedMessage = DESDecrypt(ciphertextBin, roundKeys);
    
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
    
    return 0;
}
