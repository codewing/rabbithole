//
// Created by codewing on 07.11.18.
//

#include "SimpleRenderer.hpp"

SimpleRenderer::SimpleRenderer(SDL_Window* window) : r{window}  {
}

void SimpleRenderer::render() {
    sre::RenderPass rp = sre::RenderPass::create().build();
    rp.drawLines({{0,0,0},{1,1,1}});
    r.swapWindow();
}
