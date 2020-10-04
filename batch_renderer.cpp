#include "batch_renderer.h"
#include <iostream>


std::vector<float> batch_vertices(std::pair<const float*, uint> vertex_texture_packs[], size_t attrib_size, size_t vert_count, size_t count)
{
	std::vector<float> data(count * (attrib_size + 1) * vert_count);


	auto* ptr = &vertex_texture_packs[0];
	//iterate through all meshes
	for (int i = 0; i < count; ++i)
	{
		const float* dataptr = ptr->first;
		//iterate through all vertices in a mesh
		for (int j = 0; j < vert_count; ++j)
		{
			//iterate through every float attribute in a vertex
			for (int k = 0; k < attrib_size; ++k)
			{
				data.push_back(*dataptr);
				++dataptr;
			}
			data.push_back(ptr->second);
			//data.push_back(ptr->second.second);
		}
		++ptr;
	}
	return data;
}
