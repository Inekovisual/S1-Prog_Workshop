#include <sil/sil.hpp>
#include "random.hpp"
#include <algorithm>

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
        color = glm::vec3(1.0f) - color;
    }
}

void color_gradient(sil::Image &image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            float valeur = float(x) / (image.width() - 1);

            image.pixel(x, y) = glm::vec3(valeur);
        }
    }
}

void mirror(sil::Image &image)
{
    for (int x = 0; x < image.width() / 2; x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int mirrored_x = image.width() - (x + 1);
            std::swap(image.pixel(mirrored_x, y), image.pixel(x, y));
        }
    }
}

void noisy_image(sil::Image &image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            if (true_with_probability(0.3))
            {
                image.pixel(x, y) = glm::vec3(random_float(0, 1), random_float(0, 1), random_float(0, 1));
            }
        }
    }
}

sil::Image rotation(sil::Image &image)
{
    sil::Image new_image{image.height(), image.width()};

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int new_x = image.height() - 1 - y;
            int new_y = x;
            new_image.pixel(new_x, new_y) = image.pixel(x, y);
        }
    }

    return new_image;
}

sil::Image rgb_split(const sil::Image &image)
{
    sil::Image new_image{image.width(), image.height()};
    int offset = 20;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int x_red = std::max(0, x - offset);
            int x_blue = std::min(x + offset, image.width() - 1);

            float r = image.pixel(x_red, y).r;
            float g = image.pixel(x, y).g;
            float b = image.pixel(x_blue, y).b;

            new_image.pixel(x, y) = glm::vec3(r, g, b);
        }
    }

    return new_image;
}

void brightness(sil::Image &image)
{
    float power = 0.5;

    for (glm::vec3 &color : image.pixels())
    {
        color = glm::pow(color, glm::vec3(power));
    }
}

void disk(sil::Image &image)
{
    float radius = 100;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            glm::vec2 position{x, y};
            float distance = glm::length(position - glm::vec2(image.width() / 2, image.height() / 2));

            if (distance <= radius)
            {
                image.pixel(x, y) = glm::vec3(1);
            }
            else
            {
                image.pixel(x, y) = glm::vec3(0);
            }
        }
    }
}

void circle(sil::Image &image)
{
    float radius = 100;
    float thickness = 5;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            glm::vec2 position{x, y};
            float distance = glm::length(position - glm::vec2(image.width() / 2, image.height() / 2));

            if (radius - thickness <= distance && distance <= radius)
            {
                image.pixel(x, y) = glm::vec3(1);
            }
            else
            {
                image.pixel(x, y) = glm::vec3(0);
            }
        }
    }
}

void animation(sil::Image &image)
{
    float radius = 100;

    for (int center = 0; center < image.width(); center += 20)
    {
        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
                glm::vec2 position{x, y};
                float distance = glm::length(position - glm::vec2(center, image.height() / 2));

                if (distance <= radius)
                {
                    image.pixel(x, y) = glm::vec3(1);
                }
                else
                {
                    image.pixel(x, y) = glm::vec3(0);
                }
            }
        }

        int frame_number = center / 20;
        image.save("output/animation/animation" + std::to_string(frame_number) + ".png");
    }
}

void rosace(sil::Image &image)
{
    float radius = 100;
    float thickness = 5;
    float angle = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
                glm::vec2 position{x, y};
                float distance = glm::length(position - glm::vec2(image.width() / 2 + radius * cos(glm::radians(angle)), image.height() / 2 + radius * sin(glm::radians(angle))));

                if (radius - thickness <= distance && distance <= radius)
                {
                    image.pixel(x, y) = glm::vec3(1);
                }
            }
        }

        angle += 60;
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
        sil::Image image{300, 200};
        color_gradient(image);
        image.save("output/color_gradient.png");
    }

    {
        sil::Image image{"images/logo.png"};
        mirror(image);
        image.save("output/mirror.png");
    }

    {
        sil::Image image{"images/logo.png"};
        noisy_image(image);
        image.save("output/noisy_image.png");
    }

    {
        sil::Image image{"images/logo.png"};
        sil::Image new_image = rotation(image);
        new_image.save("output/rotation.png");
    }

    {
        sil::Image image{"images/logo.png"};
        sil::Image new_image = rgb_split(image);
        new_image.save("output/rgb_split.png");
    }

    {
        sil::Image image{"images/photo.jpg"};
        brightness(image);
        image.save("output/brightness.jpg");
    }

    {
        sil::Image image{500, 500};
        disk(image);
        image.save("output/disk.png");
    }

    {
        sil::Image image{500, 500};
        circle(image);
        image.save("output/circle.png");
    }

    {
        sil::Image image{500, 500};
        animation(image);
    }

    {
        sil::Image image{"output/circle.png"};
        rosace(image);
        image.save("output/rosace.png");
    }
}