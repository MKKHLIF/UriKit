#pragma once
#include <memory>

class PercentDecoder {
public:
    ~PercentDecoder() noexcept;

    PercentDecoder(const PercentDecoder &) = delete;

    PercentDecoder(PercentDecoder &&) noexcept;

    PercentDecoder &operator=(const PercentDecoder &) = delete;

    PercentDecoder &operator=(PercentDecoder &&) noexcept;

    PercentDecoder();

    [[nodiscard]] bool next(char c) const;

    [[nodiscard]] bool done() const;

    [[nodiscard]] char getDecodedCharacter() const;

private:
    struct Impl;

    std::unique_ptr<Impl> impl_;
};
