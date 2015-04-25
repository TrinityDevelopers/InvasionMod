#pragma once

#include <lw.h>
#include "../../level/TileSource.h"
#include "Tessellator.h"

class TileTessellator {
public:
	char filler[4];						// 0
	TileSource *_tileSource;			// 4
	TextureUVCoordinateSet _texture;	// 8
	bool _renderTexture;				// 40
	char filler1[88];					//128
    int rotBottom;						//132
    int rotTop;							//136
    int rotEast;						//140
    int rotWest;						//144
    int rotNorth;						//148
    int rotSouth;						//152
    char filler2[512];					//660
	Tessellator* tessellator_inst;		// 664
	AABB bounds;						// 668

public:
    bool tessellateGlowstoneTorchTileInWorld(Tile*, int, int, int, TilePos const&, TileSource*);
    void tessellateGlowstoneTorch(Tile*, double, double, double, double, double);
	bool tessellateInWorld(Tile *, const TilePos &, bool);
	void tessellateBlockInWorld(Tile *, const TilePos &);
	void tessellateTorch(Tile*, float, float, float, float, float);
    void getData(TilePos const&) const;
	long getLightColor(const TilePos &);
	void tex1(unsigned int);
    void setRenderBounds(AABB const&);
};
