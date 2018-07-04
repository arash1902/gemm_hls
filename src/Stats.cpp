#include "MatrixMatrix.h"
#include "Memory.h"

// Prints the expected performance of the current configuration in hardware.
// If a different frequency is achieved, it can be passed as the first argument
// to the executable.
int main(int argc, char **argv) {
  float frequency = kFrequency;
  if (argc > 1) {
    frequency = std::stof(argv[1]);
  }
  const unsigned long long nOps =
      2 * static_cast<unsigned long long>(kSizeN) * kSizeK * kSizeM;
  std::cout << "Frequency:            " << frequency << " MHz\n";
  std::cout << "Number of operations: " << nOps << " ("
            << static_cast<float>(nOps) << ")\n";
  const auto peakPerf = 2e-3 * kInnerTileSizeN * kInnerTileSizeM * frequency;
  std::cout << "Peak performance:     " << peakPerf << " GOp/s\n";
  std::cout << "Peak runtime:         " << nOps / (1e9 * peakPerf)
            << " seconds.\n";

  // std::cout << (static_cast<unsigned long>(kOuterTilesN) * kOuterTilesM * kOuterTilesK *
  //      (kOuterTileSize / kTransposeWidth) * kInnerTilesN * kInnerTileSizeN *
  //      kTransposeWidth * MemoryPack_t::kWidth)
  //           << std::endl;
  //
  // std::cout << kTotalReadsFromA << std::endl;

  std::cout << static_cast<unsigned long>(kOuterTilesN) * kOuterTilesM *
                    kOuterTileSize * kInnerTileSizeN << std::endl;
  std::cout << kTotalReadsFromA / kComputeTilesN << std::endl;
  return 0;
}
