#pragma once

#include <cstddef>
#include <typeinfo>
#include <utility>
#include <cstdint>

template <class Iterator>
class Sequence {
public:
    Sequence(Iterator begin, Iterator end)
        : begin_{std::move(begin)}, end_{std::move(end)}, it_(begin_) {
    }

    [[nodiscard]] Iterator begin() const {
        return begin_;
    }

    [[nodiscard]] Iterator end() const {
        return end_;
    }

    auto operator*() {
        return *it_;
    }

    Iterator& operator++() {
        return ++it_;
    }

private:
    Iterator begin_, end_, it_;
};

template <class Iterator>
class RepeatIterator {
public:
    RepeatIterator(Iterator begin, Iterator end, size_t count = 0)
        : begin_{begin}, it_{begin}, end_{end}, count_{count} {
    }

    RepeatIterator& operator++() {
        if (!(++it_ != end_)) {
            ++count_;
            it_ = begin_;
        }
        return *this;
    }

    auto operator*() const {
        return *it_;
    }
    bool operator==(const RepeatIterator& rhs) const = default;

private:
    Iterator begin_, it_, end_;
    size_t count_;
};

auto Repeat(const auto& sequence, size_t n) {
    auto begin = sequence.begin();
    auto end = sequence.end();
    if (n && (begin != end)) {
        return Sequence{RepeatIterator{begin, end}, RepeatIterator{begin, end, n}};
    }
    return Sequence{RepeatIterator{end, end}, RepeatIterator{end, end}};
}

template <class Iterator1, class Iterator2>
class ZipIterator {
public:
    ZipIterator(Iterator1 begin1, Iterator2 begin2)
        : begin1_(std::move(begin1)), it1_(begin1_), begin2_(std::move(begin2)), it2_(begin2_) {
    }
    ZipIterator& operator++() {
        ++it1_;
        ++it2_;
        return *this;
    }
    bool operator==(const ZipIterator& rhs) const {
        return it1_ == rhs.it1_ || it2_ == rhs.it2_;
    }
    auto operator*() {
        return std::pair{*it1_, *it2_};
    }

private:
    Iterator1 begin1_, it1_;
    Iterator2 begin2_, it2_;
};

auto Zip(const auto& a, const auto& b) {
    auto it1 = ZipIterator{a.begin(), b.begin()};
    auto it2 = ZipIterator{a.end(), b.end()};
    return Sequence{it1, it2};
}

class Range {
public:
    Range(int64_t from, int64_t to) : Range(from, to, 1) {
    }
    Range(int64_t from, int64_t to, int64_t step)
        : begin_(from, step),
          end_(from + ((to - from) / step + ((to - from) % step != 0 ? 1 : 0)) * step, step) {
    }

    explicit Range(int64_t to) : Range(0, to, 1) {
    }

    class Iterator {
    public:
        explicit Iterator(int64_t value, int64_t step) : value_(value), step_(step) {
        }
        Iterator(const Iterator&) = default;
        Iterator(const Iterator&& rhs) noexcept : Iterator(rhs.value_, rhs.step_) {
        }
        Iterator& operator=(const Iterator& rhs) = default;
        Iterator& operator=(const Iterator&& rhs) = delete;
        ~Iterator() = default;
        int64_t operator*() const {
            return value_;
        }
        Iterator& operator++() {
            value_ += step_;
            return *this;
        }
        bool operator==(const Iterator& rhs) const = default;

    private:
        int64_t value_;
        int64_t step_;
    };
    [[nodiscard]] Iterator begin() const {
        return begin_;
    }
    [[nodiscard]] Iterator end() const {
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <typename Iterator>
class GroupIterator {
public:
    GroupIterator(Iterator begin, Iterator end)
        : end_(end), current_begin_(begin), current_end_(begin) {
        while (current_end_ != end && *current_end_ == *begin) {
            ++current_end_;
        }
    }
    auto operator*() {
        return Sequence{current_begin_, current_end_};
    }
    GroupIterator& operator++() {
        current_begin_ = current_end_;
        while (current_end_ != end_ && *current_end_ == *current_begin_) {
            ++current_end_;
        }
        return *this;
    }
    bool operator==(const GroupIterator& rhs) const {
        return current_begin_ == rhs.current_begin_ && current_end_ == rhs.current_end_;
    }

private:
    Iterator end_;
    Iterator current_begin_, current_end_;
};

template <typename T>
auto Group(const T& seq) {
    return Sequence{GroupIterator{seq.begin(), seq.end()}, GroupIterator{seq.end(), seq.end()}};
}
