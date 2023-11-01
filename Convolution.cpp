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
Convolution::Convolution(const Convolution &other)
    : kernelHeight(other.kernelHeight), kernelWidth(other.kernelWidth), stride(other.stride), padding(other.padding) {
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this != &other) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;

        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        stride = other.stride;
        padding = other.padding;

        kernel = new double*[kernelHeight];
        for (int i = 0; i < kernelHeight; ++i) {
            kernel[i] = new double[kernelWidth];
            for (int j = 0; j < kernelWidth; ++j) {
                kernel[i][j] = other.kernel[i][j];
            }
        }
    }
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    ImageMatrix newImage;
    if (padding){
        newImage = ImageMatrix(input_image.get_height() + 2, input_image.get_width() + 2);
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
        newImage = ImageMatrix(input_image.get_height(), input_image.get_width());
        newImage = input_image;
    }


    int convolvedImage_height = (input_image.get_height() - kernelHeight + 2 * padding) / stride + 1;
    int convolvedImage_width = (input_image.get_width() - kernelWidth + 2 * padding) / stride + 1;
    ImageMatrix convolvedImage(convolvedImage_height, convolvedImage_width);
    for (int i = 0; i <= newImage.get_height() - kernelHeight; i += stride) {
        for (int j = 0; j <= newImage.get_width() - kernelWidth; j += stride) {
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
