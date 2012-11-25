#include "stdafx.h"
#include "model.h"

model::model()
{

}

model::model(const string &filename)
{
    load_obj(filename);
}

model::model(std::istream &stream)
{
    load_obj(stream);
}

void model::load_sphere(float radius, int segments)
{
    load_sphere_verts(radius, segments);
    load_sphere_indices(radius, segments);
}

void model::load_sphere_verts(float radius, int segments)
{
    const float PI = 3.1415926f;
    const float deltax = 2.0 * PI / segments;
    const float deltay = PI / segments;

    verts_.clear();
    verts_.push_back(vec3_t(0, -radius, 0));

    float angley = -PI / 2 + deltay;
    for (int y = 1; y < segments - 1; ++y, angley += deltay)
    {
        vec3_t vert;
        vert.y = sin(angley) * radius;
        const float projection = cos(angley) * radius;

        float anglex = 0.0f;
        for (int x = 0; x < segments; ++x, anglex += deltax)
        {
            vert.x = sin(anglex) * projection;
            vert.z = cos(anglex) * projection;
            verts_.push_back(vert);
        }
    }

    verts_.push_back(vec3_t(0, radius, 0));
}

void model::load_sphere_indices(float radius, int segments)
{
    indices_.clear();

/*
    for (int x = 0; x < segments; ++x)
    {
        indices_.push_back(0);
        indices_.push_back(x + 1);
        indices_.push_back(((x + 1) % segments) + 1);
    }*/

    int pos = segments * 4 + 1;
    for (int y = 3; y < segments -1 ; ++y, pos += segments)
    {
        for (int x = 0; x < segments; ++x)
        {
            const int x1 = (x + 1) % segments;
            indices_.push_back(pos + x);
            indices_.push_back(pos + x  - segments);
            indices_.push_back(pos + x1 - segments);

            indices_.push_back(pos + x1 - segments);
            indices_.push_back(pos + x1);
            indices_.push_back(pos + x);
        }
    }
}

void model::load_triangle()
{
    verts_.clear();
    verts_.push_back(vec3_t(-1, -1, 0));
    verts_.push_back(vec3_t( 0,  1, 0));
    verts_.push_back(vec3_t( 1, -1, 0));
    indices_.clear();
    indices_.push_back(0);
    indices_.push_back(1);
    indices_.push_back(2);
}
