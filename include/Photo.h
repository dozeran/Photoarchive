
#ifndef PHOTO_H
#define PHOTO_H

#include "MetadataList.h"

#include <string>

class Photo {
public:
    Photo(const std::string& filename, std::size_t metadataCapacity = 0);

    const std::string& filename() const noexcept;

    void addMetadata(const PhotoMetadata& metadata);

    const MetadataList& metadata() const noexcept;

    std::size_t metadataCount() const noexcept;

private:
    std::string filename_;
    MetadataList metadata_;
};

#endif
