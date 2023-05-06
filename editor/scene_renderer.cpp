#include "scene_renderer.h"

auto Tobot::Editor::sceneRendererMain(SDL_Renderer * renderer, ImVec2 scenePosition, ImVec2 sceneWindowSize,
                                      SDL_Texture * sceneTexture) -> void {
    // Drawing a texture in the scene window for testing - This texture should be the whole scene later

    // To place the texture in the center of the screen we need to know the position of the size of the scene window
    SDL_Rect rect = {(int)scenePosition.x, (int)scenePosition.y, (int)sceneWindowSize.x, (int)sceneWindowSize.y};
    SDL_RenderCopy(renderer, sceneTexture, NULL, &rect);
}