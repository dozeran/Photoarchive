#ifndef PHOTO_METADATA_H
#define PHOTO_METADATA_H

#include <string>

struct PhotoMetadata {
    std::string tag;
    double latitude;
    double longitude;
};

#endif