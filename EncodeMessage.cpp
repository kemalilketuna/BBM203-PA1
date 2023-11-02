#include "EncodeMessage.h"
#include <cmath>
#include <bitset>

// Helper function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
        i += 6;
    }
    return true;
}

// Helper function to get the nth Fibonacci number

int fibonacci(int n) {
    // Create a static vector to store computed Fibonacci values
    static std::vector<int> fibCache(n + 1, -1);

    // Base cases
    if (n <= 1) return n;

    // Check if the value is already computed
    if (fibCache[n] != -1) return fibCache[n];

    // Compute and store the value in the cache
    fibCache[n] = fibonacci(n - 1) + fibonacci(n - 2);

    return fibCache[n];
}


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    std::string transformedMessage = "";

    // 1. Character Transformation
    for (int i = 0; i < message.size(); i++) {
        char c = message[i];
        if (isPrime(i)) {
            int asciiValue = static_cast<int>(c) + fibonacci(i);
            if (asciiValue <= 32) asciiValue += 33;
            if (asciiValue >= 127) asciiValue = 126;
            transformedMessage += static_cast<char>(asciiValue);
        } else {
            transformedMessage += c;
        }
    }

    // 2. Right Circular Shifting
    int shiftAmount = transformedMessage.size() / 2;
    std::string shiftedMessage = transformedMessage.substr(transformedMessage.size() - shiftAmount) + transformedMessage.substr(0, transformedMessage.size() - shiftAmount);

    // 3. Message Embedding
    ImageMatrix newImg = img;
    for (int i = 0; i < shiftedMessage.size() && i < positions.size(); i++) {
        std::bitset<7> charBits(shiftedMessage[i]);
        newImg.get_data()[positions[i].first][positions[i].second] = charBits[0];
    }

    return newImg;
}
