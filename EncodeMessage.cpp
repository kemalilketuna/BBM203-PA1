#include "EncodeMessage.h"
#include <cmath>
#include <bitset>
#include <algorithm>

// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Implementation of binary_to_decimal function
double EncodeMessage::binary_to_decimal(const std::string &binary) {
    double decimal = 0;
    int power = 0;

    // Convert binary string to decimal
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += std::pow(2, power);
        }
        power++;
    }

    return decimal;
}


std::string EncodeMessage::decimal_to_binary(int number) {
    if (number == 0) return "0";

    std::string binary = "";
    while (number > 0) {
        binary += (number % 2) ? '1' : '0'; // Append '1' or '0' depending on the remainder
        number /= 2; // Divide the number by 2
    }

    std::reverse(binary.begin(), binary.end()); // The binary string is in reverse order
    return binary;
}

std::string EncodeMessage::string_to_binary(const std::string& text) {
    std::string binaryString = "";
    for (char c : text) {
        // Convert each character to a binary string of length 7
        binaryString += std::bitset<7>(c).to_string();
    }
    return binaryString;
}

// Function to check if a number is prime
bool EncodeMessage::isPrime(int num) {
    if (num <= 1) {
        return false; // 0 and 1 are not prime numbers
    }
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            return false; // Found a divisor, not prime
        }
    }
    return true; // No divisors found, number is prime
}

// Function to get the nth Fibonacci number
int EncodeMessage::fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    int previous = 0, current = 1;

    for (int i = 2; i <= n; i++) {
        int next = previous + current;
        previous = current;
        current = next;
    }

    return current;
}


// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message,
                                                const std::vector<std::pair<int, int>>& positions){

    // Transform the message
    std::string transformedMessage = message;
    for (size_t i = 0; i < message.size(); ++i) {
        if (isPrime(i)) {
            int asciiValue = static_cast<int>(message[i]);
            asciiValue += fibonacci(i);
            // If the ascii value is less than 32, add 33 to it
            // If the ascii value is greater than 127, set it to 126
            if (asciiValue <= 32) asciiValue += 33;
            if (asciiValue >= 127) asciiValue = 126;
            transformedMessage[i] = static_cast<char>(asciiValue);
        }
    }

    // Shift the transformed message
    int shift = transformedMessage.size() / 2;
    size_t length = transformedMessage.size();
    std::string shifted_message = transformedMessage.substr(length - shift, shift) + transformedMessage.substr(0, length - shift);

    // Convert the shifted message to binary
    std::string binary_message = string_to_binary(shifted_message);

    // Create a copy of the original image to encode the message into
    ImageMatrix encoded_image = img;

    // Iterate over the provided positions
    for(size_t i=0; i < positions.size()&& i < binary_message.size(); i++){
        int x = positions[i].first;
        int y = positions[i].second;
        int pixelValue = img.get_data(x, y);
        std::string binaryValueOfPixel = decimal_to_binary(pixelValue);
        binaryValueOfPixel[binaryValueOfPixel.size() - 1] = binary_message[i];
        encoded_image.set_data(x, y, binary_to_decimal(binaryValueOfPixel));
    }
    
    return encoded_image;
}

