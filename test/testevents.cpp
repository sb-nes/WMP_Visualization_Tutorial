/////////////////////////////////////////////////////////////////////////////
//
// testEvents.cpp : Implementation of CTest events
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test.h"

void CTest::OpenStateChange( long NewState )
{
    switch (NewState)
    {
    case wmposUndefined:
        break;
    case wmposPlaylistChanging:
        break;
    case wmposPlaylistLocating:
        break;
    case wmposPlaylistConnecting:
        break;
    case wmposPlaylistLoading:
        break;
    case wmposPlaylistOpening:
        break;
    case wmposPlaylistOpenNoMedia:
        break;
    case wmposPlaylistChanged:
        break;
    case wmposMediaChanging:
        break;
    case wmposMediaLocating:
        break;
    case wmposMediaConnecting:
        break;
    case wmposMediaLoading:
        break;
    case wmposMediaOpening:
        break;
    case wmposMediaOpen:
        break;
    case wmposBeginCodecAcquisition:
        break;
    case wmposEndCodecAcquisition:
        break;
    case wmposBeginLicenseAcquisition:
        break;
    case wmposEndLicenseAcquisition:
        break;
    case wmposBeginIndividualization:
        break;
    case wmposEndIndividualization:
        break;
    case wmposMediaWaiting:
        break;
    case wmposOpeningUnknownURL:
        break;
    default:
        break;
    }
}

void CTest::PlayStateChange( long NewState )
{
    switch (NewState)
    {
    case wmppsUndefined:
        break;
    case wmppsStopped:
        break;
    case wmppsPaused:
        break;
    case wmppsPlaying:
        break;
    case wmppsScanForward:
        break;
    case wmppsScanReverse:
        break;
    case wmppsBuffering:
        break;
    case wmppsWaiting:
        break;
    case wmppsMediaEnded:
        break;
    case wmppsTransitioning:
        break;
    case wmppsReady:
        break;
    case wmppsReconnecting:
        break;
    case wmppsLast:
        break;
    default:
        break;
    }
}

void CTest::AudioLanguageChange( long LangID )
{
}

void CTest::StatusChange()
{
}

void CTest::ScriptCommand( BSTR scType, BSTR Param )
{
}

void CTest::NewStream()
{
}

void CTest::Disconnect( long Result )
{
}

void CTest::Buffering( VARIANT_BOOL Start )
{
}

void CTest::Error()
{
    CComPtr<IWMPError>      spError;
    CComPtr<IWMPErrorItem>  spErrorItem;
    HRESULT                 dwError = S_OK;
    HRESULT                 hr = S_OK;

    if (m_spCore)
    {
        hr = m_spCore->get_error(&spError);

        if (SUCCEEDED(hr))
        {
            hr = spError->get_item(0, &spErrorItem);
        }

        if (SUCCEEDED(hr))
        {
            hr = spErrorItem->get_errorCode( (long *) &dwError );
        }
    }
}

void CTest::Warning( long WarningType, long Param, BSTR Description )
{
}

void CTest::EndOfStream( long Result )
{
}

void CTest::PositionChange( double oldPosition, double newPosition)
{
}

void CTest::MarkerHit( long MarkerNum )
{
}

void CTest::DurationUnitChange( long NewDurationUnit )
{
}

void CTest::CdromMediaChange( long CdromNum )
{
}

void CTest::PlaylistChange( IDispatch * Playlist, WMPPlaylistChangeEventType change )
{
    switch (change)
    {
    case wmplcUnknown:
        break;
    case wmplcClear:
        break;
    case wmplcInfoChange:
        break;
    case wmplcMove:
        break;
    case wmplcDelete:
        break;
    case wmplcInsert:
        break;
    case wmplcAppend:
        break;
    case wmplcPrivate:
        break;
    case wmplcNameChange:
        break;
    case wmplcMorph:
        break;
    case wmplcSort:
        break;
    case wmplcLast:
        break;
    default:
        break;
    }
}

void CTest::CurrentPlaylistChange( WMPPlaylistChangeEventType change )
{
    switch (change)
    {
    case wmplcUnknown:
        break;
    case wmplcClear:
        break;
    case wmplcInfoChange:
        break;
    case wmplcMove:
        break;
    case wmplcDelete:
        break;
    case wmplcInsert:
        break;
    case wmplcAppend:
        break;
    case wmplcPrivate:
        break;
    case wmplcNameChange:
        break;
    case wmplcMorph:
        break;
    case wmplcSort:
        break;
    case wmplcLast:
        break;
    default:
        break;
    }
}

void CTest::CurrentPlaylistItemAvailable( BSTR bstrItemName )
{
}

void CTest::MediaChange( IDispatch * Item )
{
}

void CTest::CurrentMediaItemAvailable( BSTR bstrItemName )
{
}

void CTest::CurrentItemChange( IDispatch *pdispMedia)
{
}

void CTest::MediaCollectionChange()
{
}

void CTest::MediaCollectionAttributeStringAdded( BSTR bstrAttribName,  BSTR bstrAttribVal )
{
}

void CTest::MediaCollectionAttributeStringRemoved( BSTR bstrAttribName,  BSTR bstrAttribVal )
{
}

void CTest::MediaCollectionAttributeStringChanged( BSTR bstrAttribName, BSTR bstrOldAttribVal, BSTR bstrNewAttribVal)
{
}

void CTest::PlaylistCollectionChange()
{
}

void CTest::PlaylistCollectionPlaylistAdded( BSTR bstrPlaylistName)
{
}

void CTest::PlaylistCollectionPlaylistRemoved( BSTR bstrPlaylistName)
{
}

void CTest::PlaylistCollectionPlaylistSetAsDeleted( BSTR bstrPlaylistName, VARIANT_BOOL varfIsDeleted)
{
}

void CTest::ModeChange( BSTR ModeName, VARIANT_BOOL NewValue)
{
}

void CTest::MediaError( IDispatch * pMediaObject)
{
}

void CTest::OpenPlaylistSwitch( IDispatch *pItem )
{
}

void CTest::DomainChange( BSTR strDomain)
{
}

void CTest::SwitchedToPlayerApplication()
{
}

void CTest::SwitchedToControl()
{
}

void CTest::PlayerDockedStateChange()
{
}

void CTest::PlayerReconnect()
{
}

void CTest::Click( short nButton, short nShiftState, long fX, long fY )
{
}

void CTest::DoubleClick( short nButton, short nShiftState, long fX, long fY )
{
}

void CTest::KeyDown( short nKeyCode, short nShiftState )
{
}

void CTest::KeyPress( short nKeyAscii )
{
}

void CTest::KeyUp( short nKeyCode, short nShiftState )
{
}

void CTest::MouseDown( short nButton, short nShiftState, long fX, long fY )
{
}

void CTest::MouseMove( short nButton, short nShiftState, long fX, long fY )
{
}

void CTest::MouseUp( short nButton, short nShiftState, long fX, long fY )
{
}
