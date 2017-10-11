#include <stdlib.h> // malloc, free

#include "shoveler/camera/identity.h"
#include "shoveler/filter/depth_texture_gaussian.h"
#include "shoveler/light/spot.h"
#include "shoveler/material/depth.h"
#include "shoveler/scene.h"

static void updatePosition(void *spotlightPointer, ShovelerVector3 position);
static ShovelerVector3 getPosition(void *spotlightPointer);
static int renderSpotLight(void *spotlightPointer, ShovelerScene *scene, ShovelerCamera *camera, ShovelerFramebuffer *framebuffer);
static void freeSpotLight(void *spotlightPointer);

ShovelerLightSpotShared *shovelerLightSpotSharedCreate(int width, int height, GLsizei samples, float ambientFactor, float exponentialFactor, ShovelerVector3 color) {
	ShovelerLightSpotShared *shared = malloc(sizeof(ShovelerLightSpotShared));
	shared->shadowMapSampler = shovelerSamplerCreate(true, true);
	shared->depthFramebuffer = shovelerFramebufferCreateDepthOnly(width, height, samples);
	shared->depthMaterial = shovelerMaterialDepthCreate();
	shared->depthFilter = shovelerFilterDepthTextureGaussianCreate(width, height, samples, exponentialFactor);
	shared->ambientFactor = ambientFactor;
	shared->exponentialFactor = exponentialFactor;
	shared->color = color;
	return shared;
}

ShovelerLightSpot *shovelerLightSpotCreateWithShared(ShovelerCamera *camera, ShovelerLightSpotShared *shared, bool managedShared)
{
	ShovelerLightSpot *spotlight = malloc(sizeof(ShovelerLightSpot));
	spotlight->light.data = spotlight;
	spotlight->light.updatePosition = updatePosition;
	spotlight->light.getPosition = getPosition;
	spotlight->light.render = renderSpotLight;
	spotlight->light.freeData = freeSpotLight;
	spotlight->light.uniforms = shovelerUniformMapCreate();
	spotlight->camera = camera;
	spotlight->shared = shared;
	spotlight->manageShared = managedShared;

	shovelerUniformMapInsert(spotlight->light.uniforms, "isExponentialLiftedShadowMap", shovelerUniformCreateInt(1));
	shovelerUniformMapInsert(spotlight->light.uniforms, "lightAmbientFactor", shovelerUniformCreateFloat(spotlight->shared->ambientFactor));
	shovelerUniformMapInsert(spotlight->light.uniforms, "lightExponentialShadowFactor", shovelerUniformCreateFloat(spotlight->shared->exponentialFactor));
	shovelerUniformMapInsert(spotlight->light.uniforms, "lightColor", shovelerUniformCreateVector3Pointer(&spotlight->shared->color));
	shovelerUniformMapInsert(spotlight->light.uniforms, "lightPosition", shovelerUniformCreateVector3Pointer(&spotlight->camera->position));
	shovelerUniformMapInsert(spotlight->light.uniforms, "lightView", shovelerUniformCreateMatrixPointer(&spotlight->camera->view));
	shovelerUniformMapInsert(spotlight->light.uniforms, "lightProjection", shovelerUniformCreateMatrixPointer(&spotlight->camera->projection));
	shovelerUniformMapInsert(spotlight->light.uniforms, "shadowMap", shovelerUniformCreateTexture(spotlight->shared->depthFilter->outputTexture, spotlight->shared->shadowMapSampler));

	return spotlight;
}

void shovelerLightSpotSharedFree(ShovelerLightSpotShared *shared)
{
	if(shared == NULL) {
		return;
	}

	shovelerFilterFree(shared->depthFilter);
	shovelerMaterialFree(shared->depthMaterial);
	shovelerFramebufferFree(shared->depthFramebuffer);
	shovelerSamplerFree(shared->shadowMapSampler);

	free(shared);
}

static void updatePosition(void *spotlightPointer, ShovelerVector3 position)
{
	ShovelerLightSpot *spotlight = (ShovelerLightSpot *) spotlightPointer;
	spotlight->camera->position = position;
	shovelerCameraUpdateView(spotlight->camera);
}

static ShovelerVector3 getPosition(void *spotlightPointer)
{
	ShovelerLightSpot *spotlight = (ShovelerLightSpot *) spotlightPointer;
	return spotlight->camera->position;
}

static int renderSpotLight(void *spotlightPointer, ShovelerScene *scene, ShovelerCamera *camera, ShovelerFramebuffer *framebuffer)
{
	ShovelerLightSpot *spotlight = (ShovelerLightSpot *) spotlightPointer;

	int rendered = 0;

	// render depth map
	shovelerFramebufferUse(spotlight->shared->depthFramebuffer);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	rendered += shovelerSceneRenderModels(scene, spotlight->camera, NULL, spotlight->shared->depthMaterial, false, false, true);

	// filter depth map
	rendered += shovelerFilterRender(spotlight->shared->depthFilter, spotlight->shared->depthFramebuffer->depthTarget);

	// render additive light to scene
	rendered += shovelerSceneRenderPass(scene, camera, &spotlight->light, framebuffer, SHOVELER_SCENE_RENDER_MODE_ADDITIVE_LIGHT);

	return rendered;
}

static void freeSpotLight(void *spotlightPointer)
{
	ShovelerLightSpot *spotlight = (ShovelerLightSpot *) spotlightPointer;

	if(spotlight == NULL) {
		return;
	}

	shovelerCameraFree(spotlight->camera);
	shovelerUniformMapFree(spotlight->light.uniforms);

	if(spotlight->manageShared) {
		shovelerLightSpotSharedFree(spotlight->shared);
	}

	free(spotlight);
}
