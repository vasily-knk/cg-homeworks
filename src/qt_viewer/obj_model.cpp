#include "stdafx.h"
#include "obj_model.h"

obj_model::obj_model()
{

}

obj_model::obj_model(const string &filename)
{
    load(filename);
}

obj_model::obj_model(std::istream &stream)
{
    load(stream);
}

void obj_model::load(const string &filename)
{
    ifstream stream;
    stream.exceptions(ifstream::badbit);
    stream.open(filename);
    load(stream);
}

void obj_model::load(std::istream &stream)
{
    verts_.clear();
    indices_.clear();

    string str;
    while (std::getline(stream, str))
    {
        std::stringstream ss(str);
        string cmd;

        ss >> cmd;

        const size_t pos = ss.tellg();
        string substr(str.substr(pos + 1));
        if (cmd == "v")
            parse_vertex(substr);
        else if (cmd == "f")
            parse_face(substr);
    }
}

void obj_model::parse_vertex(const string &str)
{
    vec3_t vert;
    std::stringstream ss(str);
    ss >> vert.x >> vert.y >> vert.z;
    verts_.push_back(vert);
}

namespace 
{
    inline bool is_slash(const char c)
    {
        return (c == '/');
    }
}

void obj_model::parse_face(const string &str)
{
    vector<string> blocks;
    boost::split(blocks, str, boost::is_space(), boost::token_compress_on);

    int counter = 0;
    
    BOOST_FOREACH(const string &block, blocks)
    {
        vector<string> numbers;
        boost::split(numbers, block, is_slash);

        index_t index = boost::lexical_cast<index_t>(numbers.front());
        indices_.push_back(index - 1);

        ++counter;
    }

    if (counter != 3)
        throw std::runtime_error("Only faces with 3 vertices are supported");
}
