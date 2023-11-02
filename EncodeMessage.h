#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();

    ImageMatrix encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions);


private:
    // Any private helper functions or variables if necessary
    std::string string_to_binary(const std::string &message);
    bool isPrime(int n);
    int fibonacci(int n);
    std::string transformMessage(const std::string &message);
    std::string decimal_to_binary(int decimal, bool pad);
    std::string right_circle_shift(const std::string &message, int shift);
    double binary_to_decimal(const std::string &binary);    
};

#endif // ENCODE_MESSAGE_H