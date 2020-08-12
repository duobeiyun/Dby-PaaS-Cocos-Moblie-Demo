
#include "CacheVideoFrame.h"

namespace duobeiyun
{
    namespace cocos
    {
        CacheVideoFrame::CacheVideoFrame(int width, int height)
        {
            _width = width;
            _height = height;
            _data = malloc(width * height * 4);
        }

        CacheVideoFrame::~CacheVideoFrame()
        {
            if (_data)
            {
                free(_data);
                _data = NULL;
            }
        }
    }
}
