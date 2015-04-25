#include "TileTessellator.h"

void TileTessellator::setRenderBounds(AABB const& bounds) {
    this->bounds = bounds;
}

bool TileTessellator::tessellateGlowstoneTorchTileInWorld(Tile* tile, int x, int y, int z, TilePos const& pos, TileSource* ts) {
    int data = ts->getData(x, y, z);
    Tessellator* tess = this->tessellator_inst;
    tess->color(1.0F, 1.0F, 1.0F, 1.0F);
    double var7 = 0.4000000059604645D;
    double var9 = 0.5F - var7;
    double var11 = 0.20000000298023224D;
 
    if(data == 1) this->tessellateGlowstoneTorch(tile, x - var9, y + var11, z, -var7, 0.0F);
    else if(data == 2) this->tessellateGlowstoneTorch(tile, x + var9, y + var11, z, var7, 0.0F);
    else if(data == 3) this->tessellateGlowstoneTorch(tile, x, y + var11, z - var9, 0.0F, -var7);
    else if(data == 4) this->tessellateGlowstoneTorch(tile, x, y + var11, z + var9, 0.0F, var7);
    else this->tessellateGlowstoneTorch(tile, x, y, z, 0.0F, 0.0F);
    return true;
}
 
void TileTessellator::tessellateGlowstoneTorch(Tile* tile, double x, double y, double z, double xRot, double zRot) {
    Tessellator* tess = this->tessellator_inst;
    TextureUVCoordinateSet gTorch = tile->getTextureUVCoordinateSet("glowstone_torch", 0);
 
    float var15 = gTorch.minU;
    float var17 = gTorch.minV;
    float var19 = gTorch.maxU;
    float var21 = gTorch.maxV;
    float var23 = gTorch.getInterpolatedU(7.0F);
    float var25 = gTorch.getInterpolatedV(6.0F);
    float var27 = gTorch.getInterpolatedU(9.0F);
    float var29 = gTorch.getInterpolatedV(8.0F);
    float var31 = gTorch.getInterpolatedU(7.0F);
    float var33 = gTorch.getInterpolatedV(13.0F);
    float var35 = gTorch.getInterpolatedU(9.0F);
    float var37 = gTorch.getInterpolatedV(15.0F);
    x += 0.5F;
    z += 0.5F;
    float var39 = x - 0.5F;
 
    float var41 = x + 0.5F;
    float var43 = z - 0.5F;
    float var45 = z + 0.5F;
    float var47 = 0.0625F;
    float var49 = 0.625F;
 
    tess->vertexUV(x + xRot * (1.0F - var49) - var47, y + var49, z + zRot * (1.0F - var49) - var47, var23, var25);
    tess->vertexUV(x + xRot * (1.0F - var49) - var47, y + var49, z + zRot * (1.0F - var49) + var47, var23, var29);
    tess->vertexUV(x + xRot * (1.0F - var49) + var47, y + var49, z + zRot * (1.0F - var49) + var47, var27, var29);
    tess->vertexUV(x + xRot * (1.0F - var49) + var47, y + var49, z + zRot * (1.0F - var49) - var47, var27, var25);
    tess->vertexUV(x + var47 + xRot, y, z - var47 + zRot, var35, var33);
    tess->vertexUV(x + var47 + xRot, y, z + var47 + zRot, var35, var37);
    tess->vertexUV(x - var47 + xRot, y, z + var47 + zRot, var31, var37);
    tess->vertexUV(x - var47 + xRot, y, z - var47 + zRot, var31, var33);
    tess->vertexUV(x - var47, y + 1.0F, var43, var15, var17);
    tess->vertexUV(x - var47 + xRot, y + 0.0F, var43 + zRot, var15, var21);
    tess->vertexUV(x - var47 + xRot, y + 0.0F, var45 + zRot, var19, var21);
    tess->vertexUV(x - var47, y + 1.0F, var45, var19, var17);
    tess->vertexUV(x + var47, y + 1.0F, var45, var15, var17);
    tess->vertexUV(x + xRot + var47, y + 0.0F, var45 + zRot, var15, var21);
    tess->vertexUV(x + xRot + var47, y + 0.0F, var43 + zRot, var19, var21);
    tess->vertexUV(x + var47, y + 1.0F, var43, var19, var17);
    tess->vertexUV(var39, y + 1.0F, z + var47, var15, var17);
    tess->vertexUV(var39 + xRot, y + 0.0F, z + var47 + zRot, var15, var21);
    tess->vertexUV(var41 + xRot, y + 0.0F, z + var47 + zRot, var19, var21);
    tess->vertexUV(var41, y + 1.0F, z + var47, var19, var17);
    tess->vertexUV(var41, y + 1.0F, z - var47, var15, var17);
    tess->vertexUV(var41 + xRot, y + 0.0F, z - var47 + zRot, var15, var21);
    tess->vertexUV(var39 + xRot, y + 0.0F, z - var47 + zRot, var19, var21);
    tess->vertexUV(var39, y + 1.0F, z - var47, var19, var17);
}