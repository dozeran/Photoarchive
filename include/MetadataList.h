
#ifndef METADATA_LIST_H
#define METADATA_LIST_H

#include "PhotoMetadata.h"

#include <cstddef>
#include <utility>

class MetadataList {
public:
    MetadataList() = default;
    explicit MetadataList(std::size_t capacity);

    // Rule of Five

    // 1. Деструктор звільняє пам'ять, якою володіє об'єкт.
    ~MetadataList();

    // 2. Конструктор копіювання створює незалежну копію масиву.
    MetadataList(const MetadataList& other);

    // 3. Копіювальне присвоєння використовує copy-and-swap.
    MetadataList& operator=(const MetadataList& other);

    // 4. Конструктор переміщення передає володіння масивом.
    MetadataList(MetadataList&& other) noexcept;

    // 5. Переміщувальне присвоєння передає володіння масивом.
    MetadataList& operator=(MetadataList&& other) noexcept;

    void add(const PhotoMetadata& metadata);

    PhotoMetadata& at(std::size_t index);
    const PhotoMetadata& at(std::size_t index) const;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;

    static void resetCounters() noexcept;
    static std::size_t copyCount() noexcept;
    static std::size_t moveCount() noexcept;

    friend void swap(MetadataList& first, MetadataList& second) noexcept;

private:
    PhotoMetadata* items_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    static std::size_t copy_count_;
    static std::size_t move_count_;
};

#endif
