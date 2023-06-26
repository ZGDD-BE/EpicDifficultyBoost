/**
 * @file  ContentLogFileEndPoint.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"
#include "Core.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class ContentLogFileEndPoint.
 *
 */
class ContentLogFileEndPoint {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CONTENTLOGFILEENDPOINT
public:
    class ContentLogFileEndPoint& operator=(class ContentLogFileEndPoint const &) = delete;
    ContentLogFileEndPoint(class ContentLogFileEndPoint const &) = delete;
    ContentLogFileEndPoint() = delete;
#endif

public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_CONTENTLOGFILEENDPOINT
    /**
     * @symbol ?flush\@ContentLogFileEndPoint\@\@UEAAXXZ
     */
    MCVAPI void flush();
    /**
     * @symbol ?isEnabled\@ContentLogFileEndPoint\@\@UEBA_NXZ
     */
    MCVAPI bool isEnabled() const;
    /**
     * @symbol ?log\@ContentLogFileEndPoint\@\@UEAAXW4LogArea\@\@W4LogLevel\@\@PEBD\@Z
     */
    MCVAPI void log(enum class LogArea, enum class LogLevel, char const *);
    /**
     * @symbol ?logOnlyOnce\@ContentLogFileEndPoint\@\@UEBA_NXZ
     */
    MCVAPI bool logOnlyOnce() const;
    /**
     * @symbol ?setEnabled\@ContentLogFileEndPoint\@\@UEAAX_N\@Z
     */
    MCVAPI void setEnabled(bool);
#endif
    /**
     * @symbol ??0ContentLogFileEndPoint\@\@QEAA\@VPath\@Core\@\@0V?$optional\@W4LogLevel\@\@\@std\@\@\@Z
     */
    MCAPI ContentLogFileEndPoint(class Core::Path, class Core::Path, class std::optional<enum class LogLevel>);
    /**
     * @symbol ?FILE_NAME\@ContentLogFileEndPoint\@\@2V?$basic_string_view\@DU?$char_traits\@D\@std\@\@\@std\@\@B
     */
    MCAPI static class std::basic_string_view<char, struct std::char_traits<char>> const FILE_NAME;

};
