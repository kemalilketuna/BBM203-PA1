import zipfile

# List of files to be zipped
files = [
    "Convolution.cpp",
    "Convolution.h",
    "DecodeMessage.cpp",
    "DecodeMessage.h",
    "EdgeDetector.cpp",
    "EdgeDetector.h",
    "EncodeMessage.cpp",
    "EncodeMessage.h",
    "ImageLoader.h",
    "ImageLoader.cpp",
    "ImageMatrix.h",
    "ImageMatrix.cpp",
    "ImageProcessor.cpp",
    "ImageProcessor.h",
    "ImageSharpening.h",
    "ImageSharpening.cpp"
]

# Create a new zip file (or overwrite if it exists)
with zipfile.ZipFile("b2220356127.zip", "w") as z:
    for file in files:
        z.write(file)

print("Files zipped successfully into output.zip")