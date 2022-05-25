#ifndef OGLDEV_APP_H
#define OGLDEV_APP_H

#ifdef FREETYPE
#include "freetypeGL.h"
#endif


class OgldevApp
{
protected:
	OgldevApp();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

protected:
#ifdef FREETYPE
	FontRenderer m_fontRenderer;
#endif
private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
        int m_fps;
};

#endif