#include <global.h>

#include <llapi/mc/NetherGenerator.hpp>
#include <llapi/mc/ChunkPos.hpp>
#include <llapi/mc/BlockVolume.hpp>
#include <llapi/mc/NoiseCellInterpolator.hpp>
#include <llapi/mc/BedrockBlockTypes.hpp>
#include <llapi/mc/BlockTypeRegistry.hpp>
#include <llapi/mc/VanillaBlockTypeIds.hpp>
#include <llapi/mc/ChunkSource.hpp>
#include <llapi/mc/Dimension.hpp>
#include <llapi/mc/ChunkBlockPos.hpp>
#include <span>
#include <gsl/string_span>
#include <llapi/mc/PerlinNoise.hpp>

//TInstanceHook(void, "?_prepareHeights@NetherGenerator@@AEAAXAEAVBlockVolume@@AEBVChunkPos@@_NPEAV?$vector@FV?$allocator@F@std@@@std@@H@Z",
//    NetherGenerator,
//    BlockVolume* box,
//    const ChunkPos* chunkPos,
//    bool factorInBeardsAndShavers,
//    std::vector<short>* ZXheights) {
//    const Block& air = BedrockBlockTypes::mAir->getDefaultState();
//    const Block& grass = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Grass, true);
//    const Block& dirt = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Dirt, true);
//    const Block& stone = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Stone, true);
//    const Block& bedrock = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Bedrock, true);
//
//    PerlinNoise generator(233, 8, 1); // Assuming PerlinNoise takes seed, levels, and minLevel as parameters
//
//    for (int x = 0; x < 16; x++) {
//        for (int z = 0; z < 16; z++) {
//            Vec3 pos(chunkPos->x * 16 + x, 0, chunkPos->z * 16 + z);
//            int currentHeight = static_cast<int>(generator.getValue(pos) * 15 + 50);
//            for (int y = 0; y < 30; y++) {
//                BlockPos blockPos(x, y, z);
//                const Block& block = y <= currentHeight ? (y == currentHeight ? grass : (y == currentHeight - 1 ? dirt : stone)) : air;
//                size_t index = box->index(blockPos);
//
//                if (index < box->mBlocks.size()) {
//                    box->mBlocks[index] = &block;
//                }
//                if (ZXheights != nullptr && y == box->mHeight - 1) {
//                    ZXheights->at(z * box->mWidth + x) = currentHeight;
//                }
//            }
//        }
//    }
//}

#include <llapi/mc/OverworldGeneratorMultinoise.hpp>
#include <llapi/mc/Aquifer.hpp>
#include <llapi/mc/WorldGenCache.hpp>
#include <functional>

#include <vector>
#include <array>

template <typename T>
class ScalarOptional {
public:
    T mValue;
};


class SeamlessChunkBlendingAttenuatorUtil {
public:
    class AttenuationData
    {
    public:
        float mDistanceToBlendTarget;
        ScalarOptional<float> mBlendTargetHeight;
        std::array<ScalarOptional<float>, 41> mBlendTargetDensities;
        std::array<ScalarOptional<unsigned char>, 96> mBiomes;
        std::array<ScalarOptional<enum BlendingBlockType>, 41> mBorderBlocks;
    };
};

class Pos2d {
public:
    int x;
    int z;
};

template <int N>
class DividedPos2d : public Pos2d {
};

class SeamlessChunkBlendingAttenuator {
public:
    std::vector<std::array<SeamlessChunkBlendingAttenuatorUtil::AttenuationData, 4>> mChunkAttenuationData;
    DividedPos2d<4> mMinPos;
    int16_t mMinHeight;

    SeamlessChunkBlendingAttenuatorUtil::AttenuationData& getAttenuationData(int x, int z) {
        // Assuming x and z are within the valid range
        return mChunkAttenuationData[x][z];
    }
};


#include <llapi/mc/BlockSource.hpp>
#include <llapi/mc/SimplexNoise.hpp>
#include <llapi/mc/IRandom.hpp>
TInstanceHook(void, "?_prepareHeights@OverworldGeneratorMultinoise@@EEAAXAEAVBlockVolume@@AEBVChunkPos@@AEBVWorldGenCache@@PEAVAquifer@@$$QEAV?$function@$$A6AXAEBVBlockPos@@AEBVBlock@@H@Z@std@@_NPEAV?$vector@FV?$allocator@F@std@@@7@H@Z",
    OverworldGeneratorMultinoise,
    BlockVolume* box,
    const ChunkPos* chunkPos,
    const WorldGenCache* worldGenCache,
    Aquifer* aquiferPtr,
    std::function<void(BlockPos const&, Block const&, int)>* tickUpdateFn,
    bool factorInBeardsAndShavers,
    SeamlessChunkBlendingAttenuator* ZXheights) {
    Dimension* dimension = &((BlockSource*)(this))->getDimension();
    const Block& stone = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Stone, 1);
    const Block& dirt = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Dirt, 1);
    const Block& grass = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Grass, 1);
    const Block& bedrock = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Bedrock, 1);
    const Block& air = BedrockBlockTypes::mAir->getDefaultState();
    PerlinNoise generator(233, 8, 1); // Assuming PerlinNoise takes seed, levels, and minLevel as parameters

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            for (int y = 0; y < 320; y++) {
                Vec3 pos(chunkPos->x * 16 + x, 0, chunkPos->z * 16 + z);
                double noiseValue = generator.getValue(pos);
                // Map noise from [-1, 1] to [0, 1]
                noiseValue = (noiseValue + 1) / 2.0;
                // Map noise to desired height range
                int currentHeight = static_cast<int>(noiseValue*1.4 + 150); // 40 is the desired height range, 60 is the desired minimum height
                BlockPos blockPos(x, y, z);
                const Block& block = y <= currentHeight ? (y == currentHeight ? grass : (y == currentHeight - 1 ? dirt : stone)) : air;
                size_t index = box->index(blockPos);

                if (index < box->mBlocks.size()) {
                    box->mBlocks[index] = &block;
                }
                //if (ZXheights != nullptr && y == box->mHeight - 1) {
                //    ZXheights->getAttenuationData(x, z).mBlendTargetHeight.mValue = currentHeight;
                //}
            }
        }
    }
}









