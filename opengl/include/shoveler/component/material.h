#ifndef SHOVELER_COMPONENT_MATERIAL_H
#define SHOVELER_COMPONENT_MATERIAL_H

#include <shoveler/material/texture.h>

typedef struct ShovelerMaterialStruct ShovelerMaterial; // forward declaration: material.h
typedef struct ShovelerComponentTypeStruct ShovelerComponentType; // forward declaration: component.h
typedef struct ShovelerComponentStruct ShovelerComponent; // forward declaration: component.h

extern const char *const shovelerComponentTypeIdMaterial;

typedef enum {
	SHOVELER_COMPONENT_MATERIAL_TYPE_COLOR,
	SHOVELER_COMPONENT_MATERIAL_TYPE_TEXTURE,
	SHOVELER_COMPONENT_MATERIAL_TYPE_PARTICLE,
	SHOVELER_COMPONENT_MATERIAL_TYPE_TILEMAP,
	SHOVELER_COMPONENT_MATERIAL_TYPE_CANVAS,
	SHOVELER_COMPONENT_MATERIAL_TYPE_TILE_SPRITE,
	SHOVELER_COMPONENT_MATERIAL_TYPE_TEXT,
} ShovelerComponentMaterialType;

typedef enum {
	/** A ShovelerComponentMaterialType specifying the type of this material. */
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_TYPE,
	/**
	 * If type is SHOVELER_COMPONENT_MATERIAL_TYPE_TEXTURE, a ShovelerMaterialTextureType that
	 * further specifies the type of the texture material.
	 */
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_TEXTURE_TYPE,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_TEXTURE,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_TEXTURE_SAMPLER,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_TILEMAP,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_CANVAS,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_COLOR,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_CANVAS_REGION_POSITION,
	SHOVELER_COMPONENT_MATERIAL_OPTION_ID_CANVAS_REGION_SIZE,
} ShovelerComponentMaterialOptionId;


ShovelerComponentType *shovelerComponentCreateMaterialType();
ShovelerMaterial *shovelerComponentGetMaterial(ShovelerComponent *component);

#endif
