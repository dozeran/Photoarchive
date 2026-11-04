
#include "MetadataList.h"

#include <stdexcept>
#include <utility>

std::size_t MetadataList::copy_count_ = 0;
std::size_t MetadataList::move_count_ = 0;

MetadataList::MetadataList(std::size_t capacity)
    : items_(capacity > 0 ? new PhotoMetadata[capacity] : nullptr),
      size_(0),
      capacity_(capacity) {
}

// 1. Деструктор
MetadataList::~MetadataList() {
    delete[] items_;
}

// 2. Конструктор копіювання
MetadataList::MetadataList(const MetadataList& other)
    : items_(other.capacity_ > 0
                 ? new PhotoMetadata[other.capacity_]
                 : nullptr),
      size_(other.size_),
      capacity_(other.capacity_) {

    for (std::size_t i = 0; i < size_; ++i) {
        items_[i] = other.items_[i];
    }

    ++copy_count_;
}

// 3. Копіювальне присвоєння через copy-and-swap
MetadataList& MetadataList::operator=(const MetadataList& other) {
    if (this != &other) {
        MetadataList temp(other);
        swap(*this, temp);
    }

    return *this;
}

// 4. Конструктор переміщення
MetadataList::MetadataList(MetadataList&& other) noexcept
    : items_(other.items_),
      size_(other.size_),
      capacity_(other.capacity_) {

    other.items_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    ++move_count_;
}

// 5. Переміщувальне присвоєння
MetadataList& MetadataList::operator=(MetadataList&& other) noexcept {
    if (this != &other) {
        delete[] items_;

        items_ = other.items_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.items_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        ++move_count_;
    }

    return *this;
}

// Обмін внутрішніми даними двох об'єктів
void swap(MetadataList& first, MetadataList& second) noexcept {
    using std::swap;

    swap(first.items_, second.items_);
    swap(first.size_, second.size_);
    swap(first.capacity_, second.capacity_);
}

// Додавання елемента з автоматичним збільшенням місткості
void MetadataList::add(const PhotoMetadata& metadata) {
    if (size_ == capacity_) {
        const std::size_t new_capacity =
            capacity_ == 0 ? 1 : capacity_ * 2;

        PhotoMetadata* new_items = new PhotoMetadata[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_items[i] = items_[i];
        }

        delete[] items_;
        items_ = new_items;
        capacity_ = new_capacity;
    }

    items_[size_] = metadata;
    ++size_;
}

// Доступ до елемента з перевіркою індексу
PhotoMetadata& MetadataList::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("MetadataList index out of range");
    }

    return items_[index];
}

const PhotoMetadata& MetadataList::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("MetadataList index out of range");
    }

    return items_[index];
}

std::size_t MetadataList::size() const noexcept {
    return size_;
}

std::size_t MetadataList::capacity() const noexcept {
    return capacity_;
}

// Лічильники
void MetadataList::resetCounters() noexcept {
    copy_count_ = 0;
    move_count_ = 0;
}

std::size_t MetadataList::copyCount() noexcept {
    return copy_count_;
}

std::size_t MetadataList::moveCount() noexcept {
    return move_count_;
}
