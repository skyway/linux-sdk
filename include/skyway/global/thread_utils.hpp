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

namespace skyway{
namespace global {
namespace util {

inline int SetThreadName(const std::string& name) {
    // TODO: Support Unity
#if defined(WEBRTC_ANDROID)
#if __ANDROID_API__ < 24
    // pthread_setname_np() requires Android API 24 or later.
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

}
}
}

#endif //SKYWAY_ANDROID_SDK_THREAD_UTILS_HPP
