/////////////////////////////////////////////////////////////////////////////
//
// test.cpp : Implementation of CTest
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test.h"
#include "CPropertyDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTest::CTest
// Constructor
CTest::CTest() :
m_hwndParent(NULL),
m_clrForeground(0x0000FF),
m_nPreset(0) {
    wcsncpy_s(m_wszPluginText, sizeof(m_wszPluginText) / sizeof(m_wszPluginText[0]), 
		L"Test Plugin", sizeof(m_wszPluginText) / sizeof(m_wszPluginText[0]));
    m_dwAdviseCookie = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CTest::~CTest
// Destructor
CTest::~CTest() { }

/////////////////////////////////////////////////////////////////////////////
// CTest:::FinalConstruct
// Called when an effect is first loaded. Use this function to do one-time
// intializations that could fail (i.e. creating offscreen buffers) instead
// of doing this in the constructor, which cannot return an error.
HRESULT CTest::FinalConstruct() { return S_OK; }

/////////////////////////////////////////////////////////////////////////////
// CTest:::FinalRelease
// Called when an effect is unloaded. Use this function to free any
// resources allocated in FinalConstruct.
void CTest::FinalRelease() { ReleaseCore(); }


//////////////////////////////////////////////////////////////////////////////
// CTest::Render
// Called when an effect should render itself to the screen.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::Render(TimedLevel *pLevels, HDC hdc, RECT *prc) {
	/*{
    // Fill background with black
    HBRUSH hNewBrush = ::CreateSolidBrush( 0 );
    HPEN hNewPen = ::CreatePen( PS_SOLID, 0, m_clrForeground );
    HPEN hOldPen= static_cast<HPEN>(::SelectObject( hdc, hNewPen ));

    ::FillRect( hdc, prc, hNewBrush );
    
    // draw using the current preset
    switch (m_nPreset){
		case PRESET_BARS: // Walk through the frequencies until we run out of levels or drawing surface.
            for (int x = prc->left; x < prc->right && x < (SA_BUFFER_SIZE-1); ++x) {
                int y = static_cast<int>(((prc->bottom - prc->top)/256.0f) * pLevels->frequency[0][x - (prc->left - 1)]);
                ::MoveToEx( hdc, x, prc->bottom, NULL );  
                ::LineTo(hdc, x, prc->bottom - y); 
            }
        break;

		case PRESET_SCOPE: // Walk through the waveform data until we run out of samples or drawing surface.
            int y = static_cast<int>(((prc->bottom - prc->top)/256.0f) * pLevels->waveform[0][0]);
            ::MoveToEx( hdc, prc->left, y, NULL );  
            for (int x = prc->left; x < prc->right && x < (SA_BUFFER_SIZE-1); ++x) {
                y = static_cast<int>(((prc->bottom - prc->top)/256.0f) * pLevels->waveform[0][x - (prc->left - 1)]);
                ::LineTo(hdc, x, y); 
            }
        break;

		case PRESET_BLANK:
			//int y = static_cast<int>(((prc->bottom - prc->top)/256.0f) * pLevels->waveform[0][0]);
		break;
    }
        
    if (hNewBrush) { ::DeleteObject( hNewBrush ); }

    if (hNewPen) {
        ::SelectObject( hdc, hOldPen );
        ::DeleteObject( hNewPen );
    }
	}*/
    
	COLORREF mycolour;
    //int mylevel = pLevels->waveform[0][0];
    int mylevel = pLevels->frequency[0][1]; // [20 Hz, 22,050 Hz] => Total Range = 22,030 -> [0-255] (Sampled) || STEP SIZE = ??? || SA_BUFFER_SIZE = 1024 by default
	::UINT32 colhex;

    switch (m_nPreset) {
		// #9C2113
		case PRESET_RED: { colhex = 0x9C2113; }
        break;
		
		// #099078
		case PRESET_GREEN: { colhex = 0x099078; }
        break;
		
		// #014B43
		case PRESET_BLUE: { colhex = 0x014B43; }
        break;
    }

	mycolour = RGB(mylevel * (colhex >> 16)/0xFF, mylevel * ((colhex >> 8)&0xFF)/0xFF, mylevel * (colhex&0xFF)/0xFF);

    HBRUSH hNewBrush = ::CreateSolidBrush( mycolour );
    ::FillRect( hdc, prc, hNewBrush );

	// Destroy Resources such as Pens and Brushes
    if (hNewBrush) { ::DeleteObject( hNewBrush ); }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::MediaInfo
// Everytime new media is loaded, this method is called to pass the
// number of channels (mono/stereo), the sample rate of the media, and the
// title of the media
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::MediaInfo(LONG lChannelCount, LONG lSampleRate, BSTR bstrTitle ) { return S_OK; }


//////////////////////////////////////////////////////////////////////////////
// CTest::GetCapabilities
// Returns the capabilities of this effect. Flags that can be returned are:
//  EFFECT_CANGOFULLSCREEN      -- effect supports full-screen rendering
//  EFFECT_HASPROPERTYPAGE      -- effect supports a property page
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::GetCapabilities(DWORD * pdwCapabilities)
{
    if (NULL == pdwCapabilities)
    {
        return E_POINTER;
    }

    *pdwCapabilities = EFFECT_HASPROPERTYPAGE;
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::DisplayPropertyPage
// Invoked when a host wants to display the property page for the effect
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::DisplayPropertyPage(HWND hwndOwner)
{
    CPropertyDialog dialog(this);

    dialog.DoModal(hwndOwner);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::GetTitle
// Invoked when a host wants to obtain the title of the effect
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::GetTitle(BSTR* bstrTitle)
{
    if (NULL == bstrTitle)
    {
        return E_POINTER;
    }

    CComBSTR bstrTemp;
    bstrTemp.LoadString(IDS_EFFECTNAME); 
        
    if ((!bstrTemp) || (0 == bstrTemp.Length()))
    {
        return E_FAIL;
    }

    *bstrTitle = bstrTemp.Detach();

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::GetPresetTitle
// Invoked when a host wants to obtain the title of the given preset
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::GetPresetTitle(LONG nPreset, BSTR *bstrPresetTitle)
{
    if (NULL == bstrPresetTitle)
    {
        return E_POINTER;
    }

    if ((nPreset < 0) || (nPreset >= PRESET_COUNT))
    {
        return E_INVALIDARG;
    }

    CComBSTR bstrTemp;
    
	/*
    switch (nPreset)
    {
    case PRESET_BARS:
        bstrTemp.LoadString(IDS_BARSPRESETNAME); 
        break;

    case PRESET_SCOPE:
        bstrTemp.LoadString(IDS_SCOPEPRESETNAME); 
        break;
    } */

	switch (nPreset)
    {
    case PRESET_RED:
        bstrTemp.LoadString(IDS_REDPRESETNAME); 
        break;

    case PRESET_GREEN:
        bstrTemp.LoadString(IDS_GREENPRESETNAME); 
        break;

    case PRESET_BLUE:
        bstrTemp.LoadString(IDS_BLUEPRESETNAME); 
        break;
    }
    
    if ((!bstrTemp) || (0 == bstrTemp.Length()))
    {
        return E_FAIL;
    }

    *bstrPresetTitle = bstrTemp.Detach();

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::GetPresetCount
// Invoked when a host wants to obtain the number of supported presets
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::GetPresetCount(LONG *pnPresetCount) {
    if (NULL == pnPresetCount) { return E_POINTER; }
    *pnPresetCount = PRESET_COUNT;

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::SetCurrentPreset
// Invoked when a host wants to change the index of the current preset
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::SetCurrentPreset(LONG nPreset){
    if ((nPreset < 0) || (nPreset >= PRESET_COUNT)) { return E_INVALIDARG; }
    m_nPreset = nPreset;

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::GetCurrentPreset
// Invoked when a host wants to obtain the index of the current preset
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::GetCurrentPreset(LONG *pnPreset) {
    if (NULL == pnPreset){ return E_POINTER; }
    *pnPreset = m_nPreset;

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::SetCore
// Set WMP core interface
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::SetCore(IWMPCore * pCore) {
    HRESULT hr = S_OK;

    // release any existing WMP core interfaces
    ReleaseCore();

    // If we get passed a NULL core, this  means
    // that the plugin is being shutdown.

    if (pCore == NULL)
    {
        return S_OK;
    }

    m_spCore = pCore;

    // connect up the event interface
    CComPtr<IConnectionPointContainer>  spConnectionContainer;

    hr = m_spCore->QueryInterface( &spConnectionContainer );

    if (SUCCEEDED(hr))
    {
        hr = spConnectionContainer->FindConnectionPoint( __uuidof(IWMPEvents), &m_spConnectionPoint );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_spConnectionPoint->Advise( GetUnknown(), &m_dwAdviseCookie );

        if ((FAILED(hr)) || (0 == m_dwAdviseCookie))
        {
            m_spConnectionPoint = NULL;
        }
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::Create
// Invoked when the visualization should be initialized.
//
// If hwndParent != NULL, RenderWindowed() will be called and the visualization
// should draw into the window specified by hwndParent. This will be the
// behavior when the visualization is hosted in a window.
//
// If hwndParent == NULL, Render() will be called and the visualization
// should draw into the DC passed to Render(). This will be the behavior when
// the visualization is hosted windowless (like in a skin for example).
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::Create(HWND hwndParent) {
    m_hwndParent = hwndParent;
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::Destroy
// Invoked when the visualization should be released.
//
// Any resources allocated for rendering should be released.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::Destroy() {
    m_hwndParent = NULL;
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::NotifyNewMedia
// Invoked when a new media stream begins playing.
//
// The visualization can inspect this object for properties (like name or artist)
// that might be interesting for visualization.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::NotifyNewMedia(IWMPMedia *pMedia) { return S_OK; }

//////////////////////////////////////////////////////////////////////////////
// CTest::OnWindowMessage
// Window messages sent to the parent window.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::OnWindowMessage(UINT msg, WPARAM WParam, LPARAM LParam, LRESULT *plResultParam ) {
    // return S_OK only if the plugin has handled the window message
    // return S_FALSE to let the defWindowProc handle the message
    return S_FALSE;
}

//////////////////////////////////////////////////////////////////////////////
// CTest::RenderWindowed
// Called when an effect should render itself to the screen.
//
// The fRequiredRender flag specifies if an update is required, otherwise the
// update is optional. This allows visualizations that are fairly static (for example,
// album art visualizations) to only render when the parent window requires it,
// instead of n times a second for dynamic visualizations.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::RenderWindowed(TimedLevel *pLevels, BOOL fRequiredRender ){
    // NULL parent window should not happen 
    if (NULL == m_hwndParent){ return E_UNEXPECTED; }

    // At this point the visualization should draw directly into the parent
    // window. This sample just calls windowless render for simplicity.
    HDC hdc = ::GetDC(m_hwndParent);
    if (NULL == hdc){ return E_FAIL; }

    RECT rParent = { 0 };
    ::GetClientRect(m_hwndParent, &rParent);

    Render(pLevels, hdc, &rParent);
    
    ::ReleaseDC(m_hwndParent, hdc);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTest::ReleaseCore
// Release WMP core interfaces
//////////////////////////////////////////////////////////////////////////////
void CTest::ReleaseCore()
{
    if (m_spConnectionPoint)
    {
        if (0 != m_dwAdviseCookie)
        {
            m_spConnectionPoint->Unadvise(m_dwAdviseCookie);
            m_dwAdviseCookie = 0;
        }
        m_spConnectionPoint = NULL;
    }

    if (m_spCore)
    {
        m_spCore = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////////
// CTest::get_foregroundColor
// Property get to retrieve the foregroundColor prop via the public interface.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::get_foregroundColor(BSTR *pVal){
    return ColorToWz( pVal, m_clrForeground);
}


//////////////////////////////////////////////////////////////////////////////
// CTest::put_foregroundColor
// Property put to set the foregroundColor prop via the public interface.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTest::put_foregroundColor(BSTR newVal) {
    return WzToColor(newVal, &m_clrForeground);
}


//////////////////////////////////////////////////////////////////////////////
// CTest::WzToColor
// Helper function used to convert a string into a COLORREF.
//////////////////////////////////////////////////////////////////////////////
HRESULT CTest::WzToColor(const WCHAR *pwszColor, COLORREF *pcrColor){ 
    if (NULL == pwszColor)
    {
        //NULL color string passed in
        return E_POINTER;
    }

    if (0 == lstrlenW(pwszColor))
    {
        //Empty color string passed in
        return E_INVALIDARG;
    }

    if (NULL == pcrColor)
    {
        //NULL output color DWORD passed in
        return E_POINTER;
    }
    
    if (lstrlenW(pwszColor) != 7)
    {
        //hex color string is not of the correct length
        return E_INVALIDARG;
    }

    DWORD dwRet = 0;
    for (int i = 1; i < 7; i++)
    {
        // shift dwRet by 4
        dwRet <<= 4;
        // and add in the value of this string

        if ((pwszColor[i] >= L'0') && (pwszColor[i] <= L'9'))
        {
            dwRet += pwszColor[i] - '0';
        }
        else if ((pwszColor[i] >= L'A') && (pwszColor[i] <= L'F'))
        {
            dwRet += 10 + (pwszColor[i] - L'A');
        }
        else if ((pwszColor[i] >= L'a') && (pwszColor[i] <= L'f'))
        {
            dwRet += 10 + (pwszColor[i] - L'a');
        }
        else
        {
           //Invalid hex digit in color string
            return E_INVALIDARG;
        }
    }

    *pcrColor = SwapBytes(dwRet);

    return S_OK;
} 


//////////////////////////////////////////////////////////////////////////////
// CTest::ColorToWz
// Helper function used to convert a COLORREF to a BSTR.
//////////////////////////////////////////////////////////////////////////////
HRESULT CTest::ColorToWz( BSTR* pbstrColor, COLORREF crColor) {
    _ASSERT( NULL != pbstrColor );
    _ASSERT( (crColor & 0x00FFFFFF) == crColor );

    *pbstrColor = NULL;

    WCHAR wsz[8];
    HRESULT hr  = S_OK;

    swprintf_s( wsz, sizeof(wsz)/sizeof(wsz[0]), L"#%06X", SwapBytes(crColor) );
    
    *pbstrColor = ::SysAllocString( wsz );

    if (!pbstrColor) {
        hr = E_FAIL;
    }

    return hr;
}


//////////////////////////////////////////////////////////////////////////////
// CTest::SwapBytes
// Used to convert between a DWORD and COLORREF.  Simply swaps the lowest 
// and 3rd order bytes.
//////////////////////////////////////////////////////////////////////////////
inline DWORD CTest::SwapBytes(DWORD dwRet) {
    return ((dwRet & 0x0000FF00) | ((dwRet & 0x00FF0000) >> 16) | ((dwRet & 0x000000FF) << 16));
}

