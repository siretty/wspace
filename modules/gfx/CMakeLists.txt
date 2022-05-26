
wspace_module(
    gfx

    SOURCE_DIRECTORY src
    COMPONENT_BASE wspace/gfx

    COMPONENT ogl/buffer
    COMPONENT ogl/array
    COMPONENT ogl/shader
    COMPONENT ogl/program
    COMPONENT ogl/object

    COMPONENT asteroid_renderer
    COMPONENT ship_renderer
    COMPONENT station_renderer

    COMPONENT perspective_camera

    LINK_MODULE support

    LINK_PUBLIC glad
)
