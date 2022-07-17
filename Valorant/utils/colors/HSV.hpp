#pragma once

#include <iostream>

using namespace std;

class Color {
	public:
		static struct HSV {
            int h;
            float s;
            float v;
        };

        static enum ColorName
        {
            Neutro,
            Vermelho,
            Magenta,
            Violeta,
            Azul,
            Ciano,
            Verde,
            Amarelo,
            Laranja
        };
        static string toString(ColorName color);
};

//PASTED SCRIPT FROM https://github.com/FloatingBanana

#define M_MIN(a, b) (a < b ? a : b)
#define M_MAX(a, b) (a < b ? b : a)

Color::HSV toHSV(float r, float g, float b) {
    r = r / 255.0f;
    g = g / 255.0f;
    b = b / 255.0f;

    float cmax = M_MAX(r, M_MAX(g, b));
    float cmin = M_MIN(r, M_MIN(g, b));
    float diff = cmax - cmin;
    int h = 0;
    float s = 0;
    float v = cmax;

    if (cmax == cmin)
        h = 0;
    else if (cmax == r)
        h = 60 * ((g - b) / diff) + 360;

    else if (cmax == g)
        h = 60 * ((b - r) / diff) + 120;

    else if (cmax == b)
        h = 60 * ((r - g) / diff) + 240;

    if (diff != 0) {
        s = (diff / cmax);
    }

    return { h = h % 360, s = s, v = v };
};

//END OF SCRIPT FROM FLOATING BANANA
//BASED ON SCRIPT FROM Lalo (KaitoMajima)

Color::ColorName Categorize(Color::HSV color)
{
    if (color.s <= 0) return Color::ColorName::Neutro;
    if ((color.v * 100) <= 13) return Color::ColorName::Neutro;
    if ((color.s * 100) <= 13) return Color::ColorName::Neutro;

    float hue = color.h;

    if(hue >= 345 || hue < 30)
        return Color::ColorName::Vermelho;
    if(hue >= 285)
        return Color::ColorName::Magenta;
    if(hue >= 270)
        return Color::ColorName::Violeta;
    if(hue >= 210)
        return Color::ColorName::Azul;
    if(hue >= 165)
        return Color::ColorName::Ciano;
    if(hue >= 105)
        return Color::ColorName::Verde;
    if(hue >= 45)
        return Color::ColorName::Amarelo;
    if(hue >= 30)
        return Color::ColorName::Laranja;
}

//END OF BAED SCRIPT


string Color::toString(ColorName color)
{
    switch (color)
    {
        case Color::Neutro:
            return "neutro";
        case Color::Vermelho:
            return "vermelho";
        case Color::Magenta:
            return "magenta";
        case Color::Violeta:
            return "violeta";
        case Color::Azul:
            return "azul";
        case Color::Ciano:
            return "ciano";
        case Color::Verde:
            return "verde";
        case Color::Amarelo:
            return "amarelo";
        case Color::Laranja:
            return "laranja";
        default:
            return "erro";
    }
}