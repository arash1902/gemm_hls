/// @author    Johannes de Fine Licht (definelicht@inf.ethz.ch)
/// @date      June 2018 
/// @copyright This software is copyrighted under the BSD 3-Clause License. 

#pragma once

#include "Config.h"
#include "hlslib/DataPack.h"
#include <type_traits>

constexpr int kSeed = 5; // For initializing matrices for testing

constexpr int kMemoryWidth = kMemoryWidthBytes / sizeof(Data_t);
static_assert(kMemoryWidthBytes % sizeof(Data_t) == 0,
              "Memory width not divisable by size of data type.");
using MemoryPack_t = hlslib::DataPack<Data_t, kMemoryWidth>;
using ComputePackN_t = hlslib::DataPack<Data_t, kComputeTileSizeN>;
using ComputePackM_t = hlslib::DataPack<Data_t, kComputeTileSizeM>;
using OutputPack_t =
    hlslib::DataPack<Data_t, kComputeTileSizeN * kComputeTileSizeM>;

constexpr int kTransposeWidth = kTransposeWidthBytes / sizeof(Data_t);
static_assert(kTransposeWidthBytes % sizeof(Data_t) == 0,
              "Transpose width must be divisable by data size.");
static_assert(kTransposeWidthBytes % kMemoryWidthBytes == 0,
              "Transpose width must be divisable by memory port width.");

constexpr int kSizeKMemory = kSizeK / kMemoryWidth;
static_assert(kSizeK % kMemoryWidth == 0,
              "K must be divisable by memory width.");

constexpr int kSizeMMemory = kSizeM / kMemoryWidth;
static_assert(kSizeM % kMemoryWidth == 0,
              "M must be divisable by memory width.");

constexpr int kOuterTileSizeMemory = kOuterTileSize / kMemoryWidth;
static_assert(kOuterTileSize % kMemoryWidth == 0,
              "Outer memory tile size must be divisable by memory port width.");

constexpr int kOuterTilesN = kSizeN / kOuterTileSize;
static_assert(kSizeN % kOuterTileSize == 0,
              "N must be divisable by the outer tile size.");

constexpr int kOuterTilesK = kSizeK / kOuterTileSize;
static_assert(kSizeK % kOuterTileSize == 0,
              "K must be divisable by the outer tile size.");

constexpr int kOuterTilesM = kSizeM / kOuterTileSize;
static_assert(kSizeM % kOuterTileSize == 0,
              "M must be divisable by the outer tile size.");

constexpr int kInnerTilesN = kOuterTileSize / kInnerTileSizeN;
static_assert(kOuterTileSize % kInnerTileSizeN == 0,
              "Outer tile size must be divisable by the inner tile size.");

constexpr int kInnerTilesM = kOuterTileSize / kInnerTileSizeM;
static_assert(kOuterTileSize % kInnerTileSizeM == 0,
              "Outer tile size must be divisable by the inner tile size.");

constexpr int kComputeTilesN = kInnerTileSizeN / kComputeTileSizeN;
static_assert(kInnerTileSizeN % kComputeTileSizeN == 0,
              "Inner tile size must be divisable by compute tile size.");

constexpr int kComputeTilesM = kInnerTileSizeM / kComputeTileSizeM;
static_assert(kInnerTileSizeM % kComputeTileSizeM == 0,
              "Inner tile size must be divisable by compute tile size.");

template <typename T,
          class = typename std::enable_if<std::is_integral<T>::value, T>::type>
constexpr T PowerOfTwo(T number, unsigned char power) {
  return (number > 0) ? PowerOfTwo(number >> 1, power + 1) : (1 << (power - 1));
}

extern "C" {

void MatrixMatrix(MemoryPack_t const *aMem, MemoryPack_t const *bMem,
                  MemoryPack_t *cMem);
}
