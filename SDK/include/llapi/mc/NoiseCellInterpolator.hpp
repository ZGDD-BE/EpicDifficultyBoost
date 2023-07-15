/**
 * @file  NoiseCellInterpolator.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class NoiseCellInterpolator.
 *
 */
class NoiseCellInterpolator {

#define AFTER_EXTRA
// Add Member There
public:
    gsl::span<const float> mInputValues;
    float mNoise000;
    float mNoise100;
    float mNoise001;
    float mNoise101;
    float mNoise010;
    float mNoise110;
    float mNoise011;
    float mNoise111;
    float mValueXY00;
    float mValueXY10;
    float mValueXY01;
    float mValueXY11;
    float mValueY0;
    float mValueY1;
    float mLerpedValue;
    float mXZDeltaSize;
    float mYDeltaSize;



#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_NOISECELLINTERPOLATOR
public:
    class NoiseCellInterpolator& operator=(class NoiseCellInterpolator const &) = delete;
    NoiseCellInterpolator(class NoiseCellInterpolator const &) = delete;
    NoiseCellInterpolator() = delete;
#endif

public:
    /**
     * @symbol ??0NoiseCellInterpolator\@\@QEAA\@V?$span\@$$CBM$0?0\@gsl\@\@HH\@Z
     */
    MCAPI NoiseCellInterpolator(class gsl::span<float const, -1>, int, int);
    /**
     * @symbol ??0NoiseCellInterpolator\@\@QEAA\@V?$span\@$$CBM$0?0\@gsl\@\@\@Z
     */
    MCAPI NoiseCellInterpolator(class gsl::span<float const, -1>);
    /**
     * @symbol ?getLerpedValue\@NoiseCellInterpolator\@\@QEBAMXZ
     */
    MCAPI float getLerpedValue() const;
    /**
     * @symbol ?selectCellXZ\@NoiseCellInterpolator\@\@QEAAXHHHH\@Z
     */
    MCAPI void selectCellXZ(int, int, int, int);
    /**
     * @symbol ?updateForX\@NoiseCellInterpolator\@\@QEAAXE\@Z
     */
    MCAPI void updateForX(unsigned char);
    /**
     * @symbol ?updateForZ\@NoiseCellInterpolator\@\@QEAAXE\@Z
     */
    MCAPI void updateForZ(unsigned char);

};
