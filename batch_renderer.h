#pragma once
#include <vector>
typedef unsigned int uint;

/*

creates vector of batched triangles

*/
std::vector<float> batch_vertices(std::pair<const float*,uint> vertex_texture_packs[] , size_t attrib_size, size_t vert_count, size_t count);