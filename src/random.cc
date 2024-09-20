#include "commons/random.hh"

#include <chrono>
#include <numeric>
#include <functional>

#if defined(WINDOWS)
#include <windows.h>
#include <ntsecapi.h>
#endif

uint64_t genSeed()
{
  uint64_t out = 0;
#if defined(WINDOWS)
  if(!RtlGenRandom(&out, 8))
  {
    out = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }
#elif defined(OSX) || defined(LINUX)
  FILE *urandFile = fopen("/dev/urandom", "rb");
    if(!urandFile)
    {
      out = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    else
    {
      size_t r = fread(&out, 8, 1, urandFile);
      fclose(urandFile);
    }
#endif
  return out;
}

Random::Random()
{
  const Seed seed = this->generateSeed();
  this->mt32.seed(seed);
  this->mt64.seed(seed);
}

Random::Seed Random::generateSeed() const
{
  return genSeed();
}

uint32_t Random::nextUInt32(uint32_t min, uint32_t max)
{
  if(min == 0 && max == 0)
  {
    return this->mt32();
  }
  else
  {
    return std::bind(std::uniform_int_distribution<uint32_t>(min, max), this->mt32)();
  }
}

int32_t Random::nextInt32(int32_t min, int32_t max)
{
  if(min == 0 && max == 0)
  {
    return std::bind(std::uniform_int_distribution<int32_t>(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()), this->mt32)();
  }
  else
  {
    return std::bind(std::uniform_int_distribution<uint32_t>(min, max), this->mt32)();
  }
}

uint64_t Random::nextUInt64(uint64_t min, uint64_t max)
{
  if(min == 0 && max == 0)
  {
    return this->mt64();
  }
  else
  {
    return std::bind(std::uniform_int_distribution<uint64_t>(min, max), this->mt64)();
  }
}

uint64_t Random::nextInt64(int64_t min, int64_t max)
{
  if(min == 0 && max == 0)
  {
    return std::bind(std::uniform_int_distribution<int64_t>(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max()), this->mt64)();
  }
  else
  {
    return std::bind(std::uniform_int_distribution<uint64_t>(min, max), this->mt64)();
  }
}

float Random::nextFloat()
{
  return std::bind(std::uniform_real_distribution<float>(0, 1), this->mt32)();
}

double Random::nextDouble()
{
  return std::bind(std::uniform_real_distribution<double>(0, 1), this->mt64)();
}

uint32_t FastRandom::nextUint32() const
{
  return this->pcgHash();
}

float FastRandom::nextFloat() const
{
  const uint64_t rng = this->pcgHash();
  return (float)rng / (float)std::numeric_limits<uint32_t>::max();
}

uint32_t FastRandom::pcgHash() const
{
  uint32_t state = genSeed() * 747796405u + 2891336453u;
  uint32_t word = ((state >> ((state >> 28u) + 4u) * 277803737u));
  return (word >> 22u) ^ word;
}

uint32_t FastRandom::pcgHashIterative(const uint32_t &seed) const
{
  uint32_t state = seed * 747796405u + 2891336453u;
  uint32_t word = ((state >> ((state >> 28u) + 4u) * 277803737u));
  return (word >> 22u) ^ word;
}
