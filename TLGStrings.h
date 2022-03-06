
#pragma once

#define TVPDataFlagMustBeZero TJS_W("Data flag must be 0 (any flags are not yet supported)")
#define TVPInvalidTlgHeaderOrVersion TJS_W("Invalid TLG header or unsupported TLG version.")
#define TVPTLGLoadError TJS_W("TLG Read Error /%1")
#define TVPTlgMalformedTagMissionColonAfterNameLength TJS_W("Malformed TLG SDS tag structure, missing colon after name length")
#define TVPTlgMalformedTagMissionColonAfterVaueLength TJS_W("Malformed TLG SDS tag structure, missing colon after value length")
#define TVPTlgMalformedTagMissionCommaAfterTag TJS_W("Malformed TLG SDS tag structure, missing comma after a tag")
#define TVPTlgMalformedTagMissionEqualsAfterName TJS_W("Malformed TLG SDS tag structure, missing equals after name")
#define TVPTlgUnsupportedUniversalTransitionRule TJS_W("TLG cannot be used as universal transition rule, province(_p) or mask(_m) images.")
#define TVPUnsupportedColorCount TJS_W("Unsupported color count : ")
#define TVPUnsupportedColorType TJS_W("Unsupported color type")
#define TVPUnsupportedColorTypeColon TJS_W("Unsupported color type : ")
#define TVPUnsupportedEntropyCodingMethod TJS_W("Unsupported entropy coding method")
#define TVPUnsupportedExternalGolombBitLengthTable TJS_W("External golomb bit length table is not yet supported.")
#define TVPTlgInsufficientMemory TJS_W("SaveTLG6: Insufficient memory")
#define TVPTlgTooLargeBitLength TJS_W("SaveTLG6: Too large bit length (given image may be too large)")
