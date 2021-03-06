#ifndef SHOVELER_COMPONENT_SPRITE_H
#define SHOVELER_COMPONENT_SPRITE_H

typedef struct ShovelerComponentTypeStruct ShovelerComponentType; // forward declaration: component.h
typedef struct ShovelerComponentStruct ShovelerComponent; // forward declaration: component.h
typedef struct ShovelerSpriteStruct ShovelerSprite; // forward declaration: sprite.h

extern const char *const shovelerComponentTypeIdSprite;

typedef enum {
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_POSITION,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_POSITION_MAPPING_X,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_POSITION_MAPPING_Y,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_ENABLE_COLLIDER,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_CANVAS,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_LAYER,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_SIZE,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_TEXT_SPRITE,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_TILE_SPRITE,
	SHOVELER_COMPONENT_SPRITE_OPTION_ID_TILEMAP_SPRITE,
} ShovelerComponentSpriteOptionId;

ShovelerComponentType *shovelerComponentCreateSpriteType();
ShovelerSprite *shovelerComponentGetSprite(ShovelerComponent *component);

#endif
