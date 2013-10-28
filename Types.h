#ifndef HSG_TYPES_H_
#define HSG_TYPES_H_

#include <stdint.h>

namespace hsg {
    typedef int32_t status;

    const status STATUS_OK   = 0;
    const status STATUS_KO   = -1;

    template<typename T>struct Size{
    	Size():Width(0), Height(0){}
    	Size(T height, T width): Width(width),Height(height){}

    	T Width;
    	T Height;
    };

    typedef Size<float> Size_f;
    typedef Size<int> Size_i;

}

#endif /* HSG_TYPES_H_ */
