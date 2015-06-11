/*
 * See the README file for copyright information and how to reach the author.
 *  
 */

/* 
 * File:   allwinnerdevice.c
 * Author: Roland Fehr
 *
 * Created on 3. Juni 2015, 13:58
 */

#include "allwinnerdevice.h"

/**
 * Construktor
 * 
 */
cAllwinnerDevice::cAllwinnerDevice(void (*onPrimaryDevice)(void)) : 
    cDevice(),
    m_onPrimaryDevice(onPrimaryDevice),
    m_mutex(new cMutex()),
    m_hasVideo(false),
    m_hasAudio(false)
{

}// end of method

/**
 * Deconstructor
 * 
 */
cAllwinnerDevice::~cAllwinnerDevice()
{
    DeInit();

    //delete m_omx;
    //delete m_audio;
    delete m_mutex;
}// end of method

/**
 * Init 
 * @return int 
 */
int cAllwinnerDevice::Init(void)
{
    return 0;
    
}// end of method

/**
 * DeInit 
 * @return int
 */
int cAllwinnerDevice::DeInit(void)
{
    return 0;
}// end of method

/**
 * Start 
 * @return bool
 */
bool cAllwinnerDevice::Start(void)
{
    return true;
}// end of method

/**
 * HasIBPTrickSpeed
 * @return 
 */
bool cAllwinnerDevice::HasIBPTrickSpeed(void)
{
	return !m_hasVideo;
}// end of method

/**
 * GetOsdSize
 * @param Width
 * @param Height
 * @param PixelAspect
 */
void cAllwinnerDevice::GetOsdSize(int &Width, int &Height, double &PixelAspect)
{
    //cRpiDisplay::GetSize(Width, Height, PixelAspect);
}// end of method

/**
 * GetVideoSize
 * @param Width
 * @param Height
 * @param VideoAspect
 */
void cAllwinnerDevice::GetVideoSize(int &Width, int &Height, double &VideoAspect)
{
	bool interlaced;
	int frameRate;

	//m_omx->GetVideoFormat(Width, Height, frameRate, interlaced);

	if (Height)
		VideoAspect = (double)Width / Height;
	else
		VideoAspect = 1.0;
}//end of method

/**
 * ScaleVideo
 * @param Rect
 */
void cAllwinnerDevice::ScaleVideo(const cRect &Rect)
{
	DBG("ScaleVideo(%d, %d, %d, %d)",
		Rect.X(), Rect.Y(), Rect.Width(), Rect.Height());

	//m_omx->SetDisplayRegion(Rect.X(), Rect.Y(), Rect.Width(), Rect.Height());
}//end of method

/**
 * MakePrimaryDevice
 * @param On
 */
void cAllwinnerDevice::MakePrimaryDevice(bool On)
{
	if (On && m_onPrimaryDevice)
		m_onPrimaryDevice();
	cDevice::MakePrimaryDevice(On);
}// end of method

/**
 * 
 * @param Volume
 */
void cAllwinnerDevice::SetVolumeDevice(int Volume)
{
	DBG("SetVolume(%d)", Volume);
	if (Volume)
	{
		//m_omx->SetVolume(Volume);
		//m_omx->SetMute(false);
	}
	//else
		//m_omx->SetMute(true);
}// end of method

/**
 * PlayAudio 
 * @param Data
 * @param Length
 * @param Id
 * @return 
 */
int cAllwinnerDevice::PlayAudio(const uchar *Data, int Length, uchar Id)
{
	m_mutex->Lock();
/*
	if (!m_hasAudio)
	{
		m_hasAudio = true;
		m_audioId = Id;
		m_omx->SetClockReference(cOmx::eClockRefAudio);

		if (!m_hasVideo)
		{
			DBG("audio first");
			m_omx->SetClockScale(s_playbackSpeeds[m_direction][m_playbackSpeed]);
			m_omx->StartClock(m_hasVideo, m_hasAudio);
		}

		if (Transferring())
			ResetLatency();
	}

	int64_t pts = PesHasPts(Data) ? PesGetPts(Data) : 0;

	// keep track of direction in case of trick speed
	if (m_trickRequest && pts)
	{
		if (m_audioPts)
			PtsTracker(PtsDiff(m_audioPts, pts));

		m_audioPts = pts;
	}

	if (Transferring() && pts)
	{
		if (m_audioId != Id)
		{
			ResetLatency();
			m_audioId = Id;
		}
		UpdateLatency(pts);
	}

	int ret = Length;
	int length = Length - PesPayloadOffset(Data);

	// ignore packets with invalid payload offset
	if (length > 0)
	{
		const uchar *data = Data + PesPayloadOffset(Data);

		// remove audio substream header as seen in PES recordings with AC3
		// audio track (0x80: AC3, 0x88: DTS, 0xA0: LPCM)
		if ((data[0] == 0x80 || data[0] == 0x88 || data[0] == 0xa0)
				&& data[0] == Id)
		{
			data += 4;
			length -= 4;
		}
		if (!m_audio->WriteData(data, length, pts))
			ret = 0;
	}
 */
	m_mutex->Unlock();
	//return ret;
        return 1;
}// end of method

/**
 * 
 * @param Data
 * @param Length
 * @param EndOfFrame
 * @return 
 */
int cAllwinnerDevice::PlayVideo(const uchar *Data, int Length, bool EndOfFrame)
{
    m_mutex->Lock();
        /*
    int ret = Length;

    cVideoCodec::eCodec codec = PesHasPts(Data) ? ParseVideoCodec(
                    Data + PesPayloadOffset(Data), Length - PesPayloadOffset(Data)) :
                    cVideoCodec::eInvalid;

    // video restart after Clear() with same codec
    bool videoRestart = (!m_hasVideo && codec == m_videoCodec &&
                    cRpiSetup::IsVideoCodecSupported(codec));

    // video restart after SetPlayMode() or codec changed
    if (codec != cVideoCodec::eInvalid && codec != m_videoCodec)
    {
            m_videoCodec = codec;

            if (m_hasVideo)
            {
                    m_omx->StopVideo();
                    m_hasVideo = false;
            }

            if (cRpiSetup::IsVideoCodecSupported(codec))
            {
                    videoRestart = true;
                    m_omx->SetVideoCodec(codec);
                    DLOG("set video codec to %s", cVideoCodec::Str(codec));
            }
            else
                    Skins.QueueMessage(mtError, tr("video format not supported!"));
    }

    if (videoRestart)
    {
            m_hasVideo = true;

            if (!m_hasAudio)
            {
                    DBG("video first");
                    m_omx->SetClockReference(cOmx::eClockRefVideo);
                    m_omx->SetClockScale(s_playbackSpeeds[m_direction][m_playbackSpeed]);
                    m_omx->StartClock(m_hasVideo, m_hasAudio);
            }

            if (Transferring())
                    ResetLatency();
    }

    if (m_hasVideo)
    {
            int64_t pts = PesHasPts(Data) ? PesGetPts(Data) : 0;

            // keep track of direction in case of trick speed
            if (m_trickRequest && pts && m_videoPts)
                    PtsTracker(PtsDiff(m_videoPts, pts));

            if (!m_hasAudio && Transferring() && pts)
                    UpdateLatency(pts);

            // skip PES header, proceed with payload towards OMX
            Length -= PesPayloadOffset(Data);
            Data += PesPayloadOffset(Data);

            while (Length > 0)
            {
                    OMX_BUFFERHEADERTYPE *buf = m_omx->GetVideoBuffer(pts);
                    if (buf)
                    {
                            buf->nFilledLen = buf->nAllocLen < (unsigned)Length ?
                                            buf->nAllocLen : Length;

                            memcpy(buf->pBuffer, Data, buf->nFilledLen);
                            Length -= buf->nFilledLen;
                            Data += buf->nFilledLen;

                            if (EndOfFrame && !Length)
                                    buf->nFlags |= OMX_BUFFERFLAG_ENDOFFRAME;

                            if (!m_omx->EmptyVideoBuffer(buf))
                            {
                                    ret = 0;
                                    ELOG("failed to pass buffer to video decoder!");
                                    break;
                            }
                    }
                    else
                    {
                            ret = 0;
                            break;
                    }
                    pts = 0;
            }int cOmxDevice::PlayVideo(const uchar *Data, int Length, bool EndOfFrame)
    {
    m_mutex->Lock();
    int ret = Length;

    cVideoCodec::eCodec codec = PesHasPts(Data) ? ParseVideoCodec(
                    Data + PesPayloadOffset(Data), Length - PesPayloadOffset(Data)) :
                    cVideoCodec::eInvalid;

    // video restart after Clear() with same codec
    bool videoRestart = (!m_hasVideo && codec == m_videoCodec &&
                    cRpiSetup::IsVideoCodecSupported(codec));

    // video restart after SetPlayMode() or codec changed
    if (codec != cVideoCodec::eInvalid && codec != m_videoCodec)
    {
            m_videoCodec = codec;

            if (m_hasVideo)
            {
                    m_omx->StopVideo();
                    m_hasVideo = false;
            }

            if (cRpiSetup::IsVideoCodecSupported(codec))
            {
                    videoRestart = true;
                    m_omx->SetVideoCodec(codec);
                    DLOG("set video codec to %s", cVideoCodec::Str(codec));
            }
            else
                    Skins.QueueMessage(mtError, tr("video format not supported!"));
    }

    if (videoRestart)
    {
            m_hasVideo = true;

            if (!m_hasAudio)
            {
                    DBG("video first");
                    m_omx->SetClockReference(cOmx::eClockRefVideo);
                    m_omx->SetClockScale(s_playbackSpeeds[m_direction][m_playbackSpeed]);
                    m_omx->StartClock(m_hasVideo, m_hasAudio);
            }

            if (Transferring())
                    ResetLatency();
    }

    if (m_hasVideo)
    {
            int64_t pts = PesHasPts(Data) ? PesGetPts(Data) : 0;

            // keep track of direction in case of trick speed
            if (m_trickRequest && pts && m_videoPts)
                    PtsTracker(PtsDiff(m_videoPts, pts));

            if (!m_hasAudio && Transferring() && pts)
                    UpdateLatency(pts);

            // skip PES header, proceed with payload towards OMX
            Length -= PesPayloadOffset(Data);
            Data += PesPayloadOffset(Data);

            while (Length > 0)
            {
                    OMX_BUFFERHEADERTYPE *buf = m_omx->GetVideoBuffer(pts);
                    if (buf)
                    {
                            buf->nFilledLen = buf->nAllocLen < (unsigned)Length ?
                                            buf->nAllocLen : Length;

                            memcpy(buf->pBuffer, Data, buf->nFilledLen);
                            Length -= buf->nFilledLen;
                            Data += buf->nFilledLen;

                            if (EndOfFrame && !Length)
                                    buf->nFlags |= OMX_BUFFERFLAG_ENDOFFRAME;

                            if (!m_omx->EmptyVideoBuffer(buf))
                            {
                                    ret = 0;
                                    ELOG("failed to pass buffer to video decoder!");
                                    break;
                            }
                    }
                    else
                    {
                            ret = 0;
                            break;
                    }
                    pts = 0;
            }
    }
    m_mutex->Unlock();
    return ret;
    }
	}
         */
	m_mutex->Unlock();
	//return ret;
        return 1;
}// end of method