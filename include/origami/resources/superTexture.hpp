#ifndef ORIGAMI_RESOURCES_SUPERTEXTURE_HPP
#define ORIGAMI_RESOURCES_SUPERTEXTURE_HPP

#include "origami/components/program.hpp"
#include <utility>
#include <vector>
#include <glad/gl.h>

namespace origami::resources {
class SuperTexture {
    std::vector<bool> blocks;
    int bX, bY;
    int fullWidth, fullHeight;
    float relWidth, relHeight;
    int blocksCount;
public:
    GLuint texHandle;
    int bWidth;
    int bHeight;
    /**
   * @brief Construct a super texture (for allocating different sub-textures within)
   *
   * @param blockWidth How wide each sub-block is
   * @param blockHeight How tall each sub-block is
   * @param blocksX How many blocks wide the super-tex should be
   * @param blockxY How many blocks tall the super-tex should be
   */
    SuperTexture(int blockWidth, int blockHeight, int blocksX, int blockxY);

    /**
   * @brief Allocate a texture
   *
   * @returns A (id, (x, y)) structure
   */
    std::pair<int, std::pair<int, int>> Allocate();
    /**
   * @brief Deallocates the given block by ID
   *
   * @param id The index of the block to deallocate
   */
    void Deallocate(int id);

    /**
   * @brief Binds the texture (you need to bind all the TxOffsLocations yourself!)
   */
    void BindRaw();

    void Activate();
    
    // /**
    //  * @brief Binds the texture and sets the relevant shader uniforms
    //  *
    //  * @param id The id of the block to bind
    //  * @param program The program to be used to render the thing
    //  */
    // void Bind(int id, components::Program program);

    /**
     * @brief Binds the texture and sets the relevant shader uniforms
     *
     * @param x The x-coordinate of the block to be bound
     * @param y The y-coordinate of the block to be bound
     * @param program The program to be used to render the thing
     */
    void Bind(int x, int y, components::Program program);
};
}

#endif // !ORIGAMI_RESOURCES_SUPERTEXTURE_HPP
