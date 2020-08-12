
#ifndef DBYContext_hpp
#define DBYContext_hpp

#include "include_file.h"

#include "DBYEngineExtension.h"
#include "DbyVideoRawDataControl.h"

namespace duobeiyun
{
    namespace cocos
    {
        class DBYContext
        {
        public:
            se::Object* _refObj;
            DbyEngineEventHandler* _dbyEngineEventHandler;
            DbyVideoRawDataControl *_videoDataControl;
            DBYContext();
            ~DBYContext();
        };
    }
}
#endif /* DBYContext_hpp */
