
#include "Photo.h"

#include <utility>

Photo::Photo(const std::string& filename, std::size_t metadataCapacity)
    : filename_(filename),
      metadata_(metadataCapacity) {
}

const std::string& Photo::filename() const noexcept {
    return filename_;
}

void Photo::addMetadata(const PhotoMetadata& metadata) {
    metadata_.add(metadata);
}

const MetadataList& Photo::metadata() const noexcept {
    return metadata_;
}

std::size_t Photo::metadataCount() const noexcept {
    return metadata_.size();
}
