#pragma once
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>
#include "MeshHelper.h"

#include <queue>
#include <set>
// Pre_allocated efault Variables
constexpr float common_time_step = 0.05;
struct Faces;
struct Mesh;

struct Edges
{
    unsigned v1, v2;
    unsigned f1, f2;
    Edges(const unsigned &vc1, const unsigned &vc2, const unsigned &fc1, const unsigned &fc2) : v1(vc1), v2(vc2)
    {
        bool face = fc1 > fc2;
        f1 = face ? fc1 : fc2;
        f2 = face ? fc2 : fc1;
    }

    Edges(const unsigned &vc1, const unsigned &vc2) : v1(vc1), v2(vc2), f1(0), f2(0)
    {
        bool vertex = vc1 > vc2;
        v1 = vertex ? vc1 : vc2;
        v2 = vertex ? vc2 : vc1;
    }

    friend std::ostream &operator<<(std::ostream &os, const Edges &edge_info)
    {
        os << "Edges: " << edge_info.v1
           << " " << edge_info.v2 << " Face: " << edge_info.f1
           << "  " << edge_info.f2 << std::endl;
        return os;
    }

    bool contains(unsigned int indices)
    {
        if (v1 == indices)
        {
            return true;
        }
        if (v2 == indices)
        {
            return true;
        }
        return false;
    }

    bool operator==(const Edges &rhs) const
    {
        return (v1 == rhs.v1 && v2 == rhs.v2) || (v1 == rhs.v2 && v1 == rhs.v2);
    };
    bool operator!=(const Edges &rhs) const
    {
        return !(*this == rhs);
    }

    struct Edgeshash
    {
        std::size_t operator()(const Edges &edge) const
        {
            unsigned hashv1 = edge.v1;
            unsigned hashv2 = edge.v2;

            if (hashv1 <= hashv2)
            {
                std::swap(hashv1, hashv2);
            }

            return (std::hash<unsigned int>()(hashv1) +
                    (std::hash<unsigned int>()(hashv2) << 1));
        }
    };
};
typedef std::unordered_set<Edges, Edges::Edgeshash> EdgeSet;

// positive = orientend clockwise

// using edges = std::pair<unsigned, unsigned>;
// using edges_face = std::pair<unsigned, unsigned>;

float in_triangle_test_2d(const Mesh &mesh, const unsigned int &face, const Vertices &point);
// FACE STRUCT
////////////////////////////////////////////////////////////////
struct Faces
{
    std::vector<unsigned> vertices; // Indices à utilisable uniquement par la classe Mesh
    std::vector<unsigned> neighbor; // Indices des faces voisines
    // Cosntructor
    Faces() = default;
    Faces(unsigned x, unsigned y, unsigned z) : vertices{x, y, z}, neighbor(3) {};
    Faces(unsigned x, unsigned y, unsigned z, const Faces &face) : vertices{x, y, z}, neighbor(face.neighbor) {

                                                                   };
    Faces(const Faces &face) : vertices(face.vertices), neighbor(face.neighbor) {};

    bool operator==(const Faces &rhs) const { return (vertices == rhs.vertices) && (neighbor == rhs.neighbor); };

    bool operator!=(const Faces &rhs) const
    {
        return !(*this == rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Faces &face)
    {
        os << "Vertices: " << face.vertices[0]
           << "  " << face.vertices[1]
           << " " << face.vertices[2] << " Neighbor: " << face.neighbor[0]
           << "  " << face.neighbor[1]
           << " " << face.neighbor[2] << std::endl;
        return os;
    }

    ~Faces() = default;
};

// Retourne l'indice local de sommet
inline unsigned return_local_indices(const Faces &face, unsigned glob_indices)
{
    unsigned i = 0;
    for (const auto &vert : face.vertices)
    {
        if (vert != glob_indices)
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

class Mesh;

// Some function make more sense in Mesh
std::vector<unsigned> travel(const Mesh &mesh, unsigned vertices_indices);
unsigned getNeighbors(const Faces &curr_face, unsigned &indice, std::function<unsigned(const unsigned &)> direction);
inline unsigned return_local_indices(const Faces &face, unsigned glob_indices);

class Mesh
{
private:
    std::vector<Vertices> vertices;
    std::vector<Faces> faces; // Itself imply infinite face
    std::vector<unsigned int> convex_hull;

public:
    Mesh() = default;
    Mesh(const std::vector<Vertices> &p_vertices) : vertices(p_vertices) {};
    Mesh(const std::vector<Vertices> &p_vertices, const std::vector<Faces> &p_faces) : vertices(p_vertices), faces(p_faces) {};
    Mesh(std::vector<Vertices> &&p_vertices, const std::vector<Faces> &&p_faces) : vertices(std::move(p_vertices)), faces(std::move(p_faces)) {};

    std::vector<Vertices> getVerticeArray() const
    {
        return vertices;
    }

    std::vector<unsigned int> getFacesArray() const
    {
        std::vector<unsigned int> faces_indices;
        for (const auto &face : faces)
        {
            faces_indices.emplace_back(face.vertices[0]);
            faces_indices.emplace_back(face.vertices[1]);
            faces_indices.emplace_back(face.vertices[2]);
        }
        return faces_indices;
    }

    Vertices getVertice(unsigned indice) const
    {
        return vertices[indice];
    }

    unsigned int &swapVerticeFace(unsigned indice)
    {
        return vertices[indice].face;
    }

    Faces getFace(unsigned indice) const
    {
        return faces[indice];
    }
    int getVerticesNb() const
    {
        return vertices.size();
    }

    int getFacesNb() const
    {
        return faces.size();
    }
    std::vector<Vertices> getBounds()
    {

        Vertices max = Vertices(std::numeric_limits<float>::min());
        Vertices min = Vertices(std::numeric_limits<float>::max());

        for (const auto &vertex : vertices)
        {
            if (vertex.x < min.x)
            {
                min.x = vertex.x;
            }
            if (vertex.x > max.x)
            {
                max.x = vertex.x;
            }
            if (vertex.y < min.y)
            {
                min.y = vertex.y;
            }
            if (vertex.y > max.y)
            {
                max.y = vertex.y;
            }
        }

        return {max, min};
    }

    int addVertice(const Vertices &vert)
    {
        vertices.emplace_back(vert.x, vert.y, vert.z);
        return vertices.size() - 1;
    }

    int makeFace(int index1, int index2, int index3)
    {
        faces.emplace_back(index1, index2, index3);
        int size = faces.size() - 1;
        faces[size].neighbor.resize(3);
        std::fill(faces[size].neighbor.begin(), faces[size].neighbor.end(), size);
        return size;
    }

    // Return a neighbor in direction specified by a function of type indice_local + (1 or 2)/3
    unsigned int getNeighborInFace(unsigned &indice_face, unsigned &indice_vertex, std::function<unsigned(const unsigned &)> direction)
    {
        // Return the face opposed to local indices
        return faces[indice_face].neighbor[direction(indice_vertex)];
    }

    // Retourne le sommet ne correspondant à aucun de ceux du bord
    inline int return_opposite_vertices(const Edges &edge, std::vector<unsigned> candidates)
    {
        int i = 0;
        for (const auto &vert : candidates)
        {

            if (vert == edge.v1 || vert == edge.v2)
            {
                i++;
                continue;
            }
            else
            {
                if (i != vert)
                {
                    int i = 3;
                }
                break;
            }
        }

        return i;
    }

    void createSuperTriangle();

    // Mesh structures manipulations
    unsigned int identify_point_face(const Vertices &point)
    {

        std::cout << "Identify point: " << point << std::endl;
        for (int i = 0; i < faces.size(); i++)
        {
            if (in_triangle_test_2d(*this, i, point) >= 0)
            {

                return i;
            }
        }
        return static_cast<unsigned int>(-1);
    }

    // Hopefully nobody see this thing
    int identify_intersection(Vertices &orign, const Vertices &ray_dir, const std::vector<Vertices> &points_world, float &t, Vertices &intersection)
    {
        static constexpr float epsilon_mesh = std::numeric_limits<float>::epsilon();
        int i = 0;
        for (const auto &triangles : faces)
        {
            // Compute normal vector to check if ray parallel
            Vertices edge1 = vertices[triangles.vertices[1]] - vertices[triangles.vertices[0]];
            Vertices edge2 = vertices[triangles.vertices[2]] - vertices[triangles.vertices[0]];
            Vertices normal_ray_e2 = crossProduct(ray_dir, edge2);
            // Useful in this implem ?
            const float det = dotProduct(edge1, normal_ray_e2);
            ////////////

            const float inv_det = 1.0 / det;
            const Vertices ray_vo = orign - vertices[triangles.vertices[0]];

            float val_u = inv_det * dotProduct(ray_vo, normal_ray_e2);

            if (val_u < 0 || val_u > 1)
            {
                continue;
            }

            const Vertices cross_e1 = crossProduct(ray_vo, edge1);
            float val_v = inv_det * dotProduct(ray_dir, cross_e1);

            if (val_v < 0 || val_v + val_u > 1)
            {
                continue;
            }

            t = inv_det * dotProduct(edge2, cross_e1);
            if (t > epsilon_mesh)
            {
                intersection = orign + (ray_dir * t); // Compute intersection point

                return i;
            }
            std::cout << "No this" << i << std::endl;
            i++;
        }

        return -1;
    }

    float orientation_test_edges(const Edges edge, const Vertices &vert3)
    {
        Vertices vert1(vertices[edge.v1]);
        Vertices vert2(vertices[edge.v2]);

        return (((vert2.x - vert1.x) * (vert3.y - vert1.y)) -
                ((vert2.y - vert1.y) * (vert3.x - vert1.x)));
    }
    const Edges &closest_Edges(const Edges &a, const Edges &b, const Edges &c, const Vertices &vert)
    {
        float result_a = std::abs(orientation_test_edges(a, vert));
        float result_b = std::abs(orientation_test_edges(b, vert));
        float result_c = std::abs(orientation_test_edges(c, vert));
        if (result_a >= result_b)
        {
            if (result_a >= result_c)
            {
                return a;
            }
        }
        else
        {
            if (result_b >= result_c)
            {
                return b;
            }
        }
        return c;
    }

    inline bool edgeCoherence(Edges edge);
    bool edgeCoherence(Edges edge, unsigned int face1, unsigned int face2);
    // Insertion must be within the convex hull
    Faces insert_point_convexless(const unsigned int &new_point, unsigned int &vertices_face);
    Faces insert_point_convexless(const int &coord_x, const int &coord_y, const int &coord_z, unsigned int &vertices_face);

    friend void lawson(Mesh &mesh);

    Edges sharedEdge(unsigned int &face1, unsigned int &face2)
    {
        std::vector<unsigned> indices;
        for (const auto &vert : faces[face1].vertices)
        {
            for (const auto &vert2 : faces[face2].vertices)
            {

                if (vert == vert2)
                {
                    indices.push_back(vert2);
                }
            }
        }
        if (indices.size() == 2)
        {
            return Edges(indices[0], indices[1], face1, face2);
        }
        else
        {
            return Edges(-1, -1);
        };
    };
    // Pour un triangle le cercle circonscrit à une arête à son point opposé hors du delaunay
    bool flip_edge(Edges &edge_info);

    bool isDelaunay(Edges edge);

    void incremental_triangulate();
    void incremental_triangulate2();
    //Divide incremental_triangulate into two function for real time
    std::vector<unsigned int> incremental_triangulate2_step_start();
    void incremental_triangulate2_step(std::vector<unsigned int>& );
    // TODO  All really needed ?
    void extractEdges(std::queue<Edges> &edge_queue);
    void extractEdgesFromFace(std::queue<Edges> &edge_queue, EdgeSet &edge_set, unsigned int &face, const Faces &back_up);
    void extractEdgesFromFace(std::queue<Edges> &edge_queue, EdgeSet &edge_set, unsigned int &face);
    void extractFacesEdge(std::queue<Edges> &edge_queue, Edges edge_info);

    void split_triangle(unsigned int vertice_indx, unsigned int &new_vertices_face);
    /////////////////////////////////////// TP3
    template <typename T>
    T compute_laplacian(unsigned int indice, const std::vector<T> &curr_weigh);
    template <typename T>
    T compute_laplacian_with_function(unsigned int indice, std::function<T(const Mesh &, unsigned &indice_a, unsigned &indice_b)> function) const;

    std::vector<Vertices> compute_mesh_normal();
    std::vector<Vertices> compute_mesh_normal_test();
    std::vector<float> compute_mean_curvature_f();
    std::vector<Vertices> compute_mean_curvature_tex_coords();
    std::vector<Vertices> compute_laplacian_vects() const;

    void mesh_heat_diffusion(float time_step = common_time_step);
    ////////////////Iterator
    struct Iterator_Face
    {
        Iterator_Face() = default;

        Iterator_Face(Faces *ptr) : m_ptr(ptr) {}

        Faces &operator*() const { return *m_ptr; }
        Faces *operator->() { return m_ptr; }
        Iterator_Face &operator++()
        {
            m_ptr++;
            return *this;
        }
        Iterator_Face operator++(int)
        {
            Iterator_Face tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const Iterator_Face &a, const Iterator_Face &b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator_Face &a, const Iterator_Face &b) { return a.m_ptr != b.m_ptr; };

    private:
        Faces *m_ptr;
    };

    Iterator_Face faces_begin() { return Iterator_Face(&faces[0]); }
    Iterator_Face faces_end() { return Iterator_Face(&faces[(faces.size())]); }

    struct Iterator_Vertice
    {
        Iterator_Vertice() = default;

        Iterator_Vertice(Vertices *ptr) : m_ptr(ptr) {}

        Vertices &operator*() const { return *m_ptr; }
        Vertices *operator->() { return m_ptr; }
        Iterator_Vertice &operator++()
        {
            m_ptr++;
            return *this;
        }
        Iterator_Vertice operator++(int)
        {
            Iterator_Vertice tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const Iterator_Vertice &a, const Iterator_Vertice &b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator_Vertice &a, const Iterator_Vertice &b) { return a.m_ptr != b.m_ptr; };

    private:
        Vertices *m_ptr;
    };

    Iterator_Vertice vertices_begin() { return Iterator_Vertice(&vertices[0]); }
    Iterator_Vertice vertices_end() { return Iterator_Vertice(&vertices[(vertices.size())]); }

    struct Circulator_Face
    {
        Circulator_Face() = default;

        Circulator_Face(std::vector<unsigned> faces, unsigned p_current_face, unsigned p_vertex_anchor) : m_ptr(faces), current_face_index(p_current_face), vert_index(p_vertex_anchor)
        {
        }
        unsigned end()
        {
            return m_ptr[m_ptr.size() - 1];
        }

        unsigned size()
        {
            return m_ptr.size();
        }

        unsigned operator*() const { return m_ptr[current_face_index]; }

        // Turn countercklockwise
        unsigned &operator++()
        {
            current_face_index = (current_face_index + 1) % (m_ptr.size());
            return m_ptr[current_face_index];
        }
        // Turn clockwise
        unsigned operator++(int)
        {
            unsigned tmp = current_face_index;
            current_face_index = (current_face_index + 1) % (m_ptr.size());
            return m_ptr[tmp];
        }

        friend bool operator==(const Circulator_Face &a, const Circulator_Face &b)
        {
            // return &a.m_ptr == &b.m_ptr;
            return (a.m_ptr.size() == b.m_ptr.size()) && (a.current_face_index == b.current_face_index) && (a.vert_index == b.vert_index);
        };
        friend bool operator!=(const Circulator_Face &a, const Circulator_Face &b)
        {
            // return &a.m_ptr != &b.m_ptr;
            return !((a.m_ptr.size() == b.m_ptr.size()) && (a.current_face_index == b.current_face_index) && (a.vert_index == b.vert_index));
        };

    private:
        // Faces
        std::vector<unsigned> m_ptr; // Or directly get face
        unsigned current_face_index;
        unsigned vert_index;
    };

    Circulator_Face incident_faces(unsigned &vertices_indices) const;
    // An incident faces designed to handle the convex hull better
    Circulator_Face incident_faces_convex(unsigned &vertices_indices) const;

    ////////////////////////////////IDK

    struct Circulator_Vertices
    {
        Circulator_Vertices() = default;

        Circulator_Vertices(std::vector<unsigned> vertices, unsigned p_current_vertices, unsigned p_vertex_anchor)
            : m_ptr(vertices), current_vertices(p_current_vertices), vert_index(p_vertex_anchor)
        {
        }

        unsigned operator*() const { return m_ptr[current_vertices]; }
        // Turn countercklockwise
        unsigned &operator++()
        {
            current_vertices = (current_vertices + 1) % (m_ptr.size());
            return m_ptr[current_vertices];
        }
        // Turn clockwise
        unsigned operator++(int)
        {
            unsigned tmp = current_vertices;
            current_vertices = (current_vertices + 1) % (m_ptr.size());
            return m_ptr[tmp];
        }

        friend bool operator==(const Circulator_Vertices &a, const Circulator_Vertices &b)
        {
            return (a.m_ptr.size() == b.m_ptr.size()) && (a.current_vertices == b.current_vertices) && (a.vert_index == b.vert_index);
        }
        friend bool operator!=(const Circulator_Vertices &a, const Circulator_Vertices &b)
        {
            return ((a.m_ptr.size() == b.m_ptr.size()) && (a.current_vertices == b.current_vertices) && (a.vert_index == b.vert_index));
        };

    private:
        // Faces
        std::vector<unsigned> m_ptr; // Or directly get face
        unsigned current_vertices;   // Index in the table
        unsigned vert_index;         // Index of the vertices the circulator was created rom
    };

    Circulator_Vertices incident_vertices(unsigned &vertices_indices) const;
};

// Return local indices of the a vertices neighbor on a face in a given direction
unsigned getNeighbors(const Faces &curr_face, unsigned &indice, std::function<unsigned(const unsigned &)> direction);
// Function handling removal and rebinding of vertices
// Probably to put in "vertices simplification function"

float in_triangle_test_2d(const Mesh &mesh, const unsigned int &face, const Vertices &point);

float in_triangle_test_2d(std::vector<Vertices> &vertices, const Faces &face, unsigned int &point);
inline int return_opposite_vertices(const Edges &edge, std::vector<unsigned> candidates)
{

    int i = 0;
    for (const auto &vert : candidates)
    {

        if (vert == edge.v1 || vert == edge.v2)
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