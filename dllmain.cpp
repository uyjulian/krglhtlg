
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <objidl.h>
#include "tp_stub.h"
#include "tvpgl.h"
#include "TVPBinaryStreamShim.h"
#include "LayerBitmapIntf.h"
#define EXPORT(hr) extern "C" __declspec(dllexport) hr __stdcall

extern void TVPLoadTLG(void* formatdata, void *callbackdata, tTVPGraphicSizeCallback sizecallback,
	tTVPGraphicScanLineCallback scanlinecallback, tTVPMetaInfoPushCallback metainfopushcallback,
	tTJSBinaryStream *src, tjs_int keyidx, tTVPGraphicLoadMode mode);

void TVPLoadTLGForPlugin(void* formatdata, void *callbackdata, tTVPGraphicSizeCallback sizecallback,
	tTVPGraphicScanLineCallback scanlinecallback, tTVPMetaInfoPushCallback metainfopushcallback,
	IStream *isrc, tjs_int keyidx, tTVPGraphicLoadMode mode)
{
	tTJSBinaryStream src(isrc);
	TVPLoadTLG(formatdata, callbackdata, sizecallback, scanlinecallback, metainfopushcallback, &src, keyidx, mode);
}

extern void TVPLoadHeaderTLG(void* formatdata, tTJSBinaryStream *src, iTJSDispatch2** dic );
void TVPLoadHeaderTLGForPlugin(void* formatdata, IStream *isrc, iTJSDispatch2** dic)
{
	tTJSBinaryStream src(isrc);
	TVPLoadHeaderTLG(formatdata, &src, dic);
}

extern void TVPSaveAsTLG(void* formatdata, tTJSBinaryStream* dst, const tTVPBaseBitmap* image, const ttstr & mode, iTJSDispatch2* meta );

void TVPSaveAsTLGForPlugin(void* formatdata, void* callbackdata, IStream* idst, const ttstr & mode, tjs_uint width, tjs_uint height, tTVPGraphicSaveScanLineCallback scanlinecallback, iTJSDispatch2* meta )
{
	tTJSBinaryStream dst(idst);
	tTVPBaseBitmap bmp(width, height, callbackdata, scanlinecallback);
	TVPSaveAsTLG(formatdata, &dst, &bmp, mode, meta);
}

extern bool TVPAcceptSaveAsTLG(void* formatdata, const ttstr & type, class iTJSDispatch2** dic);

BOOLEAN WINAPI DllMain(HMODULE hDllHandle, DWORD nReason, LPVOID lpReserved)
{
	switch (nReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hDllHandle);
			break;
		}
	}

	return TRUE;
}

static tjs_int GlobalRefCountAtInit = 0;
EXPORT(HRESULT) V2Link(iTVPFunctionExporter *exporter)
{
	TVPInitImportStub(exporter);
	TVPTLG6InitLeadingZeroTable();
	TVPTLG6InitGolombTable();

	TVPRegisterGraphicLoadingHandler( ttstr(TJS_W(".tlg")), TVPLoadTLGForPlugin, TVPLoadHeaderTLGForPlugin, TVPSaveAsTLGForPlugin, TVPAcceptSaveAsTLG, NULL );
	TVPRegisterGraphicLoadingHandler( ttstr(TJS_W(".tlg5")), TVPLoadTLGForPlugin, TVPLoadHeaderTLGForPlugin, TVPSaveAsTLGForPlugin, TVPAcceptSaveAsTLG, NULL );
	TVPRegisterGraphicLoadingHandler( ttstr(TJS_W(".tlg6")), TVPLoadTLGForPlugin, TVPLoadHeaderTLGForPlugin, TVPSaveAsTLGForPlugin, TVPAcceptSaveAsTLG, NULL );

	GlobalRefCountAtInit = TVPPluginGlobalRefCount;
	return S_OK;
}

EXPORT(HRESULT) V2Unlink() {
	if(TVPPluginGlobalRefCount > GlobalRefCountAtInit) return E_FAIL;

	TVPUnregisterGraphicLoadingHandler( ttstr(TJS_W(".tlg")), TVPLoadTLGForPlugin, TVPLoadHeaderTLGForPlugin, TVPSaveAsTLGForPlugin, TVPAcceptSaveAsTLG, NULL );
	TVPUnregisterGraphicLoadingHandler( ttstr(TJS_W(".tlg5")), TVPLoadTLGForPlugin, TVPLoadHeaderTLGForPlugin, TVPSaveAsTLGForPlugin, TVPAcceptSaveAsTLG, NULL );
	TVPUnregisterGraphicLoadingHandler( ttstr(TJS_W(".tlg6")), TVPLoadTLGForPlugin, TVPLoadHeaderTLGForPlugin, TVPSaveAsTLGForPlugin, TVPAcceptSaveAsTLG, NULL );

	TVPUninitImportStub();
	return S_OK;
}
