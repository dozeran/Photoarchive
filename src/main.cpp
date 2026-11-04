
#include "MetadataListV2.h"
#include "Photo.h"

#include <iostream>

int main() {
    Photo photo("mountains.jpg");

    photo.addMetadata({"mountains", 48.9226, 24.7111});
    photo.addMetadata({"nature", 48.9230, 24.7120});

    std::cout << "Photo: " << photo.filename() << '\n';
    std::cout << "Metadata count: " << photo.metadataCount() << '\n';

    for (std::size_t i = 0; i < photo.metadataCount(); ++i) {
        const auto& item = photo.metadata().at(i);

        std::cout << "Tag: " << item.tag
                  << ", latitude: " << item.latitude
                  << ", longitude: " << item.longitude
                  << '\n';
    }

    // Демонстрація версії за правилом нуля
    MetadataListV2 metadataV2;
    metadataV2.add({"travel", 50.4501, 30.5234});

    std::cout << "\nRule of Zero version:\n";
    std::cout << "Metadata count: " << metadataV2.size() << '\n';

    return 0;
}
