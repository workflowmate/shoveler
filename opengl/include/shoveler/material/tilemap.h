#ifndef SHOVELER_MATERIAL_TILEMAP_H
#define SHOVELER_MATERIAL_TILEMAP_H

#include <shoveler/material.h>
#include <shoveler/texture.h>
#include <shoveler/tilemap.h>
#include <shoveler/tileset.h>

ShovelerMaterial *shovelerMaterialTilemapCreate();
/** adds a layer to a tilemap material, returning the index of the new layer */
int shovelerMaterialTilemapAddLayer(ShovelerMaterial *tilemapMaterial, ShovelerTexture *layerTexture);
/** adds a tileset to a tilemap material, returning the index of the new tileset */
int shovelerMaterialTilemapAddTileset(ShovelerMaterial *tilemapMaterial, ShovelerTileset *tileset);
void shovelerMaterialTilemapSetActive(ShovelerMaterial *tilemapMaterial, ShovelerTilemap *tilemap);
void shovelerMaterialTilemapSetActiveTiles(ShovelerMaterial *tilemapMaterial, ShovelerTexture *tiles);
void shovelerMaterialTilemapSetActiveTileset(ShovelerMaterial *tilemapMaterial, int tilesetId, ShovelerTileset *tileset);

#endif
