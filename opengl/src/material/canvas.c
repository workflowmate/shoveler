#include <stdlib.h> // malloc, free

#include "shoveler/material/canvas.h"
#include "shoveler/canvas.h"
#include "shoveler/light.h"
#include "shoveler/log.h"
#include "shoveler/model.h"
#include "shoveler/scene.h"

typedef struct {
	ShovelerMaterial *material;
	ShovelerCanvas *activeCanvas;
} MaterialData;

static bool render(ShovelerMaterial *material, ShovelerScene *scene, ShovelerCamera *camera, ShovelerLight *light, ShovelerModel *model, ShovelerRenderState *renderState);
static void freeTilemap(ShovelerMaterial *material);

ShovelerMaterial *shovelerMaterialCanvasCreate()
{
	MaterialData *materialData = malloc(sizeof(MaterialData));
	materialData->material = shovelerMaterialCreateUnmanaged(0);
	materialData->material->data = materialData;
	materialData->material->render = render;
	materialData->material->freeData = freeTilemap;
	materialData->activeCanvas = NULL;

	return materialData->material;
}

void shovelerMaterialCanvasSetActive(ShovelerMaterial *material, ShovelerCanvas *canvas)
{
	MaterialData *materialData = material->data;
	materialData->activeCanvas = canvas;
}

static bool render(ShovelerMaterial *material, ShovelerScene *scene, ShovelerCamera *camera, ShovelerLight *light, ShovelerModel *model, ShovelerRenderState *renderState)
{
	MaterialData *materialData = material->data;

	if(materialData->activeCanvas == NULL) {
		shovelerLogWarning("Failed to render canvas material %p without an active canvas.", material);
		return false;
	}

	return shovelerCanvasRender(materialData->activeCanvas, scene, camera, light, model, renderState);
}

static void freeTilemap(ShovelerMaterial *material)
{
	MaterialData *materialData = material->data;
	free(materialData);
}
