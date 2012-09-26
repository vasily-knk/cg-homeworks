#pragma once

struct vec3_t
{
    float x, y, z;
};

struct face_t
{
    vector<int> verts;
};

class obj_model
{
public:
    obj_model();
    explicit obj_model(const string &filename);
    explicit obj_model(std::istream &stream);

public:
    void load(const string &filename);
    void load(std::istream &stream);

private:
    void parse_vertex(const string &str);
    void parse_face(const string &str);

private:
    vector<vec3_t> verts_;
    vector<face_t> faces_;
};