#pragma once

#include <cstdint>
#include <random>

/// Mersenne twister based random number generator
/// Cryptographically secure, best distribution, but slower
struct Random
{
  typedef uint64_t Seed;

  /// Seeds the Mersenne-Twister devices with a cryptographically secure seed value
  Random();

  /// Get a cryptographically secure seed value
  /// \return The seed value
  Seed generateSeed() const;

  /// Generate a non-deterministic random 32-bit unsigned integer value
  /// If min and max are left at 0, the full range is used
  /// \param min Specifies the lower bounds of the range to generate numbers in
  /// \param max Specifies the upper bounds of the range to generate numbers in
  /// \return The random value
  uint32_t nextUInt32(uint32_t min = 0, uint32_t max = 0);

  /// Generate a non-determinstic random 32-bit signed integer value
  /// If min and max are left at 0, the full range is used
  /// \param min Specifies the lower bounds of the range to generate numbers in
  /// \param max Specifies the upper bounds of the range to generate numbers in
  /// \return The random value
  int32_t nextInt32(int32_t min = 0, int32_t max = 0);

  /// Generate a non-deterministic random 64-bit unsigned integer value
  /// If min and max are left at 0, the full range is used
  /// \param min Specifies the lower bounds of the range to generate numbers in
  /// \param max Specifies the upper bounds of the range to generate numbers in
  /// \return The random value
  uint64_t nextUInt64(uint64_t min = 0, uint64_t max = 0);

  /// Generate a non-deterministic random 64-bit signed integer value
  /// If min and max are left at 0, the full range is used
  /// \param min Specifies the lower bounds of the range to generate numbers in
  /// \param max Specifies the upper bounds of the range to generate numbers in
  /// \return The random value
  uint64_t nextInt64(int64_t min = 0, int64_t max = 0);

  /// Generate a pseudorandom float value
  /// \return 0.0 - 1.0 range float value
  float nextFloat();

  /// Generate a psudorandom double value
  /// \return 0.0 - 1.0 range double value
  double nextDouble();

private:
  std::mt19937 mt32;
  std::mt19937_64 mt64;
};

/// PCG hash based random number generator
/// Not the best distribution, limited type output, but fast
struct FastRandom
{
  uint32_t nextUint32();

  float nextFloat();

private:
  uint32_t pcgHash() const;

  uint32_t pcgHashIterative(uint32_t &seed) const;
};
