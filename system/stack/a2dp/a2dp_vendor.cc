/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Vendor Specific A2DP Codecs Support
 */

#define LOG_TAG "a2dp_vendor"

#include "a2dp_vendor.h"

#include "a2dp_vendor_aptx.h"
#include "a2dp_vendor_aptx_hd.h"
#include "a2dp_vendor_ldac.h"
#include "a2dp_vendor_opus.h"
#include "a2dp_vendor_lhdcv3.h"
#include "a2dp_vendor_lhdcv2.h"
#include "a2dp_vendor_lhdcv3_dec.h"
#include "a2dp_vendor_lhdcv5.h"
#include "stack/include/bt_hdr.h"

bool A2DP_IsVendorSourceCodecValid(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_IsVendorSourceCodecValidAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_IsVendorSourceCodecValidAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_IsVendorSourceCodecValidLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_IsVendorSourceCodecValidOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_IsVendorSourceCodecValidLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_IsVendorSourceCodecValidLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_IsVendorSourceCodecValidLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return false;
}

bool A2DP_IsVendorSinkCodecValid(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id>
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_IsVendorSinkCodecValidLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_IsVendorSinkCodecValidOpus(p_codec_info);
  }

  // Check for Savitech LHDCV3 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_IsVendorSinkCodecValidLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_IsVendorSinkCodecValidLhdcV5(p_codec_info);
  }

  return false;
}

bool A2DP_IsVendorPeerSourceCodecValid(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id>
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_IsVendorPeerSourceCodecValidLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_IsVendorPeerSourceCodecValidOpus(p_codec_info);
  }

  // Check for Savitech LHDCV3 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_IsVendorPeerSourceCodecValidLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_IsVendorPeerSourceCodecValidLhdcV5(p_codec_info);
  }

  return false;
}

bool A2DP_IsVendorPeerSinkCodecValid(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_IsVendorPeerSinkCodecValidAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_IsVendorPeerSinkCodecValidAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_IsVendorPeerSinkCodecValidLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_IsVendorPeerSinkCodecValidOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_IsVendorPeerSinkCodecValidLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_IsVendorPeerSinkCodecValidLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_IsVendorPeerSinkCodecValidLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return false;
}

bool A2DP_IsVendorSinkCodecSupported(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id>
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_IsVendorSinkCodecSupportedLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_IsVendorSinkCodecSupportedOpus(p_codec_info);
  }

  // Check for Savitech LHDCV3 Sink
  else if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_IsVendorSinkCodecSupportedLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5 Sink
  else if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_IsVendorSinkCodecSupportedLhdcV5(p_codec_info);
  }

  return false;
}

bool A2DP_IsVendorPeerSourceCodecSupported(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id> and peer codec capabilities
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_IsPeerSourceCodecSupportedLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_IsPeerSourceCodecSupportedOpus(p_codec_info);
  }

  // Check for Savitech LHDCV3 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_IsPeerSourceCodecSupportedLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_IsPeerSourceCodecSupportedLhdcV5(p_codec_info);
  }

  return false;
}

uint32_t A2DP_VendorCodecGetVendorId(const uint8_t* p_codec_info) {
  const uint8_t* p = &p_codec_info[A2DP_VENDOR_CODEC_VENDOR_ID_START_IDX];

  uint32_t vendor_id = (p[0] & 0x000000ff) | ((p[1] << 8) & 0x0000ff00) |
                       ((p[2] << 16) & 0x00ff0000) |
                       ((p[3] << 24) & 0xff000000);

  return vendor_id;
}

uint16_t A2DP_VendorCodecGetCodecId(const uint8_t* p_codec_info) {
  const uint8_t* p = &p_codec_info[A2DP_VENDOR_CODEC_CODEC_ID_START_IDX];

  uint16_t codec_id = (p[0] & 0x00ff) | ((p[1] << 8) & 0xff00);

  return codec_id;
}

bool A2DP_VendorUsesRtpHeader(bool content_protection_enabled,
                              const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorUsesRtpHeaderAptx(content_protection_enabled,
                                        p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorUsesRtpHeaderAptxHd(content_protection_enabled,
                                          p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorUsesRtpHeaderLdac(content_protection_enabled,
                                        p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorUsesRtpHeaderOpus(content_protection_enabled,
                                        p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorUsesRtpHeaderLhdcV2(content_protection_enabled,
                                          p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorUsesRtpHeaderLhdcV3(content_protection_enabled,
                                          p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorUsesRtpHeaderLhdcV5(content_protection_enabled,
                                          p_codec_info);
  }
  // Add checks based on <content_protection_enabled, vendor_id, codec_id>

  return true;
}

const char* A2DP_VendorCodecName(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecNameAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecNameAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorCodecNameLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorCodecNameOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorCodecNameLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorCodecNameLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorCodecNameLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return "UNKNOWN VENDOR CODEC";
}

bool A2DP_VendorCodecTypeEquals(const uint8_t* p_codec_info_a,
                                const uint8_t* p_codec_info_b) {
  tA2DP_CODEC_TYPE codec_type_a = A2DP_GetCodecType(p_codec_info_a);
  tA2DP_CODEC_TYPE codec_type_b = A2DP_GetCodecType(p_codec_info_b);

  if ((codec_type_a != codec_type_b) ||
      (codec_type_a != A2DP_MEDIA_CT_NON_A2DP)) {
    return false;
  }

  uint32_t vendor_id_a = A2DP_VendorCodecGetVendorId(p_codec_info_a);
  uint16_t codec_id_a = A2DP_VendorCodecGetCodecId(p_codec_info_a);
  uint32_t vendor_id_b = A2DP_VendorCodecGetVendorId(p_codec_info_b);
  uint16_t codec_id_b = A2DP_VendorCodecGetCodecId(p_codec_info_b);

  if (vendor_id_a != vendor_id_b || codec_id_a != codec_id_b) return false;

  // Check for aptX
  if (vendor_id_a == A2DP_APTX_VENDOR_ID &&
      codec_id_a == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecTypeEqualsAptx(p_codec_info_a, p_codec_info_b);
  }

  // Check for aptX-HD
  if (vendor_id_a == A2DP_APTX_HD_VENDOR_ID &&
      codec_id_a == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecTypeEqualsAptxHd(p_codec_info_a, p_codec_info_b);
  }

  // Check for LDAC
  if (vendor_id_a == A2DP_LDAC_VENDOR_ID && codec_id_a == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorCodecTypeEqualsLdac(p_codec_info_a, p_codec_info_b);
  }

  // Check for Opus
  if (vendor_id_a == A2DP_OPUS_VENDOR_ID && codec_id_a == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorCodecTypeEqualsOpus(p_codec_info_a, p_codec_info_b);
  }

    // Check for Savitech LHDCV2
  if (vendor_id_a == A2DP_LHDC_VENDOR_ID && codec_id_a == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorCodecTypeEqualsLhdcV2(p_codec_info_a, p_codec_info_b);
  }

  // Check for Savitech LHDCV3
  if (vendor_id_a == A2DP_LHDC_VENDOR_ID && codec_id_a == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorCodecTypeEqualsLhdcV3(p_codec_info_a, p_codec_info_b);
  }

  // Check for Savitech LHDCV5
  if (vendor_id_a == A2DP_LHDC_VENDOR_ID && codec_id_a == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorCodecTypeEqualsLhdcV5(p_codec_info_a, p_codec_info_b);
  }

  // OPTIONAL: Add extra vendor-specific checks based on the
  // vendor-specific data stored in "p_codec_info_a" and "p_codec_info_b".

  return true;
}

bool A2DP_VendorCodecEquals(const uint8_t* p_codec_info_a,
                            const uint8_t* p_codec_info_b) {
  tA2DP_CODEC_TYPE codec_type_a = A2DP_GetCodecType(p_codec_info_a);
  tA2DP_CODEC_TYPE codec_type_b = A2DP_GetCodecType(p_codec_info_b);

  if ((codec_type_a != codec_type_b) ||
      (codec_type_a != A2DP_MEDIA_CT_NON_A2DP)) {
    return false;
  }

  uint32_t vendor_id_a = A2DP_VendorCodecGetVendorId(p_codec_info_a);
  uint16_t codec_id_a = A2DP_VendorCodecGetCodecId(p_codec_info_a);
  uint32_t vendor_id_b = A2DP_VendorCodecGetVendorId(p_codec_info_b);
  uint16_t codec_id_b = A2DP_VendorCodecGetCodecId(p_codec_info_b);

  if ((vendor_id_a != vendor_id_b) || (codec_id_a != codec_id_b)) return false;

  // Check for aptX
  if (vendor_id_a == A2DP_APTX_VENDOR_ID &&
      codec_id_a == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecEqualsAptx(p_codec_info_a, p_codec_info_b);
  }

  // Check for aptX-HD
  if (vendor_id_a == A2DP_APTX_HD_VENDOR_ID &&
      codec_id_a == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecEqualsAptxHd(p_codec_info_a, p_codec_info_b);
  }

  // Check for LDAC
  if (vendor_id_a == A2DP_LDAC_VENDOR_ID && codec_id_a == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorCodecEqualsLdac(p_codec_info_a, p_codec_info_b);
  }

  // Check for Opus
  if (vendor_id_a == A2DP_OPUS_VENDOR_ID && codec_id_a == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorCodecEqualsOpus(p_codec_info_a, p_codec_info_b);
  }

  // Check for Savitech LHDCV2
  if (vendor_id_a == A2DP_LHDC_VENDOR_ID && codec_id_a == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorCodecEqualsLhdcV2(p_codec_info_a, p_codec_info_b);
  }

  // Check for Savitech LHDCV3
  if (vendor_id_a == A2DP_LHDC_VENDOR_ID && codec_id_a == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorCodecEqualsLhdcV3(p_codec_info_a, p_codec_info_b);
  }

  // Check for Savitech LHDCV5
  if (vendor_id_a == A2DP_LHDC_VENDOR_ID && codec_id_a == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorCodecEqualsLhdcV5(p_codec_info_a, p_codec_info_b);
  }

  // Add extra vendor-specific checks based on the
  // vendor-specific data stored in "p_codec_info_a" and "p_codec_info_b".

  return false;
}

int A2DP_VendorGetBitRate(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetBitRateAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetBitRateAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetBitRateLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetBitRateOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorGetBitRateLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetBitRateLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetBitRateLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return -1;
}

int A2DP_VendorGetTrackSampleRate(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetTrackSampleRateAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetTrackSampleRateAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetTrackSampleRateLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetTrackSampleRateOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorGetTrackSampleRateLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetTrackSampleRateLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetTrackSampleRateLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return -1;
}

int A2DP_VendorGetTrackBitsPerSample(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetTrackBitsPerSampleAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetTrackBitsPerSampleAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetTrackBitsPerSampleLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetTrackBitsPerSampleOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorGetTrackBitsPerSampleLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetTrackBitsPerSampleLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetTrackBitsPerSampleLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return -1;
}

int A2DP_VendorGetTrackChannelCount(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetTrackChannelCountAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetTrackChannelCountAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetTrackChannelCountLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetTrackChannelCountOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorGetTrackChannelCountLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetTrackChannelCountLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetTrackChannelCountLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return -1;
}

int A2DP_VendorGetSinkTrackChannelType(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id>
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetSinkTrackChannelTypeLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetSinkTrackChannelTypeOpus(p_codec_info);
  }

  // Check for Savitech LHDC V3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetSinkTrackChannelTypeLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDC V5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetSinkTrackChannelTypeLhdcV5(p_codec_info);
  }

  return -1;
}

bool A2DP_VendorGetPacketTimestamp(const uint8_t* p_codec_info,
                                   const uint8_t* p_data,
                                   uint32_t* p_timestamp) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetPacketTimestampAptx(p_codec_info, p_data, p_timestamp);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetPacketTimestampAptxHd(p_codec_info, p_data,
                                               p_timestamp);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetPacketTimestampLdac(p_codec_info, p_data, p_timestamp);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetPacketTimestampOpus(p_codec_info, p_data, p_timestamp);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorGetPacketTimestampLhdcV2(p_codec_info, p_data, p_timestamp);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetPacketTimestampLhdcV3(p_codec_info, p_data, p_timestamp);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetPacketTimestampLhdcV5(p_codec_info, p_data, p_timestamp);
  }

  // Add checks based on <vendor_id, codec_id>

  return false;
}

bool A2DP_VendorBuildCodecHeader(const uint8_t* p_codec_info, BT_HDR* p_buf,
                                 uint16_t frames_per_packet) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorBuildCodecHeaderAptx(p_codec_info, p_buf,
                                           frames_per_packet);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorBuildCodecHeaderAptxHd(p_codec_info, p_buf,
                                             frames_per_packet);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorBuildCodecHeaderLdac(p_codec_info, p_buf,
                                           frames_per_packet);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorBuildCodecHeaderOpus(p_codec_info, p_buf,
                                           frames_per_packet);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorBuildCodecHeaderLhdcV2(p_codec_info, p_buf,
                                               frames_per_packet);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorBuildCodecHeaderLhdcV3(p_codec_info, p_buf,
                                               frames_per_packet);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorBuildCodecHeaderLhdcV5(p_codec_info, p_buf,
                                               frames_per_packet);
  }

  // Add checks based on <vendor_id, codec_id>

  return false;
}

const tA2DP_ENCODER_INTERFACE* A2DP_VendorGetEncoderInterface(
    const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetEncoderInterfaceAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorGetEncoderInterfaceAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetEncoderInterfaceLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetEncoderInterfaceOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorGetEncoderInterfaceLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetEncoderInterfaceLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetEncoderInterfaceLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return NULL;
}

const tA2DP_DECODER_INTERFACE* A2DP_VendorGetDecoderInterface(
    const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id>
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorGetDecoderInterfaceLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorGetDecoderInterfaceOpus(p_codec_info);
  }

  // Check for Savitech LHDCV3 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorGetDecoderInterfaceLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5 Sink
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorGetDecoderInterfaceLhdcV5(p_codec_info);
  }

  return NULL;
}

bool A2DP_VendorAdjustCodec(uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorAdjustCodecAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorAdjustCodecAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorAdjustCodecLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorAdjustCodecOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorAdjustCodecLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorAdjustCodecLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorAdjustCodecLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return false;
}

btav_a2dp_codec_index_t A2DP_VendorSourceCodecIndex(
    const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorSourceCodecIndexAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorSourceCodecIndexAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorSourceCodecIndexLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorSourceCodecIndexOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorSourceCodecIndexLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorSourceCodecIndexLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorSourceCodecIndexLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return BTAV_A2DP_CODEC_INDEX_MAX;
}

btav_a2dp_codec_index_t A2DP_VendorSinkCodecIndex(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Add checks based on <vendor_id, codec_id>
  // NOTE: Should be done only for local Sink codecs.

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorSinkCodecIndexLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorSinkCodecIndexOpus(p_codec_info);
  }

  // Check for Savitech LHDC V3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorSinkCodecIndexLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDC V5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorSinkCodecIndexLhdcV5(p_codec_info);
  }

  return BTAV_A2DP_CODEC_INDEX_MAX;
}

const char* A2DP_VendorCodecIndexStr(btav_a2dp_codec_index_t codec_index) {
  // Add checks based on codec_index
  switch (codec_index) {
    case BTAV_A2DP_CODEC_INDEX_SOURCE_SBC:
    case BTAV_A2DP_CODEC_INDEX_SINK_SBC:
    case BTAV_A2DP_CODEC_INDEX_SOURCE_AAC:
    case BTAV_A2DP_CODEC_INDEX_SINK_AAC:
      break;  // These are not vendor-specific codecs
    case BTAV_A2DP_CODEC_INDEX_SOURCE_APTX:
      return A2DP_VendorCodecIndexStrAptx();
    case BTAV_A2DP_CODEC_INDEX_SOURCE_APTX_HD:
      return A2DP_VendorCodecIndexStrAptxHd();
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LDAC:
      return A2DP_VendorCodecIndexStrLdac();
    case BTAV_A2DP_CODEC_INDEX_SINK_LDAC:
      return A2DP_VendorCodecIndexStrLdacSink();
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LC3:
      return "LC3 not implemented";
    case BTAV_A2DP_CODEC_INDEX_SOURCE_OPUS:
      return A2DP_VendorCodecIndexStrOpus();
    case BTAV_A2DP_CODEC_INDEX_SINK_OPUS:
      return A2DP_VendorCodecIndexStrOpusSink();
    // Savitech Patch - START
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LHDCV2:
      return A2DP_VendorCodecIndexStrLhdcV2();
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LHDCV3:
      return A2DP_VendorCodecIndexStrLhdcV3();
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LHDCV5:
      return A2DP_VendorCodecIndexStrLhdcV5();
    case BTAV_A2DP_CODEC_INDEX_SINK_LHDCV3:
      return A2DP_VendorCodecIndexStrLhdcV3Sink();
    case BTAV_A2DP_CODEC_INDEX_SINK_LHDCV5:
      return A2DP_VendorCodecIndexStrLhdcV5Sink();
    // Savitech Patch - END
    // Add a switch statement for each vendor-specific codec
    case BTAV_A2DP_CODEC_INDEX_MAX:
      break;
  }

  return "UNKNOWN CODEC INDEX";
}

bool A2DP_VendorInitCodecConfig(btav_a2dp_codec_index_t codec_index,
                                AvdtpSepConfig* p_cfg) {
  // Add checks based on codec_index
  switch (codec_index) {
    case BTAV_A2DP_CODEC_INDEX_SOURCE_SBC:
    case BTAV_A2DP_CODEC_INDEX_SINK_SBC:
    case BTAV_A2DP_CODEC_INDEX_SOURCE_AAC:
    case BTAV_A2DP_CODEC_INDEX_SINK_AAC:
      break;  // These are not vendor-specific codecs
    case BTAV_A2DP_CODEC_INDEX_SOURCE_APTX:
      return A2DP_VendorInitCodecConfigAptx(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SOURCE_APTX_HD:
      return A2DP_VendorInitCodecConfigAptxHd(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LDAC:
      return A2DP_VendorInitCodecConfigLdac(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SINK_LDAC:
      return A2DP_VendorInitCodecConfigLdacSink(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LC3:
      break;  // not implemented
    case BTAV_A2DP_CODEC_INDEX_SOURCE_OPUS:
      return A2DP_VendorInitCodecConfigOpus(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SINK_OPUS:
      return A2DP_VendorInitCodecConfigOpusSink(p_cfg);
    // Savitech Patch - START
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LHDCV2:
      return A2DP_VendorInitCodecConfigLhdcV2(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LHDCV3:
      return A2DP_VendorInitCodecConfigLhdcV3(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SOURCE_LHDCV5:
      return A2DP_VendorInitCodecConfigLhdcV5(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SINK_LHDCV3:
      return A2DP_VendorInitCodecConfigLhdcV3Sink(p_cfg);
    case BTAV_A2DP_CODEC_INDEX_SINK_LHDCV5:
      return A2DP_VendorInitCodecConfigLhdcV5Sink(p_cfg);
    // Savitech Patch - END
    // Add a switch statement for each vendor-specific codec
    case BTAV_A2DP_CODEC_INDEX_MAX:
      break;
  }

  return false;
}

std::string A2DP_VendorCodecInfoString(const uint8_t* p_codec_info) {
  uint32_t vendor_id = A2DP_VendorCodecGetVendorId(p_codec_info);
  uint16_t codec_id = A2DP_VendorCodecGetCodecId(p_codec_info);

  // Check for aptX
  if (vendor_id == A2DP_APTX_VENDOR_ID &&
      codec_id == A2DP_APTX_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecInfoStringAptx(p_codec_info);
  }

  // Check for aptX-HD
  if (vendor_id == A2DP_APTX_HD_VENDOR_ID &&
      codec_id == A2DP_APTX_HD_CODEC_ID_BLUETOOTH) {
    return A2DP_VendorCodecInfoStringAptxHd(p_codec_info);
  }

  // Check for LDAC
  if (vendor_id == A2DP_LDAC_VENDOR_ID && codec_id == A2DP_LDAC_CODEC_ID) {
    return A2DP_VendorCodecInfoStringLdac(p_codec_info);
  }

  // Check for Opus
  if (vendor_id == A2DP_OPUS_VENDOR_ID && codec_id == A2DP_OPUS_CODEC_ID) {
    return A2DP_VendorCodecInfoStringOpus(p_codec_info);
  }

  // Check for Savitech LHDCV2
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV2_CODEC_ID) {
    return A2DP_VendorCodecInfoStringLhdcV2(p_codec_info);
  }

  // Check for Savitech LHDCV3
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV3_CODEC_ID) {
    return A2DP_VendorCodecInfoStringLhdcV3(p_codec_info);
  }

  // Check for Savitech LHDCV5
  if (vendor_id == A2DP_LHDC_VENDOR_ID && codec_id == A2DP_LHDCV5_CODEC_ID) {
    return A2DP_VendorCodecInfoStringLhdcV5(p_codec_info);
  }

  // Add checks based on <vendor_id, codec_id>

  return "Unsupported codec vendor_id: " + loghex(vendor_id) +
         " codec_id: " + loghex(codec_id);
}
