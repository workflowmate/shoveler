#include <stdlib.h> // malloc free

#include "shoveler/collider.h"

ShovelerColliders *shovelerCollidersCreate()
{
	ShovelerColliders *colliders = malloc(sizeof(ShovelerColliders));
	colliders->colliders2 = g_hash_table_new(g_direct_hash, g_direct_equal);
	colliders->colliders3 = g_hash_table_new(g_direct_hash, g_direct_equal);
	return colliders;
}

bool shovelerCollidersAddCollider2(ShovelerColliders *colliders, ShovelerCollider2 *collider)
{
	return g_hash_table_add(colliders->colliders2, (gpointer) collider);
}

bool shovelerCollidersAddCollider3(ShovelerColliders *colliders, ShovelerCollider3 *collider)
{
	return g_hash_table_add(colliders->colliders3, (gpointer) collider);
}

bool shovelerCollidersRemoveCollider2(ShovelerColliders *colliders, ShovelerCollider2 *collider)
{
	return g_hash_table_remove(colliders->colliders2, (gpointer) collider);
}

bool shovelerCollidersRemoveCollider3(ShovelerColliders *colliders, ShovelerCollider3 *collider)
{
	return g_hash_table_remove(colliders->colliders3, (gpointer) collider);
}

ShovelerCollider2 *shovelerCollidersIntersect2(ShovelerColliders *colliders, const ShovelerBoundingBox2 *boundingBox)
{
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, colliders->colliders2);
	ShovelerCollider2 *collider;
	while(g_hash_table_iter_next(&iter, (gpointer *) &collider, NULL)) {
		if(shovelerBoundingBox2Intersect(boundingBox, &collider->boundingBox)) {
			if(collider->intersect(collider, boundingBox)) {
				return collider;
			}
		}
	}

	return NULL;
}

ShovelerCollider3 *shovelerCollidersIntersect3(ShovelerColliders *colliders, const ShovelerBoundingBox3 *boundingBox)
{
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, colliders->colliders2);
	ShovelerCollider3 *collider;
	while(g_hash_table_iter_next(&iter, (gpointer *) &collider, NULL)) {
		if(shovelerBoundingBox3Intersect(boundingBox, &collider->boundingBox)) {
			if(collider->intersect(collider, boundingBox)) {
				return collider;
			}
		}
	}

	return NULL;
}

void shovelerCollidersFree(ShovelerColliders *colliders)
{
	g_hash_table_destroy(colliders->colliders2);
	g_hash_table_destroy(colliders->colliders3);
	free(colliders);
}