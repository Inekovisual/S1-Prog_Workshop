#include <sil/sil.hpp>

void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void channels_swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void black_and_white(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float black_and_white = (color.r + color.g + color.b) / 3;
        color = glm::vec3{black_and_white};
    }
}

void negative(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {

    }
}

void color_gradient(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {

    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"};
        keep_green_only(image);
        image.save("output/keep_green_only.png");
    }

    {
        sil::Image image{"images/logo.png"};
        channels_swap(image);
        image.save("output/channels_swap.png");
    }

    {
        sil::Image image{"images/logo.png"};     
        black_and_white(image);
        image.save("output/black_and_white.png");
    }

    {
        sil::Image image{"images/logo.png"};
        negative(image);
        image.save("output/negative.png");
    }

    {
        sil::Image image{"images/logo.png"};
        color_gradient(image);
        image.save("output/color_gradient.png");
    }
}