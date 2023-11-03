#include "EdgeDetector.h"
#include "Convolution.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    // Initialize Sobel kernels
    Gx = new double*[3];
    Gy = new double*[3];
    for (int i = 0; i < 3; ++i) {
        Gx[i] = new double[3];
        Gy[i] = new double[3];
    }

    Gx[0][0] = -1; Gx[0][1] = 0; Gx[0][2] = 1;
    Gx[1][0] = -2; Gx[1][1] = 0; Gx[1][2] = 2;
    Gx[2][0] = -1; Gx[2][1] = 0; Gx[2][2] = 1;

    Gy[0][0] = -1; Gy[0][1] = -2; Gy[0][2] = -1;
    Gy[1][0] = 0;  Gy[1][1] = 0;  Gy[1][2] = 0;
    Gy[2][0] = 1;  Gy[2][1] = 2;  Gy[2][2] = 1;
}

// Destructor
EdgeDetector::~EdgeDetector() {
    for (int i = 0; i < 3; ++i) {
        delete[] Gx[i];
        delete[] Gy[i];
    }
    delete[] Gx;
    delete[] Gy;
}

// Detect Edges using the Sobel operator
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    Convolution convX(Gx, 3, 3, 1, true);
    Convolution convY(Gy, 3, 3, 1, true);

    ImageMatrix gradientX = convX.convolve(input_image);
    ImageMatrix gradientY = convY.convolve(input_image);

    // Calculate the magnitude of the gradients
    ImageMatrix gradientMagnitude(input_image.get_height(), input_image.get_width());
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            double data = sqrt(pow(gradientX.get_data(i, j), 2) + pow(gradientY.get_data(i, j), 2));
            gradientMagnitude.set_data(i, j, data);
        }
    }

    // Calculate the avarage gradient magnitude for the threshold
    double threshold = 0.0;
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            threshold += gradientMagnitude.get_data(i, j);
        }
    }
    threshold /= (input_image.get_height() * input_image.get_width());

    std::vector<std::pair<int, int>> edgePoints;

    // Find the edge points
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            if (gradientMagnitude.get_data(i, j) > threshold) {
                edgePoints.push_back(std::make_pair(i, j));
            }
        }
    }

    return edgePoints;
}