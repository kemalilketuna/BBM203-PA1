#include "EncodeMessage.h"
#include <cmath>
#include <vector>


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


std::string EncodeMessage::decimal_to_binary(int decimal, bool is_seven_bit) {
    std::string binary = "";
    int bit_size = (is_seven_bit) ? 7 : 8;
    for (int i = 0; i < bit_size; ++i) {
        binary = std::to_string(decimal % 2) + binary;
        decimal = decimal / 2;
    }
    return binary;
}

std::string EncodeMessage::string_to_binary(const std::string &message) {
    std::string binary_message = "";
    for (char c : message){
        binary_message += decimal_to_binary(c, true);
    }
    return binary_message;
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
    for (std::pair<int,int> position : positions) {
        // If the binary message is empty, break out of the loop
        if (binary_message.empty()) {
            break;
        }

        if (position.first < 0 || position.first >= img.get_width() ||
            position.second < 0 || position.second >= img.get_height()) {
            continue;  // Skip invalid positions
        }

        double pixel = img.get_data(position.first, position.second);
        std::string binary_value_of_current_pixel = decimal_to_binary(pixel, false);

        // Replace the least significant bit of the pixel's binary value with the first bit of the binary message
        binary_value_of_current_pixel[binary_value_of_current_pixel.size() - 1] = binary_message[0];

        // Remove the used bit from the binary message
        binary_message.erase(0, 1);

        // Convert the modified binary pixel value back to decimal and update the image matrix
        encoded_image.set_data(position.first, position.second, binary_to_decimal(binary_value_of_current_pixel));
    }

    return encoded_image;
}

