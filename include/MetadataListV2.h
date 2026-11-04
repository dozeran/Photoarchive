
#ifndef METADATA_LIST_V2_H
#define METADATA_LIST_V2_H

#include "PhotoMetadata.h"

#include <cstddef>
#include <stdexcept>
#include <vector>

class MetadataListV2 {
public:
    void add(const PhotoMetadata& metadata) {
        items_.push_back(metadata);
    }

    PhotoMetadata& at(std::size_t index) {
        return items_.at(index);
    }

    const PhotoMetadata& at(std::size_t index) const {
        return items_.at(index);
    }

    std::size_t size() const noexcept {
        return items_.size();
    }

private:
    std::vector<PhotoMetadata> items_;
};

#endif
