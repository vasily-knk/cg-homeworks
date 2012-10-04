#pragma once

struct vec3_t
{
    float x, y, z;
};

class obj_model
{
public:
    typedef int index_t;
public:
    obj_model();
    explicit obj_model(const string &filename);
    explicit obj_model(std::istream &stream);

public:
    void load(const string &filename);
    void load(std::istream &stream);

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