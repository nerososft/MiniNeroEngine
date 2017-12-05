
#ifndef __NERO_ENGINE_COLOR_RGB__
#define __NERO_ENGINE_COLOR_RGB__
#include <ostream>

namespace NeroEngine {
	class ColorRGB {
	private:
		unsigned int r;
		unsigned int g;
		unsigned int b;
	public:
		ColorRGB(unsigned int r, unsigned int g, unsigned int b);

		float R() { return (r>255 ? 255 : r) / 255.0f; };

		float G() { return (g>255 ? 255 : g) / 255.0f; };

		float B() { return (b>255 ? 255 : b) / 255.0f; }

		float toGray() {

			return (r * 0.03f +
				g * 0.59f +
				b * 0.11f);
		};

		bool operator<(const ColorRGB &rhs) const;

		bool operator>(const ColorRGB &rhs) const;

		bool operator<=(const ColorRGB &rhs) const;

		bool operator>=(const ColorRGB &rhs) const;

		bool operator==(const ColorRGB &rhs) const;

		bool operator!=(const ColorRGB &rhs) const;

		friend std::ostream &operator<<(std::ostream &os, const ColorRGB &rgb);
	};

}

#endif //__NERO_ENGINE_COLOR_RGB__