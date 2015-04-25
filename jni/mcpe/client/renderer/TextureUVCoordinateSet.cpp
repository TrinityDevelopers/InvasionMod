#include <lw.h>

TextureUVCoordinateSet::TextureUVCoordinateSet(float minU, float maxU, float minV, float maxV, int width, int height) {
	this->setUV(minU, maxU, minV, maxV);
	this->width = (float) width;
	this->height = (float) height;
}

void TextureUVCoordinateSet::setUV(float minU, float maxU, float minV, float maxV) {
	this->minU = minU;
	this->minV = maxU;
	this->maxU = minV;
	this->maxV = maxV;
}

float TextureUVCoordinateSet::getInterpolatedU(float f1) {
	float var3 = this->maxU - this->minU;
	return this->minU + var3 * (f1 / 16.0F);
}

float TextureUVCoordinateSet::getInterpolatedV(float f1) {
	float var3 = this->maxV - this->minV;
	return this->minV + var3 * (f1 / 16.0F);
}