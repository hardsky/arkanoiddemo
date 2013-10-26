#ifndef _PACKT_RESOURCE_HPP_
#define _PACKT_RESOURCE_HPP_

#include "Types.h"
#include <fstream>

namespace hsg {
    class Resource {
    public:
        Resource(const char* pPath);

        const char* getPath();

        status open();
        void close();
        status read(void* pBuffer, size_t pCount);

        off_t getLength();
        const void* bufferize();

    private:
        const char* mPath;
        std::ifstream mInputStream;
        char* mBuffer;
    };
}
#endif
