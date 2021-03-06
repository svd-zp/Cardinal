//
//  Logger.h
//  iMapMy3
//
//  Created by James Humphrey on 9/17/09.
//  Copyright 2009-2010 MapMyFitness, Inc. All rights reserved.
//

@import UIKit;
@import UASDKInternal;

@protocol Loggable;

@interface Logger : NSObject <UALoggerDelegate>

/**
 *
 * Macros
 * ------------------------------------------------------------------
 *
 * The usage of these macros are strongly preferred.
 * Each macro comes in two flavors: one that includes a general
 * category, and one that does not.
 *
 * Use Log[Severity]Category() to specify a category that you
 * would like to log against. For example:
 *
 *  LogInfoCategory( UALoggerCategoryNetwork, @"The network is down." );
 *
 *  This turns into: @"[NETWORK] -[method](line) The network is down."
 *
 * Be smart when choosing severity levels. Loggers have their own preferred
 * tolerance level. Choosing the wrong kind of severity can lead to a logger
 * not saving your statement. Some examples on use cases:
 *
 * - Debug: Something you want logged for debugging/testing purposes.
 *
 * - Info: Events of some importance that happen (i.e. button was tapped,
 *   view was displayed, network reachability status, etc.)
 *
 * - Warning: Events that do not follow the happy path, or events that
 *   are allowed, but aren't necessarily satisfiable (i.e. workout failed
 *   to sync, web request timed out, memory pressure was issued, etc.)
 *
 * - Error: Events that aren't acceptable and should not happen (i.e.
 *   server returned a 400-500, an exception was thrown and was caught,
 *   core data store failed to mount, etc.)
 *
 **/

/**
 *  A macro that conveniently sets the file, function, and line number of a log statement.
 *
 *  @param s   The severity of the message.
 *  @param c   The category of the message.
 *  @param f   A format string
 *  @param ... A list of C-style arguments.
 */
#define Log( s, c, f, ... ) \
[Logger log:s category:c file:__FILE__ function:__PRETTY_FUNCTION__ lineNumber:__LINE__ format:f, ## __VA_ARGS__]

// Debug
#define LogDebugCategory( category, format, ...) \
Log( UALoggerSeverityLevelDebug, category, format, ##__VA_ARGS__ )

#define LogDebug( format, ... ) \
LogDebugCategory( UALoggerCategoryGeneral, format, ##__VA_ARGS__ )

// Info
#define LogInfoCategory( category, format, ...) \
Log( UALoggerSeverityLevelInfo, category, format, ##__VA_ARGS__ )

#define LogInfo( format, ... ) \
LogInfoCategory( UALoggerCategoryGeneral, format, ##__VA_ARGS__ )

// Warning
#define LogWarningCategory( category, format, ...) \
Log( UALoggerSeverityLevelWarning, category, format, ##__VA_ARGS__ )

#define LogWarning( format, ... ) \
LogWarningCategory( UALoggerCategoryGeneral, format, ##__VA_ARGS__ )

// Error
#define LogErrorCategory( category, format, ...) \
Log( UALoggerSeverityLevelError, category, format, ##__VA_ARGS__ )

#define LogError( format, ... ) \
LogErrorCategory( UALoggerCategoryGeneral, format, ##__VA_ARGS__ )


/**
 *  The shared logger.
 *
 *  @return A shared logger.
 */
+ (Logger *)sharedLogger;

/**
 *  Adds a logger that conforms to Loggable.
 *
 *  @param logger A logger that conforms to Loggable.
 */
- (void)addLogger:(id<Loggable>)logger;

/**
 *  Adds an array of loggers that conform to Loggable.
 *
 *  @param loggers An array of objects that conform to Loggable.
 */
- (void)addLoggers:(NSArray/*<Loggable>*/ *)loggers;

/**
 *  Logs a statement into the shared logger's registered loggers.
 *
 *  @discussion Use this method if you do not want to use the macros defined below.
 *
 *  @param severity     The severity level of the message.
 *  @param category     The category of the message.
 *  @param file         The file in which this message came from.
 *  @param function     The function in which this message came from.
 *  @param lineNumber   The line number at which this message was invoked.
 *  @param formatString A formatted string, following a variadic parameter of arguments.
 */
+ (void)log:(UALoggerSeverityLevel)severity category:(UALoggerCategory)category file:(char *)file function:(const char *)function lineNumber:(int)lineNumber format:(NSString *)formatString, ...;

/**
 *  Logs a statement (with an already-created argument list) into the shared logger's registered loggers.
 *
 *  @discussion Use this method if you do not want to use the macros defined below.
 *
 *  @param severity     The severity level of the message.
 *  @param category     The category of the message.
 *  @param file         The file in which this message came from.
 *  @param function     The function in which this message came from.
 *  @param lineNumber   The line number at which this message was invoked.
 *  @param formatString A format string.
 *  @param argList      A list of C-style arguments.
 */
+ (void)log:(UALoggerSeverityLevel)severity category:(UALoggerCategory)category file:(char *)file function:(const char *)function lineNumber:(int)lineNumber format:(NSString *)formatString args:(va_list)argList;

/**
 *  Logs a statement into the shared logger's registered loggers.
 *
 *  @discussion Use this method if you do not want to use the macros defined below.
 *
 *  @param severity     The severity level of the message.
 *  @param category     The category of the message.
 *  @param file         The file in which this message came from.
 *  @param function     The function in which this message came from.
 *  @param lineNumber   The line number at which this message was invoked.
 *  @param string       A string.
 */
+ (void)log:(UALoggerSeverityLevel)severity category:(UALoggerCategory)category file:(char *)file function:(const char *)function lineNumber:(int)lineNumber string:(NSString *)string;


@end
