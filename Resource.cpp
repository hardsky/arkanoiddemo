#include "Resource.h"
#include "Log.h"

#include <sys/stat.h>

namespace hsg {
    Resource::Resource(const char* pPath):
        mPath(pPath), mInputStream(), mBuffer(0)
    {}

    status Resource::open() {
        mInputStream.open(mPath, std::ios::in | std::ios::binary);
        return mInputStream ? STATUS_OK : STATUS_KO;
    }

    void Resource::close() {
        mInputStream.close();
        delete[] mBuffer; mBuffer = 0;
    }

    status Resource::read(void* pBuffer, size_t pCount) {
        mInputStream.read((char*)pBuffer, pCount);
        return (!mInputStream.fail()) ? STATUS_OK : STATUS_KO;
    }

    const char* Resource::getPath() {
        return mPath;
    }

    off_t Resource::getLength() {
        struct stat filestatus;
        if (stat(mPath, &filestatus) >= 0) {
            return filestatus.st_size;
        } else {
            return -1;
        }
    }

    const void* Resource::bufferize() {
        off_t lSize = getLength();
        if (lSize <= 0) return 0;

        mBuffer = new char[lSize];
        mInputStream.read(mBuffer, lSize);
        if (!mInputStream.fail()) {
            return mBuffer;
        } else {
            return 0;
        }
    }
}
