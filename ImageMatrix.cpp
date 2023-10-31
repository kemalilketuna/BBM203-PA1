#include "ImageMatrix.h"
#include "ImageLoader.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(): data(nullptr), height(0), width(0) {}

// Parameterized constructor for loading image from file
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Use ImageLoader to load the image data
    ImageLoader loader(filepath);

    // Get dimensions of the loaded image
    height = loader.getHeight();
    width = loader.getWidth();

    // Allocate memory for the data matrix and copy the loaded data
    data = new double*[height];
    for(int i = 0; i < height; i++) {
        data[i] = new double[width];
        for(int j = 0; j < width; j++) {
            data[i][j] = loader.getImageData()[i][j];
        }
    }
}

// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = new double*[height];
    for(int i = 0; i < height; i++) {
        data[i] = new double[width];
        for(int j = 0; j < width; j++) {
            data[i][j] = 0.0;
        }
    }
}


// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = new double*[height];
    for(int i = 0; i < height; i++) {
        data[i] = new double[width];
        for(int j = 0; j < width; j++) {
            data[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) : height(other.height), width(other.width) {
    data = new double*[height];
    for(int i = 0; i < height; i++) {
        data[i] = new double[width];
        for(int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Destructor
ImageMatrix::~ImageMatrix() {
    for(int i = 0; i < height; i++) {
        delete[] data[i];
    }
    delete[] data;
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if(this == &other) {
        return *this;
    }
    
    for(int i = 0; i < height; i++) {
        delete[] data[i];
    }
    delete[] data;

    height = other.height;
    width = other.width;
    
    data = new double*[height];
    for(int i = 0; i < height; i++) {
        data[i] = new double[width];
        for(int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    if(height != other.height || width != other.width) {
        // Error handling: Throw an exception or return a blank matrix
        return ImageMatrix(); // Returning a blank matrix for now
    }

    ImageMatrix result(height, width);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    if(height != other.height || width != other.width) {
        // Error handling: Throw an exception or return a blank matrix
        return ImageMatrix(); // Returning a blank matrix for now
    }

    ImageMatrix result(height, width);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix result(height, width);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    if(i < 0 || i >= height || j < 0 || j >= width) {
        // Error handling: Throw an exception or return 0
        return 0; // Returning 0 for now
    }
    return data[i][j];
}

int ImageMatrix::get_height() const {
    return height;
}

int ImageMatrix::get_width() const {
    return width;
}
