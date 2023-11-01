#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    return DecodeMessage().decodeFromImage(ImageSharpening().sharpen(img,2), EdgeDetector().detectEdges(ImageSharpening().sharpen(img,2)));
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    return EncodeMessage().encodeMessageToImage(img, message, EdgeDetector().detectEdges(img));
}