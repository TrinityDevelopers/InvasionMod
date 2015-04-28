#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>
#include <string>
#include <map>
#include <memory>
#include <lw.h>
#include <alienSpawner.h>
#include <GlowstoneTorch.h>
#include "mcpe/client/renderer/TileTessellator.h"
bool reg=false;
bool itemsAdded=false;

static void (*Minecraft_selectLevel_real)(Level*, Minecraft*, std::string const&, std::string const&, LevelSettings const&);
static void (*Gui_render_real)(Gui*, float, bool, int, int);
static void (*Item_initItems_real)();
static void (*Tile_initTiles_real)();
static void (*Item_initCreativeItems_real)();
static void (*TileTessellator_tessellateInWorld_real)(TileTessellator*, Tile*, const TilePos&, bool);
static std::string (*I18n_get_real)(std::string const&,std::vector<std::string,std::allocator<std::string>> const&);

static void addShapedRecipe(int id, int count, int damage, std::string line1, std::string line2, std::string line3, int ingCount, char charArray[], int idArray[]) {
	std::vector<std::string> shape={ line1, line2, line3};
	std::vector<Recipes::Type> ingredients;
	for(int n=0; n<ingCount; n++) {
		Recipes::Type recipeType;
		if(idArray[n]<=256) {
		    recipeType.tile=Tile::tiles[idArray[n]];
		    recipeType.item=NULL;
		}
		else {
			recipeType.tile=NULL;
			recipeType.item=Item::items[idArray[n]];
		}
		recipeType.c=charArray[n];
		ingredients.push_back(recipeType);
	}
	Recipes::getInstance()->addShapedRecipe(ItemInstance(id, count, damage), shape, ingredients);
}

static void Minecraft_selectLevel_hook(Level* level, Minecraft* mc, std::string const& str1, std::string const& str2, LevelSettings const& settings) {
	/*if(!reg) {
		reg=true;
		char gtChars[]={'g', 's'};
	    int gtIngs[]={348, 280};
	    addShapedRecipe(GLOWSTONE_TORCH_ID, 4, 0, "  ", " g ", " s ", 2, gtChars, gtIngs);
	}*/
	Minecraft_selectLevel_real(level, mc, str1, str2, settings);
}

static void Item_initItems_hook() {
	Item_initItems_real();
	AlienSpawner* alienSpawner = new AlienSpawner(ALIEN_SPAWNER_ID-0x100, "alienSpawner", 64);;
};

static void Tile_initTiles_hook() {
	Tile_initTiles_real();
	GlowstoneTorch* glowstoneTorch = new GlowstoneTorch(GLOWSTONE_TORCH_ID, "glowstoneTorch");
	TileItem* glowstoneTorchItem = new TileItem(GLOWSTONE_TORCH_ID-0x100);
}

static void Gui_render_hook(Gui* gui, float f1, bool b1, int i1, int i2) {
	Gui_render_real(gui, f1, b1, i1, i2);
}

static void Item_initCreativeItems_hook() {
	Item_initCreativeItems_real();
	Item::addCreativeItem(Item::items[ALIEN_SPAWNER_ID], 0);
	Item::addCreativeItem(Tile::tiles[GLOWSTONE_TORCH_ID], 0);
}

static void TileTessellator_tessellateInWorld_hook(TileTessellator* tess, Tile* tile, TilePos const& pos, bool b1) {
	if(tile->renderShape == 110) {
		tess->tessellateGlowstoneTorchTileInWorld(tile, pos.x, pos.y, pos.z, pos, tess->_tileSource);
	} else {
		TileTessellator_tessellateInWorld_real(tess, tile, pos, b1);
	}
}

static std::string I18n_get_hook(std::string const& key,std::vector<std::string,std::allocator<std::string>> const& a) {
	if(key == "item.alienSpawner.name") {
		return "Spawn Alien Villager";
	} else if(key == "tile.glowstoneTorch.name") {
		return "Glowstone Torch";
	} else {
		return I18n_get_real(key, a);
	}
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void* I18n_get = dlsym(RTLD_DEFAULT, "_ZN4I18n3getERKSsRKSt6vectorISsSaISsEE");
	MSHookFunction((void*) &Gui::render, (void*) &Gui_render_hook, (void**) &Gui_render_real);
    MSHookFunction((void*) &Minecraft::selectLevel, (void*) &Minecraft_selectLevel_hook, (void**) &Minecraft_selectLevel_real);
	MSHookFunction((void*) &Item::initItems, (void*) &Item_initItems_hook, (void**) &Item_initItems_real);
    MSHookFunction((void*) &Tile::initTiles, (void*) &Tile_initTiles_hook, (void**) &Tile_initTiles_real);
	MSHookFunction((void*) &Item::initCreativeItems, (void*) &Item_initCreativeItems_hook, (void**) &Item_initCreativeItems_real);
	MSHookFunction((void*) &TileTessellator::tessellateInWorld, (void*) &TileTessellator_tessellateInWorld_hook, (void**) &TileTessellator_tessellateInWorld_real);
	MSHookFunction(I18n_get, (void*) &I18n_get_hook, (void**) &I18n_get_real);
    return JNI_VERSION_1_2;
}