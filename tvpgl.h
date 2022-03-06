
#pragma once

#define TVPFillARGB TVPFillARGB_c
#define TVPTLG5ComposeColors3To4 TVPTLG5ComposeColors3To4_c
#define TVPTLG5ComposeColors4To4 TVPTLG5ComposeColors4To4_c
#define TVPTLG5DecompressSlide TVPTLG5DecompressSlide_c
#define TVPTLG6DecodeGolombValuesForFirst TVPTLG6DecodeGolombValuesForFirst_c
#define TVPTLG6DecodeGolombValues TVPTLG6DecodeGolombValues_c
#define TVPTLG6DecodeLineGeneric TVPTLG6DecodeLineGeneric_c
#define TVPTLG6DecodeLine TVPTLG6DecodeLine_c

#define TVP_TLG6_H_BLOCK_SIZE 8
#define TVP_TLG6_W_BLOCK_SIZE 8

#define TVP_TLG6_GOLOMB_N_COUNT  4
extern char TVPTLG6GolombBitLengthTable[TVP_TLG6_GOLOMB_N_COUNT*2*128][TVP_TLG6_GOLOMB_N_COUNT];

extern void TVPTLG6InitLeadingZeroTable();
extern void TVPTLG6InitGolombTable();
extern void TVPFillARGB(tjs_uint32 *dest, tjs_int len, tjs_uint32 value);
extern void TVPTLG5ComposeColors3To4(tjs_uint8 *outp, const tjs_uint8 *upper, tjs_uint8 * const * buf, tjs_int width);
extern void TVPTLG5ComposeColors4To4(tjs_uint8 *outp, const tjs_uint8 *upper, tjs_uint8 * const* buf, tjs_int width);
extern tjs_int TVPTLG5DecompressSlide(tjs_uint8 *out, const tjs_uint8 *in, tjs_int insize, tjs_uint8 *text, tjs_int initialr);
extern void TVPTLG6DecodeGolombValuesForFirst(tjs_int8 *pixelbuf, tjs_int pixel_count, tjs_uint8 *bit_pool);
extern void TVPTLG6DecodeGolombValues(tjs_int8 *pixelbuf, tjs_int pixel_count, tjs_uint8 *bit_pool);
extern void TVPTLG6DecodeLineGeneric(tjs_uint32 *prevline, tjs_uint32 *curline, tjs_int width, tjs_int start_block, tjs_int block_limit, tjs_uint8 *filtertypes, tjs_int skipblockbytes, tjs_uint32 *in, tjs_uint32 initialp, tjs_int oddskip, tjs_int dir);
extern void TVPTLG6DecodeLine(tjs_uint32 *prevline, tjs_uint32 *curline, tjs_int width, tjs_int block_count, tjs_uint8 *filtertypes, tjs_int skipblockbytes, tjs_uint32 *in, tjs_uint32 initialp, tjs_int oddskip, tjs_int dir);
