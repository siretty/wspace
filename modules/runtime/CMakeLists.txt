
wspace_module(
    runtime

    SOURCE_DIRECTORY src
    COMPONENT_BASE wspace/runtime

    COMPONENT position
    COMPONENT renderer

    LINK_MODULE support
    LINK_MODULE gfx

    LINK_PUBLIC glad
)
