
#include "DBYContext.hpp"

namespace duobeiyun {
    namespace cocos {
        DBYContext::DBYContext() : _refObj(NULL), _dbyEngineEventHandler(NULL),
                                   _videoDataControl(NULL) {

        }

        DBYContext::~DBYContext() {

            if (_dbyEngineEventHandler) {
                delete _dbyEngineEventHandler;
                _dbyEngineEventHandler = NULL;
            }
            if (_videoDataControl) {
                delete _videoDataControl;
                _videoDataControl = NULL;
            }
        }
    }
}
