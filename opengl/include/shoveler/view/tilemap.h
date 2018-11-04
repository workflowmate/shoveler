#ifndef SHOVELER_VIEW_TILEMAP_H
#define SHOVELER_VIEW_TILEMAP_H

#include <stdbool.h> // bool

#include <glib.h>

#include <shoveler/material/tilemap.h>
#include <shoveler/tileset.h>
#include <shoveler/view.h>

typedef struct {
	int numLayers;
	long long int *layerEntityIds;
	int numTilesets;
	long long int *tilesetEntityIds;
} ShovelerViewTilemapConfiguration;

static const char *shovelerViewTilemapComponentName = "tilemap";

bool shovelerViewEntityAddTilemap(ShovelerViewEntity *entity, ShovelerViewTilemapConfiguration configuration);
bool shovelerViewEntityGetTilemapLayers(ShovelerViewEntity *entity, int *numLayersPointer, ShovelerTexture ***layersPointer);
bool shovelerViewEntityGetTilemapTilesets(ShovelerViewEntity *entity, int *numTilesetsPointer, ShovelerTileset ***tilesetsPointer);
const ShovelerViewTilemapConfiguration *shovelerViewEntityGetTilemapConfiguration(ShovelerViewEntity *entity);
bool shovelerViewEntityUpdateTilemap(ShovelerViewEntity *entity, ShovelerViewTilemapConfiguration configuration);
bool shovelerViewEntityRemoveTilemap(ShovelerViewEntity *entity);

#endif