#ifndef FED_LOG_H
#define FED_LOG_H

#include <stdio.h>


/**
 * @file fed_log.h
 * @brief Federation logging utilities.
 */


/**
 * @fn FLog_errorCallback(int error, const char* description)
 * @brief Error callback used by GLFW. Print ERROR_CALLBACK message to STDERR.
 */
void FErrorCallback(
    int         error,
    const char* description);

/**
 * @fn FLog_errorMsg(const char* message)
 * @brief Print ERROR message to STDERR.
 */
void FErrorMsg(const char* message);

/**
 * @fn FLog_warningMsg(const char* message)
 * @brief Print WARNING message to STDOUT.
 */
void FWarningMsg(const char* message);

/**
 * @fn FLog_infoMsg(const char* message)
 * @brief Print INFO message to STDOUT.
 */
void FInfoMsg(const char* message);

/**
 * @fn FLog_debugMsg(const char* message)
 * @brief Print DEBUG message to STDOUT.
 */
void FDebugMsg(const char* message);


#endif
