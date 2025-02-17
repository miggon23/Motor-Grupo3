#pragma once
#ifndef __SCOLOR_H__
#define __SCOLOR_H__

#include <iostream>
#include "FlamingoExport/FlamingoAPI.h"

namespace Ogre
{
    class ColourValue;
}

namespace Flamingo
{
    class  SColor
    {
      public:
        FLAMINGOEXPORT_API SColor(float t_r = 1.0f, float t_g = 1.0f, float t_b = 1.0f, float t_a = 1.0f);
        FLAMINGOEXPORT_API ~SColor() = default;

        FLAMINGOEXPORT_API void setColor(float t_r, float t_g, float t_b, float t_a = 1.0f);

        FLAMINGOEXPORT_API bool operator==(const SColor& other);
        FLAMINGOEXPORT_API bool operator!=(const SColor& other);

        FLAMINGOEXPORT_API SColor operator+(const SColor& other);
        FLAMINGOEXPORT_API SColor operator-(const SColor& other);
        FLAMINGOEXPORT_API SColor operator*(const float& t_scalar);
        FLAMINGOEXPORT_API SColor operator*(const SColor& other);
        FLAMINGOEXPORT_API SColor operator/(const float& t_scalar);
        FLAMINGOEXPORT_API SColor operator/(const SColor& other);

        FLAMINGOEXPORT_API void operator+=(const SColor& other);
        FLAMINGOEXPORT_API void operator-=(const SColor& other);
        FLAMINGOEXPORT_API void operator*=(const float& t_scalar);
        FLAMINGOEXPORT_API void operator/=(const float& t_scalar);

        FLAMINGOEXPORT_API friend std::ostream& operator<<(std::ostream& out, const SColor& v);

        FLAMINGOEXPORT_API operator Ogre::ColourValue() const;
        static SColor ogreToSColor(const Ogre::ColourValue& t_ogre_color);

      private:
        float m_r;
        float m_g;
        float m_b;
        float m_a;

        void saturate();
        void saturate(SColor& t_c);
    };
} // namespace Flamingo
#endif
