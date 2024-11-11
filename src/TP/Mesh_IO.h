#pragma once

#include "Mesh.h"
using edges = std::pair<unsigned, unsigned>;
using edges_face = std::pair<unsigned, unsigned>;
struct PairHash
{
    std::size_t operator()(const std::pair<unsigned, unsigned> &pair) const
    { // Simple composite hash
        return ((std::hash<unsigned>()(pair.first) << 1) + std::hash<unsigned>()(pair.second));
    }
};

// Retourne le sommet ne correspondant à aucun de ceux du bord
//"Legacy Function"
inline int return_opposite_vertices(const edges &edge, std::vector<unsigned> candidates)
{
    int i = 0;
    for (const auto &vert : candidates)
    {
        if (vert == edge.first || vert == edge.second)
        {
            i++;
            continue;
        }
        else
        {
            break;
        }
    }

    return i;
}


void map_edge(std::vector<Faces> &faces, std::vector<Vertices> &vertices);
void insertionSort(int arr[], int n);





Mesh load_mesh_faceless(const char *filename, bool choice);

Mesh load_mesh(const char *filename);

// TODO More than obj ?
// TODO: const Mesh&
bool write_mesh(const char *filename, Mesh &mesh, bool normal = true, bool curvature = false, const std::vector<float> &texture_coordinate = {})
;