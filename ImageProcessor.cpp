#include "ImageProcessor.h"

// Default constructor
ImageProcessor::ImageProcessor() {

}

// Destructor
ImageProcessor::~ImageProcessor() {

}

std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    // Create an ImageSharpening object
    ImageSharpening imgSharpener;

    // Sharpen the image
    ImageMatrix sharpenedImg = imgSharpener.sharpen(img, 2);

    // Create an EdgeDetector object
    EdgeDetector edgeDetector;
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(sharpenedImg);

    DecodeMessage decodeMessage;
    // Create a DecodeMessage object and decode the hidden message from the sharpened image
    return decodeMessage.decodeFromImage(sharpenedImg, edgePixels);
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    // Create an ImageSharpening object
    ImageSharpening imgSharpener;

    // Sharpen the image
    ImageMatrix sharpenedImg = imgSharpener.sharpen(img, 2);
    
    // Create an EdgeDetector object
    EdgeDetector edgeDetector;
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(sharpenedImg);

    // Create an EncodeMessage object
    EncodeMessage encodeMessage;

    // Create an EncodeMessage object and encode the message to the image
    return encodeMessage.encodeMessageToImage(img, message, edgePixels);
}
