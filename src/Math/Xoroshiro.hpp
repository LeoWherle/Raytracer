
#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <type_traits>

inline constexpr std::uint64_t DefaultSeed = 1234567890ULL;

// SplitMix64
// Original implementation: http://prng.di.unimi.it/splitmix64.c
class SplitMix64 {
public:
    inline explicit constexpr SplitMix64(std::uint64_t state = DefaultSeed) noexcept:
        m_state(state) {};

    inline constexpr std::uint64_t operator()() noexcept
    {
        std::uint64_t z = (m_state += UINT64_C(0x9e3779b97f4a7c15));
        z = (z ^ (z >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
        z = (z ^ (z >> 27)) * UINT64_C(0x94d049bb133111eb);
        return z ^ (z >> 31);
    }

    static constexpr std::uint64_t min() noexcept { return std::numeric_limits<std::uint64_t>::lowest(); }

    static constexpr std::uint64_t max() noexcept { return std::numeric_limits<std::uint64_t>::max(); }

    friend bool operator==(const SplitMix64 &lhs, const SplitMix64 &rhs) noexcept
    {
        return (lhs.m_state == rhs.m_state);
    }

    friend bool operator!=(const SplitMix64 &lhs, const SplitMix64 &rhs) noexcept
    {
        return (lhs.m_state != rhs.m_state);
    }

private:
    std::uint64_t m_state;
};

// xoshiro128+
// Original implementation: http://prng.di.unimi.it/xoshiro128plus.c
class Xoshiro128Plus {
public:
    using s_table = std::array<std::uint32_t, 4>;

    inline explicit constexpr Xoshiro128Plus(std::uint64_t seed = DefaultSeed) noexcept:
        m_state()
    {
        SplitMix64 splitmix {seed};

        for (auto &state : m_state) {
            state = static_cast<std::uint32_t>(splitmix());
        }
    }

    inline static constexpr std::uint32_t rotl(const std::uint32_t x, const int s) noexcept
    {
        return (x << s) | (x >> (32 - s));
    }

    inline constexpr std::uint32_t operator()() noexcept
    {
        const std::uint32_t result = m_state[0] + m_state[3];
        const std::uint32_t t = m_state[1] << 9;
        m_state[2] ^= m_state[0];
        m_state[3] ^= m_state[1];
        m_state[1] ^= m_state[2];
        m_state[0] ^= m_state[3];
        m_state[2] ^= t;
        m_state[3] = rotl(m_state[3], 11);
        return result;
    }

    // This is the jump function for the generator. It is equivalent
    // to 2^64 calls to next(); it can be used to generate 2^64
    // non-overlapping subsequences for parallel computations.
    inline constexpr void jump() noexcept
    {
        constexpr std::uint32_t JUMP[] = {0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b};

        std::uint32_t s0 = 0;
        std::uint32_t s1 = 0;
        std::uint32_t s2 = 0;
        std::uint32_t s3 = 0;

        for (std::uint32_t jump : JUMP) {
            for (int b = 0; b < 32; ++b) {
                if (jump & UINT32_C(1) << b) {
                    s0 ^= m_state[0];
                    s1 ^= m_state[1];
                    s2 ^= m_state[2];
                    s3 ^= m_state[3];
                }
                operator()();
            }
        }

        m_state[0] = s0;
        m_state[1] = s1;
        m_state[2] = s2;
        m_state[3] = s3;
    }

    // This is the long-jump function for the generator. It is equivalent to
    // 2^96 calls to next(); it can be used to generate 2^32 starting points,
    // from each of which jump() will generate 2^32 non-overlapping
    // subsequences for parallel distributed computations.
    inline constexpr void longJump() noexcept
    {
        constexpr std::uint32_t LONG_JUMP[] = {0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662};

        std::uint32_t s0 = 0;
        std::uint32_t s1 = 0;
        std::uint32_t s2 = 0;
        std::uint32_t s3 = 0;

        for (std::uint32_t jump : LONG_JUMP) {
            for (int b = 0; b < 32; ++b) {
                if (jump & UINT32_C(1) << b) {
                    s0 ^= m_state[0];
                    s1 ^= m_state[1];
                    s2 ^= m_state[2];
                    s3 ^= m_state[3];
                }
                operator()();
            }
        }

        m_state[0] = s0;
        m_state[1] = s1;
        m_state[2] = s2;
        m_state[3] = s3;
    }

    inline static constexpr std::uint32_t min() noexcept
    {
        return std::numeric_limits<std::uint32_t>::lowest();
    }

    inline static constexpr std::uint32_t max() noexcept { return std::numeric_limits<std::uint32_t>::max(); }

    friend bool operator==(const Xoshiro128Plus &lhs, const Xoshiro128Plus &rhs) noexcept
    {
        return (lhs.m_state == rhs.m_state);
    }

    friend bool operator!=(const Xoshiro128Plus &lhs, const Xoshiro128Plus &rhs) noexcept
    {
        return (lhs.m_state != rhs.m_state);
    }

private:
    s_table m_state;
};
