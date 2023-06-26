/**
 * @file  Attribute.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"
#include "HashedString.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here
enum class RedefinitionMode : __int8
{
  KeepCurrent = 0x0,
  UpdateToNewDefault = 0x1,
};



#undef BEFORE_EXTRA

/**
 * @brief MC class Attribute.
 *
 */
class Attribute {

#define AFTER_EXTRA
// Add Member There
  RedefinitionMode mRedefinitionMode;
  bool mSyncable;
  uint32_t mIDValue;
  HashedString mName;


#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ATTRIBUTE
public:
    class Attribute& operator=(class Attribute const &) = delete;
    Attribute(class Attribute const &) = delete;
    Attribute() = delete;
#endif

public:
    /**
     * @symbol ??0Attribute\@\@QEAA\@AEBVHashedString\@\@W4RedefinitionMode\@\@_N\@Z
     */
    MCAPI Attribute(class HashedString const &, enum class RedefinitionMode, bool);
    /**
     * @symbol ?getName\@Attribute\@\@QEBAAEBVHashedString\@\@XZ
     */
    MCAPI class HashedString const & getName() const;
    /**
     * @symbol ?getRedefinitionMode\@Attribute\@\@QEBA?AW4RedefinitionMode\@\@XZ
     */
    MCAPI enum class RedefinitionMode getRedefinitionMode() const;
    /**
     * @symbol ?getByName\@Attribute\@\@SAAEAV1\@AEBVHashedString\@\@\@Z
     */
    MCAPI static class Attribute & getByName(class HashedString const &);

};