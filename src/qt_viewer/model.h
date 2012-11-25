#pragma once

struct vec3_t
{
    vec3_t () 
    {
   
    };

    vec3_t (float x, float y, float z)
        : x(x), y(y), z(z)
    {

    }

    float x, y, z;
};

class model
{
public:
    typedef int index_t;
public:
    model();
    explicit model(const string &filename);
    explicit model(std::istream &stream);

public:
    void load_obj(const string &filename);
    void load_obj(std::istream &stream);

    void load_sphere(float radius, int segments);
    void load_triangle();

private:
    void load_sphere_verts(float radius, int segments);
    void load_sphere_indices(float radius, int segments);

public:
    const vector<vec3_t> &get_verts() const
    {
        return verts_;
    }

    const vector<index_t> &get_indices() const
    {
        return indices_;
    }

private:
    void parse_vertex(const string &str);
    void parse_face(const string &str);

private:
    vector<vec3_t> verts_;
    vector<index_t> indices_;
};