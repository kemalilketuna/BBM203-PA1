#include <iostream>
#include "Convolution.h"

// Default constructor 
Convolution::Convolution() : kernel(nullptr), kernelHeight(0), kernelWidth(0), stride(1), padding(false) {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad)
    : kernelHeight(kh), kernelWidth(kw), stride(stride_val), padding(pad) {
        kernel = new double*[kh];
        for (int i = 0; i < kh; ++i) {
            kernel[i] = new double[kw];
            for (int j = 0; j < kw; j++) {
                kernel[i][j] = customKernel[i][j];
            }
        }
}

// Destructor
Convolution::~Convolution() {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    this->kernelHeight = other.kernelHeight;
    this->kernelWidth = other.kernelWidth;
    this->stride = other.stride;
    this->padding = other.padding;
    kernel = new double*[other.kernelHeight];
    for (int i = 0; i < other.kernelHeight; ++i) {
        kernel[i] = new double[other.kernelWidth];
        for (int j = 0; j < other.kernelWidth; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this;
    }
    // Free the existing memory
    for (int i = 0; i < kernelHeight; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;
    this->kernelHeight = other.kernelHeight;
    this->kernelWidth = other.kernelWidth;
    this->stride = other.stride;
    this->padding = other.padding;
    kernel = new double*[other.kernelHeight];
    for (int i = 0; i < other.kernelHeight; ++i) {
        kernel[i] = new double[other.kernelWidth];
        for (int j = 0; j < other.kernelWidth; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int paddingValue = padding ? 1 : 0;
    int newImage_height = (input_image.get_height() + 2 * paddingValue);
    int newImage_width = (input_image.get_width() + 2 * paddingValue);
    ImageMatrix newImage = ImageMatrix(newImage_height, newImage_width);
    if (padding) {
        // Surround top bottom left right with zeros
        for (int i = 0; i < newImage.get_height(); ++i) {
            for (int j = 0; j < newImage.get_width(); ++j) {
                if (i == 0 || j == 0 || i == newImage.get_height() - 1 || j == newImage.get_width() - 1) {
                    newImage.get_data()[i][j] = 0;
                } else {
                    newImage.get_data()[i][j] = input_image.get_data()[i - 1][j - 1];
                }
            }
        }
    } else {
        for (int i = 0; i < newImage.get_height(); ++i) {
            for (int j = 0; j < newImage.get_width(); ++j) {
                newImage.get_data()[i][j] = input_image.get_data()[i][j];
            }
        }
    }

    int convolvedImage_height = (input_image.get_height() - kernelHeight + 2 * paddingValue) / stride + 1;
    int convolvedImage_width = (input_image.get_width() - kernelWidth + 2 * paddingValue) / stride + 1;
    ImageMatrix convolvedImage(convolvedImage_height, convolvedImage_width);
    for (int i = 0; i <= newImage_height - kernelHeight; i += stride) {
        for (int j = 0; j <= newImage_width - kernelWidth; j += stride) {
            double sum = 0;
            for (int k = 0; k < kernelHeight; ++k) {
                for (int l = 0; l < kernelWidth; ++l) {
                    sum += kernel[k][l] * newImage.get_data()[i + k][j + l];
                }
            }
            convolvedImage.get_data()[i/stride][j/stride] = sum;
        }
    }
    return convolvedImage;
}
