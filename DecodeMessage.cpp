// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>
#include <vector>
#include <bitset>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryString;

    // Extract the LSB from each pixel along the detected edges
    for (const auto& pixel : edgePixels) {
        int x = pixel.first;
        int y = pixel.second;
        int pixelValue = image.get_data(x, y);
        binaryString += std::to_string(pixelValue & 1); // Extract LSB
    }

    if (binaryString.length() % 7 != 0) {
        // Pad the binary string with 0s to make it divisible by 7
        int padding = 7 - (binaryString.length() % 7);
        for (int i = 0; i < padding; i++) {
            binaryString = "0" + binaryString;            
        }
    }
    
    // Convert the binary string to ASCII
    std::string decodedMessage;
    for (size_t i = 0; i < binaryString.length(); i += 7) {
        std::string byte = binaryString.substr(i, 7);
        char asciiChar = static_cast<char>(std::stoi(byte, nullptr, 2));

        // Adjustments for printable characters
        if (asciiChar <= 32) {
            asciiChar += 33;
        } else if (asciiChar >= 127) {
            asciiChar = 126;
        }

        decodedMessage.push_back(asciiChar);
    }

    return decodedMessage;
}
