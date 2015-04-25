#pragma once

#include "../MemoryTracker.h"
#include <lw.h>

class Color;
class MaterialPtr;
class PrimitiveMode;
class Vec2;
class Index;

class Tessellator : public MemoryTracker {
public:
	static Tessellator instance;

public:
	Tessellator(MemoryTracker *);
	virtual ~Tessellator();
	void init();
	void clear();
	void begin(int);
	void begin(PrimitiveMode, int);
	void draw(const MaterialPtr&);
	void cancel();
	void beginIndices(int);
	void color(int);
	void color(int, int);
	void color(float, float, float, float);
	void color(const Color &);
	void color(int, int, int, int);
	void colorABGR(int);
	void normal(float, float, float);
	void normal(const Vec3&);
	void voidBeginAndEndCalls(bool);
	void tex(float, float);
	void tex1(float, float);
	void tex(const Vec2&);
	void tex1(const Vec2&);
	void vertex(float, float, float);
	void vertexUV(float, float, float, float, float);
	void vertexUV(const Vec3&, float, float);
	void vertex(const Vec3&);
	void quad(Index, Index, Index, Index);
	void quad(Index, bool);
	void quad(bool);
	void triangle(Index, Index, Index);
	void scale2d(float, float);
	void scale3d(float, float, float);
	void resetScale();
	void tilt();
	void resetTilt();
	void noColor();
	void enableColor();
	void trim();
	int getByteSize() const;
	void setOffset(float, float, float);
	void setOffset(const Vec3&);
	void addOffset(float, float, float);
	void addOffset(const Vec3&);
	void rotationOffset(float, const Vec3&);
	int getPolygonCount() const;
	int getColor();
	bool isTessellating() const;
	void beginOverride();
	void endOverrideAndDraw(const MaterialPtr&);
	bool isOverridden();
	void convertToTrilist(bool);
};
