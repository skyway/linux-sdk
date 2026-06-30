//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ANDROID_SDK_THREAD_UTILS_HPP
#define SKYWAY_ANDROID_SDK_THREAD_UTILS_HPP

#ifdef WEBRTC_ANDROID
#include <sys/prctl.h>
#endif

#if defined(WEBRTC_IOS) || defined(WEBRTC_LINUX)
#include <pthread.h>
#endif
#include <string>

namespace skyway {
namespace global {
namespace util {

inline int SetThreadName(const std::string& name) {
#if defined(WEBRTC_ANDROID)
#if __ANDROID_API__ < 24

    return prctl(PR_SET_NAME, name.c_str());
#else
    return pthread_setname_np(pthread_self(), name.c_str());
#endif

#elif defined(WEBRTC_IOS)
    return pthread_setname_np(name.c_str());
#elif defined(WEBRTC_LINUX)
    return pthread_setname_np(pthread_self(), name.c_str());
#endif
    return 0;
}

}  // namespace util
}  // namespace global
}  // namespace skyway

#endif
