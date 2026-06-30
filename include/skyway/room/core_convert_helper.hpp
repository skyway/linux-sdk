//
// © NTT DOCOMO BUSINESS, Inc. All Rights Reserved.
//

#ifndef SKYWAY_ROOM_CORE_CONVERT_HELPER_HPP_
#define SKYWAY_ROOM_CORE_CONVERT_HELPER_HPP_

#include <vector>

#include <skyway/core/connection_state.hpp>
#include <skyway/domain/domain.hpp>
#include <skyway/model/domain.hpp>

#include "skyway/room/types.hpp"

namespace skyway {
namespace room {
namespace core_convert_helper {

/// @cond INTERNAL_SECTION
domain::ContentType ConvertToPlatformContentType(model::ContentType type);
ConnectionState ConvertToPlatformConnectionState(core::ConnectionState state);
WebRTCStatsReport ConvertToPlatformWebRTCStatsReport(const model::WebRTCStatsReport& core_report);
WebRTCStats ConvertToPlatformWebRTCStats(const model::WebRTCStats& core_stats);
Codec ConvertToPlatformCodec(const model::Codec& core_codec);
std::vector<Codec> ConvertToPlatformCodecs(const std::vector<model::Codec>& core_codecs);
Encoding ConvertToPlatformEncoding(const model::Encoding& core_encoding);
std::vector<Encoding> ConvertToPlatformEncodings(
    const std::vector<model::Encoding>& core_encodings);
model::Codec ConvertToCoreCodec(const Codec& codec);
std::vector<model::Codec> ConvertToCoreCodecs(const std::vector<Codec>& codecs);
model::Encoding ConvertToCoreEncoding(const Encoding& encoding);
std::vector<model::Encoding> ConvertToCoreEncodings(const std::vector<Encoding>& encodings);
/// @endcond

}  // namespace core_convert_helper
}  // namespace room
}  // namespace skyway

#endif /* SKYWAY_ROOM_CORE_CONVERT_HELPER_HPP_ */
