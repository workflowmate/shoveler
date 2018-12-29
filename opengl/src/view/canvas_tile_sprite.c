#include <assert.h> // assert
#include <stdlib.h> // malloc free
#include <string.h> // memmove

#include "shoveler/view/canvas_tile_sprite.h"
#include "shoveler/view/tileset.h"
#include "shoveler/log.h"

typedef struct {
	ShovelerViewCanvasTileSpriteConfiguration configuration;
	ShovelerCanvasTileSprite *tileSprite;
} ComponentData;

static void assignConfiguration(ShovelerViewCanvasTileSpriteConfiguration *destination, const ShovelerViewCanvasTileSpriteConfiguration *source);
static void clearConfiguration(ShovelerViewCanvasTileSpriteConfiguration *configuration);
static bool activateComponent(ShovelerViewComponent *component, void *componentDataPointer);
static void deactivateComponent(ShovelerViewComponent *component, void *componentDataPointer);
static void freeComponent(ShovelerViewComponent *component, void *componentDataPointer);

bool shovelerViewEntityAddCanvasTileSprite(ShovelerViewEntity *entity, const ShovelerViewCanvasTileSpriteConfiguration *configuration)
{
	ShovelerViewComponent *component = shovelerViewEntityGetComponent(entity, shovelerViewCanvasTileSpriteComponentName);
	if(component != NULL) {
		shovelerLogWarning("Trying to add canvas tile sprite to entity %lld which already has canvas tile sprite, ignoring.", entity->entityId);
		return false;
	}

	ComponentData *componentData = malloc(sizeof(ComponentData));
	componentData->configuration.tilesetEntityId = 0;
	componentData->configuration.tilesetColumn = 0;
	componentData->configuration.tilesetRow = 0;
	componentData->configuration.position = shovelerVector2(0.0f, 0.0f);
	componentData->configuration.size = shovelerVector2(0.0f, 0.0f);
	componentData->tileSprite = NULL;

	assignConfiguration(&componentData->configuration, configuration);

	component = shovelerViewEntityAddComponent(entity, shovelerViewCanvasTileSpriteComponentName, componentData, activateComponent, deactivateComponent, freeComponent);
	assert(component != NULL);

	shovelerViewComponentAddDependency(component, componentData->configuration.tilesetEntityId, shovelerViewTilesetComponentName);

	shovelerViewComponentActivate(component);
	return true;
}

ShovelerCanvasTileSprite *shovelerViewEntityGetCanvasTileSprite(ShovelerViewEntity *entity)
{
	ShovelerViewComponent *component = shovelerViewEntityGetComponent(entity, shovelerViewCanvasTileSpriteComponentName);
	if(component == NULL) {
		return false;
	}

	ComponentData *componentData = component->data;
	return componentData->tileSprite;
}

const ShovelerViewCanvasTileSpriteConfiguration *shovelerViewEntityGetCanvasTileSpriteConfiguration(ShovelerViewEntity *entity)
{
	ShovelerViewComponent *component = shovelerViewEntityGetComponent(entity, shovelerViewCanvasTileSpriteComponentName);
	if(component == NULL) {
		return false;
	}

	ComponentData *componentData = component->data;
	return &componentData->configuration;
}

bool shovelerViewEntityUpdateCanvasTileSprite(ShovelerViewEntity *entity, const ShovelerViewCanvasTileSpriteConfiguration *configuration)
{
	ShovelerViewComponent *component = shovelerViewEntityGetComponent(entity, shovelerViewCanvasTileSpriteComponentName);
	if(component == NULL) {
		shovelerLogWarning("Trying to update canvas tile sprite of entity %lld which does not have a canvas tile sprite, ignoring.", entity->entityId);
		return false;
	}

	ComponentData *componentData = component->data;

	shovelerViewComponentDeactivate(component);

	if(!shovelerViewComponentRemoveDependency(component, componentData->configuration.tilesetEntityId, shovelerViewCanvasTileSpriteComponentName)) {
		return false;
	}

	assignConfiguration(&componentData->configuration, configuration);

	shovelerViewComponentAddDependency(component, componentData->configuration.tilesetEntityId, shovelerViewCanvasTileSpriteComponentName);

	shovelerViewComponentActivate(component);

	shovelerViewComponentUpdate(component);
	return true;
}

bool shovelerViewEntityRemoveCanvasTileSprite(ShovelerViewEntity *entity)
{
	ShovelerViewComponent *component = shovelerViewEntityGetComponent(entity, shovelerViewCanvasTileSpriteComponentName);
	if(component == NULL) {
		shovelerLogWarning("Trying to remove canvas tile sprite from entity %lld which does not have a canvas tile sprite, ignoring.", entity->entityId);
		return false;
	}

	return shovelerViewEntityRemoveComponent(entity, shovelerViewCanvasTileSpriteComponentName);
}

static void assignConfiguration(ShovelerViewCanvasTileSpriteConfiguration *destination, const ShovelerViewCanvasTileSpriteConfiguration *source)
{
	clearConfiguration(destination);

	destination->tilesetEntityId = source->tilesetEntityId;
	destination->tilesetColumn = source->tilesetColumn;
	destination->tilesetRow = source->tilesetRow;
	destination->position = source->position;
	destination->size = source->size;
}

static void clearConfiguration(ShovelerViewCanvasTileSpriteConfiguration *configuration)
{
	configuration->tilesetEntityId = 0;
	configuration->tilesetColumn = 0;
	configuration->tilesetRow = 0;
	configuration->position = shovelerVector2(0.0f, 0.0f);
	configuration->size = shovelerVector2(0.0f, 0.0f);
}

static bool activateComponent(ShovelerViewComponent *component, void *componentDataPointer)
{
	ComponentData *componentData = componentDataPointer;

	ShovelerViewEntity *tilesetEntityId = shovelerViewGetEntity(component->entity->view, componentData->configuration.tilesetEntityId);
	assert(tilesetEntityId != NULL);
	ShovelerTileset *tileset = shovelerViewEntityGetTileset(tilesetEntityId);
	assert(tileset != NULL);

	componentData->tileSprite = malloc(sizeof(ShovelerCanvasTileSprite));
	componentData->tileSprite->tileset = tileset;
	componentData->tileSprite->tilesetColumn = componentData->configuration.tilesetColumn;
	componentData->tileSprite->tilesetRow = componentData->configuration.tilesetRow;
	componentData->tileSprite->position = componentData->configuration.position;
	componentData->tileSprite->size = componentData->configuration.size;

	return true;
}

static void deactivateComponent(ShovelerViewComponent *component, void *componentDataPointer)
{
	ComponentData *componentData = componentDataPointer;

	free(componentData->tileSprite);
}

static void freeComponent(ShovelerViewComponent *component, void *componentDataPointer)
{
	ComponentData *componentData = componentDataPointer;

	free(componentData->tileSprite);

	clearConfiguration(&componentData->configuration);
	free(componentData);
}
