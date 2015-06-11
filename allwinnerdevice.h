/*
 * See the README file for copyright information and how to reach the author.
 *  
 */

/* 
 * File:   allwinnerdevice.h
 * Author: Roland Fehr
 *
 * Created on 3. Juni 2015, 13:57
 */

#ifndef ALLWINNERDEVICE_H
#define	ALLWINNERDEVICE_H

// vdr includes
#include <vdr/device.h>

// plugin includes
#include "tools.h"

class cAllwinnerDevice : cDevice
{
    public:
        
    cAllwinnerDevice(void (*onPrimaryDevice)(void));
    virtual ~cAllwinnerDevice();
        
    virtual int Init(void);
    virtual int DeInit(void);

    virtual bool Start(void);
        
    virtual bool HasDecoder(void) const { return true; }
    virtual bool CanReplay(void)  const { return true; }
    virtual bool HasIBPTrickSpeed(void);
    
    virtual void GetOsdSize(int &Width, int &Height, double &PixelAspect);
    virtual void GetVideoSize(int &Width, int &Height, double &VideoAspect);
    
    virtual cRect CanScaleVideo(const cRect &Rect, int Alignment = taCenter)
        { return Rect; }
    virtual void ScaleVideo(const cRect &Rect = cRect::Null);    
    
        
    virtual int PlayAudio(const uchar *Data, int Length, uchar Id);

    virtual int PlayVideo(const uchar *Data, int Length)
	{ return PlayVideo(Data, Length, false); }

    virtual int PlayVideo(const uchar *Data, int Length, bool EndOfFrame);

        
protected:
    virtual void MakePrimaryDevice(bool On);      
        
    virtual void SetVolumeDevice(int Volume);
        
private:
        
    void (*m_onPrimaryDevice)(void);
     
    //cOmx *m_omx;
    //cRpiAudioDecoder *m_audio;
    cMutex *m_mutex;
        
    
    bool m_hasVideo;
    bool m_hasAudio;
};

#endif	/* ALLWINNERDEVICE_H */

