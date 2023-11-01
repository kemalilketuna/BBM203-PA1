#include "ImageSharpening.h"
#include "Convolution.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    // Initialize a 3x3 averaging kernel for blurring
    blurring_kernel = new double*[kernel_height];
    for (int i = 0; i < kernel_height; ++i) {
        blurring_kernel[i] = new double[kernel_width];
        for (int j = 0; j < kernel_width; ++j) {
            blurring_kernel[i][j] = 1.0 / 9.0;  // 1/9 for averaging
        }
    }
}

// Destructor
ImageSharpening::~ImageSharpening() {
    for (int i = 0; i < kernel_height; ++i) {
        delete[] blurring_kernel[i];
    }
    delete[] blurring_kernel;
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    // Step 1: Generate Noisy (Blurred) Image
    Convolution blur;
    // double** customKernel = blurring_kernel;
    blur = Convolution(blurring_kernel, kernel_height, kernel_width, 1, true);
    ImageMatrix Inoisy = blur.convolve(input_image);

    // Step 2: Sharp Image Calculation
    ImageMatrix Isharp = input_image + (input_image - Inoisy) * k;

    // Step 3: Clipping pixel intensity values to lie within [0, 255]
    for (int i = 0; i < Isharp.get_height(); ++i) {
        for (int j = 0; j < Isharp.get_width(); ++j) {
            double pixelValue = Isharp.get_data(i, j);
            if (pixelValue < 0) {
                Isharp.get_data()[i][j] = 0;
            } else if (pixelValue > 255) {
                Isharp.get_data()[i][j] = 255;
            }
        }
    }
    
    return Isharp;
}
