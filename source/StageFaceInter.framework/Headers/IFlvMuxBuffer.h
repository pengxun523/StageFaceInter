#pragma once
#include "sskj_log.h"

class IFlvMuxBuffer
{
public:
	IFlvMuxBuffer(){};
	virtual ~IFlvMuxBuffer(){};
	virtual int GetFlvHead(const unsigned char *&pFlvHead, int &flvHeadLen, unsigned int &configVideoBitRate, unsigned int &configAudioBitRate) = 0;
	virtual int GetPacket(unsigned char *cPacket, unsigned int uiPacketSize, unsigned int &uiKeyFrame, unsigned int &seqCount) = 0;
};

