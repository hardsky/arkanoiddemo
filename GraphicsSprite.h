#ifndef _HSG_GRAPHICSSPRITE_H_
#define _HSG_GRAPHICSSPRITE_H_

#include "GraphicsTexture.h"
#include "Math/Vector3.h"
#include "Types.h"

#include <boost/shared_ptr.hpp>
#include <vector>
#include <list>
#include <map>

using namespace gameplay;

namespace hsg {
    class GraphicsSprite {
    public:
        typedef boost::shared_ptr<GraphicsSprite> ptr;

        typedef std::vector<ptr> vec;
        typedef vec::iterator vec_it;

        typedef std::list<ptr> lst;
        typedef lst::iterator lst_it;

        typedef std::multimap<int, ptr> mm;
        typedef mm::iterator mm_it;
        typedef std::pair<int, ptr> mm_pair;

    public:
        GraphicsSprite();
        GraphicsSprite(GraphicsTexture* pImage);
        GraphicsSprite(GraphicsTexture* pImage,
            float pHeight, float pWidth, Vector3 pLocation);
        GraphicsSprite(GraphicsTexture* pImage,
            float x, float y, float height, float width);

        void setLocation(float xCenter, float yCenter){m_Location.set(xCenter, yCenter, 0);};
        void setLocation(const Vector3& location){m_Location.set(location);};
        const Vector3& getLocation()const;
        void setSize(float height, float width){m_Height= height;m_Width= width;};
        void draw();
        void setActive(bool bActive);
        bool isActive()const;
        float getWidth()const;
        void setWidth(float fWidth);
        float getHeight() const;
        void setHeight(float fHeight);
    protected:
        GraphicsTexture* m_Texture;
        Vector3 m_Location; //center
        float m_Height, m_Width;
        bool m_isActive;
    };
}
#endif
