#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>

namespace surf {

using level_t = uint32_t;
using position_t = uint32_t;

using label_t = uint8_t;
static const position_t kFanout = 256;

using word_t = uint64_t;
static const unsigned kWordSize = 64;
static const word_t kMsbMask = 0x8000000000000000;
static const word_t kOneMask = 0xFFFFFFFFFFFFFFFF;

static const bool kIncludeDense = true;
static const uint32_t kSparseDenseRatio = 64;
static const label_t kTerminator = 255;

enum SuffixType {
    kNone = 0,
    kHash = 1,
    kReal = 2
};

static std::string uint64ToString(const uint64_t word) {
    uint64_t endian_swapped_word = __builtin_bswap64(word);
    return std::string(reinterpret_cast<const char*>(&endian_swapped_word), 8);
}

static uint64_t stringToUint64(const std::string& str_word) {
    uint64_t int_word = 0;
    memcpy(reinterpret_cast<char*>(&int_word), str_word.data(), 8);
    return __builtin_bswap64(int_word);
}

static void clearMSBits(word_t& word, const position_t content_len) {
    word <<= (kWordSize - content_len);
    word >>= (kWordSize - content_len);
}

} // namespace surf

#endif // CONFIG_H_
