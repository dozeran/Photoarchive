
#include "MetadataList.h"
#include "MetadataListV2.h"
#include "Photo.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

// 1. Перевірка глибокого копіювання
TEST(MetadataListTest, DeepCopy) {
    MetadataList original(2);
    original.add({"nature", 48.0, 24.0});

    MetadataList copy(original);

    EXPECT_EQ(copy.size(), 1);
    EXPECT_EQ(copy.at(0).tag, "nature");
}

// 2. Перевірка незалежності копій
TEST(MetadataListTest, CopyIndependence) {
    MetadataList original(2);
    original.add({"nature", 48.0, 24.0});

    MetadataList copy(original);
    copy.at(0).tag = "travel";

    EXPECT_EQ(original.at(0).tag, "nature");
    EXPECT_EQ(copy.at(0).tag, "travel");
}

// 3. Перевірка копіювального присвоєння
TEST(MetadataListTest, CopyAssignment) {
    MetadataList first(2);
    first.add({"forest", 49.0, 25.0});

    MetadataList second(1);
    second = first;

    EXPECT_EQ(second.size(), 1);
    EXPECT_EQ(second.at(0).tag, "forest");
}

// 4. Перевірка самоприсвоєння
TEST(MetadataListTest, SelfAssignment) {
    MetadataList list(2);
    list.add({"mountains", 48.0, 24.0});

    MetadataList& self = list;
    list = self;

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.at(0).tag, "mountains");
}

// 5. Перевірка конструктора переміщення
TEST(MetadataListTest, MoveConstructor) {
    MetadataList original(2);
    original.add({"travel", 50.0, 30.0});

    MetadataList moved(std::move(original));

    EXPECT_EQ(moved.size(), 1);
    EXPECT_EQ(original.size(), 0);
}

// 6. Перевірка переміщувального присвоєння
TEST(MetadataListTest, MoveAssignment) {
    MetadataList first(2);
    first.add({"city", 50.0, 30.0});

    MetadataList second(1);
    second.add({"old", 0.0, 0.0});

    second = std::move(first);

    EXPECT_EQ(second.size(), 1);
    EXPECT_EQ(second.at(0).tag, "city");
    EXPECT_EQ(first.size(), 0);
}

// 7. Перевірка виходу за межі масиву
TEST(MetadataListTest, BoundsChecking) {
    MetadataList list(1);

    EXPECT_THROW(list.at(0), std::out_of_range);
}

// 8. Перевірка взаємодії з класом Photo
TEST(PhotoTest, Integration) {
    Photo photo("photo.jpg");
    photo.addMetadata({"sea", 46.0, 32.0});

    EXPECT_EQ(photo.filename(), "photo.jpg");
    EXPECT_EQ(photo.metadataCount(), 1);
    EXPECT_EQ(photo.metadata().at(0).tag, "sea");
}

// 9. Перевірка правила нуля
TEST(MetadataListV2Test, RuleOfZeroCopyIndependence) {
    MetadataListV2 original;
    original.add({"forest", 49.0, 25.0});

    MetadataListV2 copy = original;
    copy.at(0).tag = "city";

    EXPECT_EQ(original.at(0).tag, "forest");
    EXPECT_EQ(copy.at(0).tag, "city");
}
