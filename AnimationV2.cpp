#include "AnimationV2.h"

AnimationV2::AnimationV2(float lenght, std::vector<AnimFrame> frames)
    : lenght(lenght), frames(frames) {
}

void AnimationV2::Update(float deltaTime) {
    time += deltaTime;
}

sf::Texture AnimationV2::GetTexture() {
    if (frames.empty()) {
        return sf::Texture(); // Return empty texture if no frames
    }

    while (time > lenght) {
        time -= lenght;
    }

    for (const auto& frame : frames) {
        if (time >= frame.time) {
            return frame.texture;
        }
    }

    return frames[0].texture; // Return first frame's texture if no match
}