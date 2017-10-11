#ifndef SHOVELER_CAMERA_PERSPECTIVE_H
#define SHOVELER_CAMERA_PERSPECTIVE_H

#include <shoveler/camera.h>
#include <shoveler/controller.h>
#include <shoveler/types.h>

typedef struct {
	ShovelerCamera camera;
	ShovelerVector3 up;
	ShovelerVector3 direction;
	ShovelerMatrix perspective;
	ShovelerController *controller;
} ShovelerCameraPerspective;

ShovelerCamera *shovelerCameraPerspectiveCreate(ShovelerVector3 position, ShovelerVector3 direction, ShovelerVector3 up, float fieldOfViewY, float aspectRatio, float nearClippingPlane, float farClippingPlane);
void shovelerCameraPerspectiveAttachController(ShovelerCamera *camera, ShovelerController *controller);
void shovelerCameraPerspectiveDetachController(ShovelerCamera *camera, ShovelerController *controller);

#endif