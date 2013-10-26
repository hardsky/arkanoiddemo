#ifndef HSG_LOG_H_
#define HSG_LOG_H_

namespace hsg {

class Log {
public:
    static void error(const char* pMessage, ...);
    static void warn(const char* pMessage, ...);
    static void info(const char* pMessage, ...);
    static void debug(const char* pMessage, ...);
};
} /* namespace hsg */

#ifndef NDEBUG
#define HSG_DEBUG(...) hsg::Log::debug(__VA_ARGS__)
#else
#define HSG_DEBUG(...)
#endif

#define HSG_ERROR(...) hsg::Log::error(__VA_ARGS__)
#define HSG_WARN(...) hsg::Log::warn(__VA_ARGS__)
#define HSG_INFO(...) hsg::Log::info(__VA_ARGS__)

#endif /* LOG_H_ */
