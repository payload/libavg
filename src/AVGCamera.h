//
// $Id$
// 

#ifndef _AVGCamera_H_
#define _AVGCamera_H_

#include "AVGNode.h"
#include "IAVGCamera.h"
#include "AVGVideoBase.h"
#include "AVGRect.h"

#include <paintlib/plbitmap.h>

#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>

#include <string>

#define AVGCAMERA_CID \
{ 0x08ced825, 0x6506, 0x41b4, { 0x87, 0xd4, 0xc8, 0x83, 0x4d, 0xb0, 0x81, 0x92 } }

#define AVGCAMERA_CONTRACTID "@c-base.org/avgcamera;1"

class AVGCamera : public AVGVideoBase , public IAVGCamera
{
    public:
        NS_DECL_ISUPPORTS
        NS_DECL_IAVGCAMERA

        static AVGCamera * create();

        AVGCamera ();
        virtual ~AVGCamera ();
        
        NS_IMETHOD GetType(PRInt32 *_retval);

        virtual void init (const std::string& id, const std::string& sDevice, 
            double frameRate, const std::string& sMode, bool bOverlay, 
            IAVGDisplayEngine * pEngine, AVGContainer * pParent, 
            AVGPlayer * pPlayer);
        virtual std::string getTypeStr ();

    private:
        bool findCameraOnPort(int port, raw1394handle_t& FWHandle);
        
        virtual bool renderToBmp(PLBmp * pBmp, const AVGDRect* pVpt = 0);
        virtual bool canRenderToBackbuffer(int BitsPerPixel);
        void YUV411toBGR24Line(PLBYTE* pSrc, int y, PLPixel24 * pDestLine);
        void YUV411toBGR24(PLBYTE* pSrc, PLBmp * pBmp);
        void YUV411toBGR24(PLBYTE* pSrc, PLBmp * pBmp, const AVGDRect& vpt);
       
        virtual bool open(int* pWidth, int* pHeight);
        virtual void close();
        virtual double getFPS();
        void checkDC1394Error(int Code, const std::string & sMsg);
        void fatalError(const std::string & sMsg);
        void dumpCameraInfo(raw1394handle_t PortHandle, nodeid_t CameraNode);

        std::string m_sDevice;
        double m_FrameRate;
        int m_FrameRateConstant;  // libdc1394 constant for framerate.
        std::string m_sMode;
        int m_Mode;               // libdc1394 constant for mode.

        dc1394_cameracapture m_Camera;
        raw1394handle_t m_FWHandle;

        static void initCameraSupport();
        static void initYUV2RGBConversionMatrix();
        static bool m_bInitialized;

};


#endif 

