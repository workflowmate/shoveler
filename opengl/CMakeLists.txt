set(SHOVELER_OPENGL_SRC
	src/camera/identity.c
	src/camera/perspective.c
	src/drawable/cube.c
	src/drawable/quad.c
	src/drawable/point.c
	src/filter/depth_texture_gaussian.c
	src/image/png.c
	src/image/ppm.c
	src/light/point.c
	src/light/spot.c
	src/material/color.c
	src/material/depth.c
	src/material/depth_texture_gaussian_filter.c
	src/material/particle.c
	src/material/screenspace_texture.c
	src/material/texture.c
	src/camera.c
	src/controller.c
	src/framebuffer.c
	src/game.c
	src/global.c
	src/image.c
	src/input.c
	src/material.c
	src/model.c
	src/opengl.c
	src/sampler.c
	src/scene.c
	src/shader.c
	src/shader_program.c
	src/texture.c
	src/uniform.c
	src/uniform_attachment.c
	src/uniform_map.c
	include/shoveler/camera/identity.h
	include/shoveler/camera/perspective.h
	include/shoveler/drawable/cube.h
	include/shoveler/drawable/point.h
	include/shoveler/drawable/quad.h
	include/shoveler/filter/depth_texture_gaussian.h
	include/shoveler/material/color.h
	include/shoveler/material/depth.h
	include/shoveler/material/depth_texture_gaussian_filter.h
	include/shoveler/light/point.h
	include/shoveler/light/spot.h
	include/shoveler/material/particle.h
	include/shoveler/material/screenspace_texture.h
	include/shoveler/material/texture.h
	include/shoveler/camera.h
	include/shoveler/controller.h
	include/shoveler/drawable.h
	include/shoveler/filter.h
	include/shoveler/framebuffer.h
	include/shoveler/game.h
	include/shoveler/global.h
	include/shoveler/image.h
	include/shoveler/image/png.h
	include/shoveler/image/ppm.h
	include/shoveler/input.h
	include/shoveler/light.h
	include/shoveler/material.h
	include/shoveler/model.h
	include/shoveler/opengl.h
	include/shoveler/sampler.h
	include/shoveler/scene.h
	include/shoveler/shader.h
	include/shoveler/shader_program.h
	include/shoveler/texture.h
	include/shoveler/uniform_attachment.h
	include/shoveler/uniform.h
	include/shoveler/uniform_map.h
)

add_library(shoveler_opengl ${SHOVELER_OPENGL_SRC})
set_property(TARGET shoveler_opengl PROPERTY C_STANDARD 99)

target_include_directories(shoveler_opengl
	PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PUBLIC $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_link_libraries(shoveler_opengl shoveler_base glad glfw png_static zlibstatic)