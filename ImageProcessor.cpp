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

    // Create a DecodeMessage object and decode the hidden message from the sharpened image
    return DecodeMessage().decodeFromImage(sharpenedImg, edgeDetector.detectEdges(sharpenedImg));
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    // Create an EdgeDetector object
    EdgeDetector edgeDetector;

    // Create an EncodeMessage object and encode the message to the image
    return EncodeMessage().encodeMessageToImage(img, message, edgeDetector.detectEdges(ImageSharpening().sharpen(img, 2)));
}
