#include "Mesh.h"

template <typename T>
T Mesh::compute_laplacian(unsigned int indice, const std::vector<T> &curr_weigh)
{

    // Récupère l'index des faces
    Mesh::Circulator_Face circ = this->incident_faces(indice);
    // Récupérer le premier indice
    unsigned int previous_face = *circ;

    circ++;

    T total = T();
    double area = 0.0;
    int fail = 0;
    for (int i = 0; i < circ.size(); ++circ, ++i)
    {

        unsigned int local_indice = return_local_indices(faces[*circ], indice);
        unsigned int previous_local_indice = return_local_indices(faces[previous_face], indice);

        unsigned vert_right = faces[*circ].vertices[(local_indice + 2) % 3];
        unsigned vert_left = faces[previous_face].vertices[(previous_local_indice + 1) % 3];
        unsigned vert_opposite = faces[*circ].vertices[(local_indice + 1) % 3];

        // Some  check to skip treatment of 0 and 0
        // Mainly created to test with double
        if (curr_weigh[vert_opposite] == 0 && curr_weigh[indice] == 0)
        {
            // Update the face reused
            previous_face = *circ;
            // std::cout << "nna" << std::endl;
            fail++;
            if (fail == circ.size())
            {
                total = T();
                area = 1;
                return T();
            }
            continue;
        }

        // Skip multipl computation, so.. ok ?
        Vertices vector_left_i = vertices[indice] - vertices[vert_left];
        Vertices vector_left_j = vertices[vert_opposite] - vertices[vert_left];
        Vertices vector_right_i = vertices[indice] - vertices[vert_right];
        Vertices vector_right_j = vertices[vert_opposite] - vertices[vert_right];

        // Left
        double cos_left = dotProduct(vector_left_i, vector_left_j) / (magn(vector_left_i) * magn(vector_left_j));
        double sin_left = std::sqrt(1 - (cos_left * cos_left));
        double cot_left = (sin_left != 0) ? (cos_left / sin_left) : 0;
        // RIght
        double cos_right = dotProduct(vector_right_i, vector_right_j) / (magn(vector_right_i) * magn(vector_right_j));
        double sin_right = std::sqrt(1 - (cos_right * cos_right));
        double cot_right = (sin_right != 0) ? (cos_right / sin_right) : 0;
        // Distance
        T distance = (curr_weigh[vert_opposite] - curr_weigh[indice]);

        total = total + (distance * (cot_right + cot_left));

        // Area approximation
        area = area + magn((crossProduct(vector_right_i, vector_right_j))) / 2.0f;

        previous_face = *circ;
    }

    T laplacian = (total) * (1 / (2 * area));

    return laplacian;
}

template <typename T>
T Mesh::compute_laplacian_with_function(unsigned int indice, std::function<T(const Mesh &, unsigned &indice_a, unsigned &indice_b)> function) const
{

    // Récupère l'index des faces
    Mesh::Circulator_Face circ = this->incident_faces_convex(indice);
    // Récupérer le premier indice
    unsigned int previous_face = *circ;
    // Skip the first indice
    circ++;

    T total = T();
    double area = 0.0;

    for (int i = 0; i < circ.size(); ++circ, ++i)
    {
        unsigned int local_indice = return_local_indices(faces[*circ], indice);
        unsigned int previous_local_indice = return_local_indices(faces[previous_face], indice);

        unsigned vert_right = faces[*circ].vertices[(local_indice + 2) % 3];
        unsigned vert_left = faces[previous_face].vertices[(previous_local_indice + 1) % 3];
        unsigned vert_opposite = faces[*circ].vertices[(local_indice + 1) % 3];

        // Skip multipl computation, so.. ok ?
        Vertices vector_left_i = vertices[indice] - vertices[vert_left];
        Vertices vector_left_j = vertices[vert_opposite] - vertices[vert_left];
        Vertices vector_right_i = vertices[indice] - vertices[vert_right];
        Vertices vector_right_j = vertices[vert_opposite] - vertices[vert_right];

        // Left
        double cos_left = dotProduct(vector_left_i, vector_left_j) / (magn(vector_left_i) * magn(vector_left_j));
        double sin_left = std::sqrt(1 - (cos_left * cos_left));
        double cot_left = (sin_left != 0) ? (cos_left / sin_left) : 0;
        // RIght
        double cos_right = dotProduct(vector_right_i, vector_right_j) / (magn(vector_right_i) * magn(vector_right_j));
        double sin_right = std::sqrt(1 - (cos_right * cos_right));
        double cot_right = (sin_right != 0) ? (cos_right / sin_right) : 0;

        // Distance
        T distance = function(*this, indice, vert_opposite);

        total = total + (distance * (cot_right + cot_left));

        // Area approximation
        area = area + magn((crossProduct(vector_right_i, vector_right_j))) / 3.0f;

        previous_face = *circ;
    }

    T laplacian = (total) * (1 / (2 * area));

    return laplacian;
}

std::vector<Vertices> Mesh::compute_laplacian_vects() const
{
    std::vector<Vertices> laplacian;
    auto compute_distance_vect = [&](const Mesh &mesh, unsigned int &indice_a, unsigned int &indice_b)
    {
        return mesh.vertices[indice_b] - mesh.vertices[indice_a];
    };

    for (int i = 0; i < vertices.size(); i++)
    {
        Vertices laplacian_vect = compute_laplacian_with_function<Vertices>(i, compute_distance_vect);

        if (std::isnan((laplacian_vect.x)))
        {
            laplacian_vect = Vertices(0, 0, 0); // Set the result to 0
        }
        laplacian.push_back(laplacian_vect);
    }
    return laplacian;
}
std::vector<Vertices> Mesh::compute_mesh_normal()
{
    std::vector<Vertices> laplace_abcisse = this->compute_laplacian_vects();
    std::vector<Vertices> normals;

    for (int i = 0; i < laplace_abcisse.size(); i++)
    {
        // Stuff to control signedness

        unsigned int local_indice = return_local_indices(faces[vertices[i].face], i);
        unsigned vert_right = faces[vertices[i].face].vertices[(local_indice + 2) % 3];
        unsigned vert_left = faces[vertices[i].face].vertices[(local_indice + 1) % 3];
        Vertices vector_left = vertices[vert_left] - vertices[i];
        Vertices vector_right = vertices[vert_right] - vertices[i];
        Vertices correct_direction_normal = crossProduct(vector_left, vector_right);
        // Laplacian normal
        Vertices normal = ((laplace_abcisse[i]) / magn(laplace_abcisse[i]));
        normals.push_back((laplace_abcisse[i]) / magn(laplace_abcisse[i]) // Multiply by coorrect sign
                          * (2 * (dotProduct(correct_direction_normal, normal) <= 0) - 1));
    }

    return normals;
}

// Averaging using laplacian and cros product
std::vector<Vertices> Mesh::compute_mesh_normal_test()
{
    std::vector<Vertices> vertex_normals = std::vector<Vertices>(vertices.size());
    for (int i = 0; i < vertex_normals.size(); i++)
    {
        unsigned int incident_face = vertices[i].face;
        unsigned int loc_indice = return_local_indices(faces[incident_face], i);
        unsigned vert_right = faces[incident_face].vertices[(loc_indice + 2) % 3];
        unsigned vert_left = faces[incident_face].vertices[(loc_indice + 1) % 3];
        vertex_normals[i] = crossProduct(vertices[vert_right], vertices[vert_left]);
        vertex_normals[i] = vertex_normals[i] / magn(vertex_normals[i]);
    }
    return vertex_normals;
}

std::vector<float> Mesh::compute_mean_curvature_f()
{
    std::vector<Vertices> laplace_abcisse = this->compute_laplacian_vects();
    std::vector<float> mean_curvature;

    for (int i = 0; i < laplace_abcisse.size(); i++)
    {
        mean_curvature.push_back(magn(laplace_abcisse[i]) / 2);
    }

    return mean_curvature;
}

std::vector<Vertices> Mesh::compute_mean_curvature_tex_coords()
{
    std::vector<Vertices> texture;
    std::vector<float> curvature = compute_mean_curvature_f();
    for (size_t counter = 0; counter < curvature.size(); counter++)
    {
        float val = 0.0;
        if (curvature[counter] >= 0.0 && curvature[counter] <= 1.0)
        {
            val = 0.50;
        }
        else if (curvature[counter] >= 1.0 && curvature[counter] <= 10.0)
        {
            val = 0.55;
        }
        else if (curvature[counter] >= 10.0 && curvature[counter] <= 20.0)
        {
            val = 0.60;
        }
        else if (curvature[counter] >= 20.0 && curvature[counter] <= 30.0)
        {
            val = 0.70;
        }
        else if (curvature[counter] >= 30.0)
        {
            val = 0.80;
        }
        texture.emplace_back(val, 0.0, 0.0);
    }
    return texture;
}

void Mesh::mesh_heat_diffusion(float time_step)
{
    std::vector<double> laplacian_tab_now = std::vector<double>(vertices.size());

    // Vertices 0 get a value
    laplacian_tab_now[0] = 100.0;
    int time = 0;

    while (time < 150)
    {
        time++;
        for (int i = 1; i < laplacian_tab_now.size(); i++)
        {
            laplacian_tab_now[i] = laplacian_tab_now[i] + (compute_laplacian(i, laplacian_tab_now) * time_step);
            laplacian_tab_now[0] = 100.0;
        }
        std::cout << time << std::endl;
    }
    for (int i = 0; i < laplacian_tab_now.size(); i++)
    {
        if (laplacian_tab_now[i] == 0)
        {
            continue;
        }
        std::cout << "Result heat: " << i << std::endl;

        std::cout << laplacian_tab_now[i] << std::endl;
    }

    return;
}

// TODO: On a vertice at  the convex hull, the faces will simply stop and not try to rotate further
Mesh::Circulator_Face Mesh::incident_faces(unsigned &vertices_indices) const
{
    // Procédé
    // On récupère la face incidente et on s'y rend
    // D'elle on prend l'une des deux faces gauche ou droite ne correspondant pas à l'indices
    // On récupère l'indice local du vertex sur cette face
    auto right_face = [&](const unsigned &indices)
    {
        return (indices + 2) % 3;
    };
    auto left_face = [&](const unsigned &indices)
    {
        return (indices + 1) % 3;
    };
    // Store in a vector the very all the indices of face bordering the vertices
    std::vector<unsigned> border_faces;

    // TODO: More or lessbad stop gap measure
    std::set<unsigned> border_faces_set;

    border_faces.push_back(vertices[vertices_indices].face);

    // Identify local indices in the incident face
    unsigned vert_loc_indices = return_local_indices(faces[border_faces[0]], vertices_indices);

    // Jumping to another face from this from one direction
    unsigned curr_face = getNeighbors(faces[vertices[vertices_indices].face], vert_loc_indices, left_face);
    // Circling in the loop face from another direction

    int count = 0;
    while (vertices[vertices_indices].face != curr_face)
    {
        if (!border_faces_set.emplace(curr_face).second)
        {
            break;
        }
        unsigned previous_face = curr_face;
        count++;
        // Recuperate current face local indices
        // We always turn while considering the original vertices as an anchor point
        vert_loc_indices = return_local_indices(faces[curr_face], vertices_indices);
        if (vert_loc_indices == 3)
        {
            break;
        }
        // Push back current face
        border_faces.push_back(curr_face);
        curr_face = getNeighbors(faces[curr_face], vert_loc_indices, left_face);
        if (curr_face == previous_face)
        {
            break; // Convexhull
        }
    }

    return Circulator_Face(border_faces, 0, vertices_indices);
}

// TODO: On a vertice at  the convex hull, the faces will simply stop and not try to rotate further
Mesh::Circulator_Face Mesh::incident_faces_convex(unsigned &vertices_indices) const
{
    auto right_face = [&](const unsigned &indices)
    {
        return (indices + 2) % 3;
    };
    auto left_face = [&](const unsigned &indices)
    {
        return (indices + 1) % 3;
    };
    // Store in a vector the very all the indices of face bordering the vertices
    std::vector<unsigned> border_faces;
    std::set<unsigned> border_faces_set;

    unsigned int start_face = vertices[vertices_indices].face;
    border_faces.push_back(start_face);
    border_faces_set.insert(start_face);
    // Identify local indices in the incident face
    unsigned vert_loc_indices = return_local_indices(faces[border_faces[0]], vertices_indices);
    // Function to get the next face in a specified direction (left or right)
    auto get_next_face = [&](unsigned curr_face, unsigned vert_loc_indices, bool left)
    {
        std::function<unsigned(const unsigned &)> direction;

        if (left)
        {
            direction = left_face;
        }
        else
        {
            direction = right_face;
        }
        return getNeighbors(faces[curr_face], vert_loc_indices, direction);
    };
    auto traverse_faces = [&](bool go_left)
    {
        unsigned curr_face = start_face;
        unsigned vert_loc_indices = return_local_indices(faces[curr_face], vertices_indices);

        while (true)
        {
            curr_face = get_next_face(curr_face, vert_loc_indices, go_left);
            if (curr_face == start_face || !border_faces_set.insert(curr_face).second)
            {
                break;
            }
            border_faces.push_back(curr_face);
            vert_loc_indices = return_local_indices(faces[curr_face], vertices_indices);
            if (vert_loc_indices == 3)
            {
                break;
            }
        }
    };
    traverse_faces(true);  // Traverse to the left
    traverse_faces(false); // Traverse to the right
    return Circulator_Face(border_faces, 0, vertices_indices);
}

Mesh::Circulator_Vertices Mesh::incident_vertices(unsigned &vertices_indices) const
{
    auto right_vertices = [&](const unsigned &indices)
    {
        return (indices + 2) % 3;
    };
    auto left_vertices = [&](const unsigned &indices)
    {
        return (indices + 1) % 3;
    };
    // Store in a vector the very all the indices of face bordering the vertices
    std::vector<unsigned> border_vertices;
    unsigned int adjacent_face = vertices[vertices_indices].face;
    // Identify local indices in the incident face
    unsigned vert_loc_indices = return_local_indices(faces[adjacent_face], vertices_indices);
    border_vertices.push_back(faces[adjacent_face].vertices[right_vertices(vert_loc_indices)]);

    unsigned curr_face = getNeighbors(faces[adjacent_face], vert_loc_indices, left_vertices);

    // Jumping to another face from this from one direction
    int i = 0;
    // Circling in the loop face from another direction
    while (vertices[vertices_indices].face != curr_face)
    {
        i++;
        vert_loc_indices = return_local_indices(faces[curr_face], vertices_indices);
        if (vert_loc_indices == 3)
        {
            break;
        }
        curr_face = getNeighbors(faces[curr_face], vert_loc_indices, left_vertices);
        border_vertices.push_back(faces[curr_face].vertices[left_vertices(vert_loc_indices)]);
    }

    return Circulator_Vertices(border_vertices, 0, vertices_indices);
}

void Mesh::extractEdges(std::queue<Edges> &edge_queue)
{
    edge_queue = std::queue<Edges>();
    std::unordered_set<Edges, Edges::Edgeshash> edge_set;
    int face_counter = 0; // face index

    std::cout << "Start exploring face" << std::endl;
    // Current indices
    for (const auto &face : faces)
    {
        unsigned f1 = face_counter;

        std::vector<Edges> curr_edges;

        for (int i = 0; i < 3; i++)
        {
            unsigned f2 = face.neighbor[i];
            unsigned vert0 = face.vertices[(i + 2) % 3];
            unsigned vert1 = face.vertices[(i + 1) % 3];
            if (f2 != static_cast<unsigned>(-1) && f1 != f2)
            {
                Edges e1(vert0, vert1, f1, f2);
                curr_edges.push_back(e1);
            }
        }
        face_counter++;

        for (const auto &edge : curr_edges)
        {

            if (edge_set.find(edge) == edge_set.end())
            {
                if (!isDelaunay(edge))
                {
                    edge_queue.push(edge);
                    edge_set.insert(edge);
                }
            }
        }
    }
}

void Mesh::extractEdgesFromFace(std::queue<Edges> &edge_queue, EdgeSet &edge_set, unsigned int &face)
{

    std::cout << "Start extracting from face" << std::endl;
    unsigned f1 = face;
    std::vector<Edges> curr_edges;

    for (int i = 0; i < 3; i++)
    {
        unsigned f2 = faces[face].neighbor[i];
        unsigned vert0 = faces[face].vertices[(i + 2) % 3];
        unsigned vert1 = faces[face].vertices[(i + 1) % 3];
        if (f2 != static_cast<unsigned>(-1) && f1 != f2)
        {
            Edges e1(vert0, vert1, f1, f2);
            if (!edgeCoherence(e1)) // TODO: Should not be necessary
            {
                continue;
            }
            curr_edges.push_back(e1);
        }
    }

    for (const auto &edge : curr_edges)
    {

        if (edge_set.find(edge) == edge_set.end())
        {
            if (!isDelaunay(edge))
            {
                edge_queue.push(edge);
                edge_set.insert(edge);
            }
        }
    }
}

bool Mesh::flip_edge(Edges &edge_info)
{
    std::vector<unsigned int> loc_vert_f1;
    std::vector<unsigned int> loc_vert_f2;
    std::vector<unsigned int> edge_faces;
    std::vector<unsigned int> edges_indices;

    Mesh::Circulator_Face itv1 = incident_faces_convex(edge_info.v1);
    int counter_face_search = 0;
    //  Get the correct faces
    for (int i = 0; i < itv1.size(); i++, itv1++)
    {
        Mesh::Circulator_Face itv2 = incident_faces_convex(edge_info.v2);

        for (int j = 0; j < itv2.size(); j++, itv2++)
        {
            if (*itv1 == *itv2)
            {
                edge_faces.push_back(*itv1);
                break;
            }
        }
    }

    // On convex hull the circuclator may be unable to go further
    // This wasn't took into account previously
    if (edge_faces.size() < 2)
    {
        std::cout << "Number of faces too low for a flip" << std::endl;
        return false;
    };

    unsigned int face1 = edge_faces[0];
    unsigned int face2 = edge_faces[1];

    if (!edgeCoherence(edge_info, face1, face2))
    { // TODO stopgap measyre
        std::cout << "The edge was found to be incoherent" << std::endl;
        return false;
    }

    loc_vert_f1.emplace_back(return_local_indices(faces[face1], edge_info.v1));
    loc_vert_f1.emplace_back(return_local_indices(faces[face1], edge_info.v2));
    loc_vert_f2.emplace_back(return_local_indices(faces[face2], edge_info.v1));
    loc_vert_f2.emplace_back(return_local_indices(faces[face2], edge_info.v2));

    // New face_f1 belong to new edge 2
    // New face_f2 belong to new edge 0
    // V0 here is the vertices at ther right of  an edge
    // For F1, v0 belonged to F2, F
    Faces face1_backup = faces[face1];
    Faces face2_backup = faces[face2];

    // Vertex 1 avec opposé face 10 qui appartenait à 8

    // Sorted in order 4 then 0
    auto opp_vertices = [&](const Edges &e, const Faces &f)
    {
        return f.vertices[return_opposite_vertices(edge_info, f.vertices)]; // opposé à f1
    };

    // Vertice directly opposed to eadch of the other face
    unsigned int new_v0_f1 = opp_vertices(edge_info, faces[face1]); // OK
    unsigned int new_v0_f2 = opp_vertices(edge_info, faces[face2]);

    unsigned int new_v1_f1 = new_v0_f2; // OK
    unsigned int new_v1_f2 = new_v0_f1;

    unsigned int new_v2_f1 = faces[face1].vertices[(return_local_indices(faces[face1], new_v0_f1) + 2) % 3]; // OK
    unsigned int new_v2_f2 = faces[face2].vertices[(return_local_indices(faces[face2], new_v0_f2) + 2) % 3];

    faces[face1].vertices[0] = new_v0_f1;
    faces[face2].vertices[0] = new_v0_f2;

    faces[face1].vertices[1] = new_v1_f1;
    faces[face2].vertices[1] = new_v1_f2;

    faces[face1].vertices[2] = new_v2_f1;
    faces[face2].vertices[2] = new_v2_f2;

    //  NEIGHBOR UPDATE
    unsigned int oppf1 = return_opposite_vertices(edge_info, face1_backup.vertices);
    unsigned int oppf2 = return_opposite_vertices(edge_info, face2_backup.vertices);

    faces[face1].neighbor[2] = face2;
    faces[face2].neighbor[2] = face1;

    // Face opposite to the old edges
    // In both case they belonged to the other face
    // Those face border the edge
    // MIght bewrong
    // Recompute
    // Local position of vertixes opposite to face

    // May be too specidfic
    std::cout << oppf1 << " " << oppf2 << std::endl;
    faces[face1].neighbor[0] = face2_backup.neighbor[(oppf2 + 2) % 3];
    faces[face2].neighbor[0] = face1_backup.neighbor[(oppf1 + 2) % 3];

    // If those face used to have value indicating they were edge at the convex hull
    if (faces[face1].neighbor[0] == face2)
    {
        faces[face1].neighbor[0] = face1;
    }
    else
    {
        unsigned int face_tochange = faces[face1].neighbor[0];
        Edges shared_edge = sharedEdge(face1, face_tochange);
        faces[face_tochange].neighbor[return_opposite_vertices(shared_edge, faces[face_tochange].vertices)] = face1;
    }

    if (faces[face2].neighbor[0] == face1)
    {
        faces[face2].neighbor[0] = face2;
    }
    else
    {
        unsigned int face_tochange = faces[face2].neighbor[0];
        Edges shared_edge = sharedEdge(face2, face_tochange);
        faces[face_tochange].neighbor[return_opposite_vertices(shared_edge, faces[face_tochange].vertices)] = face2;
    }

    faces[face1].neighbor[1] = face1_backup.neighbor[(oppf1 + 1) % 3];
    faces[face2].neighbor[1] = face2_backup.neighbor[(oppf2 + 1) % 3];

    if (faces[face1].neighbor[1] != face1) // Good chance those two don't matter
    {
        unsigned int face_tochange = faces[face1].neighbor[1];
        Edges shared_edge = sharedEdge(face1, face_tochange);
        faces[face_tochange].neighbor[return_opposite_vertices(shared_edge, faces[face_tochange].vertices)] = face1;

    } // NOt in convex hull we update the neighbor

    if (faces[face2].neighbor[1] != face2)
    {
        unsigned int face_tochange = faces[face2].neighbor[1];
        Edges shared_edge = sharedEdge(face2, face_tochange);

        faces[face_tochange].neighbor[return_opposite_vertices(shared_edge, faces[face_tochange].vertices)] = face2;

    } // NOt in convex hull we update the neighbor

    // Change neighboring faces
    return true;
}

void lawson(Mesh &mesh)
{
    // Initialize queue
    std::queue<Edges> edge_queue;
    EdgeSet edge_set;

    std::cout << " Extracting edges from   queue " << std::endl;
    mesh.extractEdges(edge_queue);
    // Current indices
    std::cout << edge_queue.size() << " edges in queue " << std::endl;
    while (!edge_queue.empty())
    {

        Edges edge = edge_queue.front();
        edge_queue.pop();

        if (mesh.isDelaunay(edge))
        {
            std::cout << "Delaunay edge " << std::endl;
            std::cout << edge << std::endl;
            continue;
        };

        // Assuming you have a way to find these faces, e.g. using a method to get faces by edge
        // Flip the edge
        if (!mesh.flip_edge(edge))
        {
            continue;
        };

        std::vector<unsigned int> edge_faces;

        Mesh::Circulator_Face itv1 = mesh.incident_faces_convex(edge.v1);
        int counter_face_search = 0;
        std::cout << "In Delaunay check" << std::endl;
        std::cout << edge << std::endl;

        for (int i = 0; i < itv1.size(); i++, itv1++)
        {
            Mesh::Circulator_Face itv2 = mesh.incident_faces_convex(edge.v2);

            for (int j = 0; j < itv2.size(); j++, itv2++)
            {
                if (*itv1 == *itv2)
                {
                    edge_faces.push_back(*itv1);
                    break;
                }
            }
        }
        if (edge_faces.size() < 2)
        {
            std::cout << "Early exit for invalid face" << std::endl;
            continue;
        };

        mesh.extractEdgesFromFace(edge_queue, edge_set, edge_faces[0]);
        mesh.extractEdgesFromFace(edge_queue, edge_set, edge_faces[1]);
        edge_set.clear();
    }
}

void Mesh::createSuperTriangle()
{
    float max_x = std::numeric_limits<float>::min();
    float max_y = std::numeric_limits<float>::min();
    float min_x = std::numeric_limits<float>::max();
    float min_y = std::numeric_limits<float>::max();

    // Find the min and max values for the x and y coordinates
    for (const auto &vertex : vertices)
    {
        if (vertex.x > max_x)
            max_x = vertex.x;
        if (vertex.y > max_y)
            max_y = vertex.y;
        if (vertex.x < min_x)
            min_x = vertex.x;
        if (vertex.y < min_y)
            min_y = vertex.y;
    }

    // Calculate the center of the bounding box
    float center_x = (min_x + max_x) / 2.0f;
    float center_y = (min_y + max_y) / 2.0f;

    float width = max_x - min_x;
    float height = max_y - min_y;
    float padding = std::max(width, height) * 2.0f;

    vertices.emplace_back(center_x, center_y + padding, 0.0);
    vertices.emplace_back(center_x - padding, center_y - padding, 0.0);
    vertices.emplace_back(center_x + padding, center_y - padding, 0.0);

    // Super triangle addition
    faces.emplace_back(vertices.size() - 3, vertices.size() - 2, vertices.size() - 1);
    faces[getFacesNb() - 1].neighbor[0] = getFacesNb() - 1;
    faces[getFacesNb() - 1].neighbor[1] = getFacesNb() - 1;
    faces[getFacesNb() - 1].neighbor[2] = getFacesNb() - 1;
}

void Mesh::incremental_triangulate()
{
    // We choose  not to use the mesh structure for simplicity
    // Look for the min and max

    this->createSuperTriangle();

    std::queue<Edges> edge_queue;
    EdgeSet edge_set;
    int counter = 0;
    while (counter < vertices.size())
    {
        edge_set.clear();
        std::cout << "Inserting point number " << vertices[counter] << " " << vertices[counter] << std::endl;
        unsigned face;
        // Pre extract "ssborder-edge"

        Faces face_backup = this->insert_point_convexless(counter, face);

        std::array<unsigned, 3> new_faces = {face, faces.size() - 1, faces.size() - 2};

        for (size_t i = 0; i < 3; i++)
        {

            extractEdgesFromFace(edge_queue, edge_set, new_faces[i]);
            while (!edge_queue.empty())
            {
                Edges current_edge = edge_queue.front();
                std::cout << current_edge << std::endl;

                edge_queue.pop();
                // We avoid flipping the new insertion
                if (current_edge.contains(counter))
                {
                    std::cout << "Skipping new edges" << current_edge << std::endl;
                    continue;
                };

                if (!isDelaunay(current_edge))
                {
                    flip_edge(current_edge);
                }
            }
        }
        std::cout << "Inserted point " << counter << std::endl
                  << std::endl;
        edge_set.clear();

        counter++;
    }
};

void Mesh::incremental_triangulate2()
{
    // Create a face 0 with the three first point
    if (getFacesNb() > 0 || getVerticesNb() == 0)
    {
        std::cout << "Triangulation must be done right after creation of the point cloud" << std::endl;
        return;
    };

    // Create Convex Hull through graham scan
    std::cout << "Creating convex hull" << std::endl;
    // The point the closest of the centroid we could find
    unsigned int center = 0;
    convex_hull = grahamScan(vertices, center);

    if (convex_hull.size() == vertices.size())
    {
        return;
    };
    for (int i = 0; i < convex_hull.size(); i++)
    {
        std::cout << "Convexhull member " << convex_hull[i] << " " << vertices[convex_hull[i]] << std::endl;
    }

    // First insertion
    size_t convex_hull_size = convex_hull.size();
    for (int i = 0; i < convex_hull_size; i++)
    {
        swapVerticeFace(convex_hull[i]) = makeFace(center, convex_hull[i % (convex_hull_size)], convex_hull[(i + 1) % (convex_hull_size)]);
    }
    for (int i = 0; i < convex_hull_size; i++)
    {
        faces[i].neighbor[2] = ((i - 1) + convex_hull_size) % convex_hull_size;
        faces[i].neighbor[1] = (i + 1) % convex_hull_size;
    }

    lawson(*this);
    //  For this step, we won't need to consider the insertion outside the convex hull at all
    int counter = 0;
    int size = vertices.size();
    std::vector<unsigned int> pre_inserted(convex_hull);
    std::cout << "Center is " << center << " " << vertices[center] << std::endl
              << std::endl;
    pre_inserted.push_back(center);
    // Should sort again to get back the correct point of the convex hull
    std::queue<Edges> edge_queue;
    EdgeSet edge_set;

    // std::vector<unsigned int> traversal = generateUniqueRandomNumbers(size, pre_inserted);
    while (counter < vertices.size())
    {
        edge_set.clear();
        bool skip = 0;
        for (int i = 0; i < pre_inserted.size(); i++)
        {
            if (counter == pre_inserted[i])
            {
                skip = 1;
            }
        }
        if (skip == 0)
        {
            std::cout << "Inserting point number " << vertices[counter] << " " << vertices[counter] << std::endl;
            unsigned face;

            // Pre extract "border-edge"
            Faces face_backup = insert_point_convexless(counter, face);
            std::array<unsigned, 3> new_faces = {face, faces.size() - 1, faces.size() - 2};

            for (size_t i = 0; i < 3; i++)
            {

                extractEdgesFromFace(edge_queue, edge_set, new_faces[i]);
                while (!edge_queue.empty())
                {
                    Edges current_edge = edge_queue.front();
                    std::cout << current_edge << std::endl;

                    edge_queue.pop();
                    // We avoid flipping the new insertion
                    if (current_edge.contains(counter))
                    {
                        continue;
                    };

                    if (!isDelaunay(current_edge))
                    {
                        flip_edge(current_edge);
                    }
                }
            }
            edge_set.clear();
        }

        counter++;
    }
}
/*
std::vector<unsigned int>  Mesh::incremental_triangulate2_step_start()

{
    if (getFacesNb() > 0 || getVerticesNb() == 0)
    {
        std::cout << "Triangulation must be done right after creation of the point cloud" << std::endl;
        return;
    };

    // Create Convex Hull through graham scan
    std::cout << "Creating convex hull" << std::endl;
    // The point the closest of the centroid we could find
    unsigned int center = 0;
    convex_hull = grahamScan(vertices, center);

    if (convex_hull.size() == vertices.size())
    {
        return;
    };
    // First insertion
    size_t convex_hull_size = convex_hull.size();
    for (int i = 0; i < convex_hull_size; i++)
    {
        swapVerticeFace(convex_hull[i]) = makeFace(center, convex_hull[i % (convex_hull_size)], convex_hull[(i + 1) % (convex_hull_size)]);
    }
    for (int i = 0; i < convex_hull_size; i++)
    {
        faces[i].neighbor[2] = ((i - 1) + convex_hull_size) % convex_hull_size;
        faces[i].neighbor[1] = (i + 1) % convex_hull_size;
    }

    lawson(*this);
    std::vector<unsigned int> pre_inserted(convex_hull);
    pre_inserted.push_back(center);

    return pre_inserted;
}

void Mesh::incremental_triangulate2_step(std::vector<unsigned int>& pre_inserted)
{
    // Create a face 0 with the three first point
   int counter = 0;
    int center = 0;
    if (convex_hull.empty())
    {
        pre_inserted = incremental_triangulate2_step_start();
    }

    //  For this step, we won't need to consider the insertion outside the convex hull at all
    int counter = 0;
    int size = vertices.size();
    std::queue<Edges> edge_queue;
    EdgeSet edge_set;
    // std::vector<unsigned int> traversal = generateUniqueRandomNumbers(size, pre_inserted);
    edge_set.clear();
    bool skip = 0;
    for (int i = 0; i < pre_inserted.size(); i++)
    {
        if (counter == pre_inserted[i])
        {
            skip = 1;
        }
    }
    if (skip == 0)
    {
        std::cout << "Inserting point number " << vertices[counter] << " " << vertices[counter] << std::endl;
        unsigned face;

        // Pre extract "border-edge"
        Faces face_backup = insert_point_convexless(counter, face);
        std::array<unsigned, 3> new_faces = {face, faces.size() - 1, faces.size() - 2};

        for (size_t i = 0; i < 3; i++)
        {

            extractEdgesFromFace(edge_queue, edge_set, new_faces[i]);
            while (!edge_queue.empty())
            {
                Edges current_edge = edge_queue.front();
                std::cout << current_edge << std::endl;

                edge_queue.pop();
                // We avoid flipping the new insertion
                if (current_edge.contains(counter))
                {
                    continue;
                };

                if (!isDelaunay(current_edge))
                {
                    flip_edge(current_edge);
                }
            }
        }
        edge_set.clear();
    }

    counter++;
}*/

Faces Mesh::insert_point_convexless(const unsigned int &new_point, unsigned int &vertices_face)
{
    // Identify if this point belong to a face
    vertices_face = identify_point_face(vertices[new_point]);
    Faces back_up = faces[vertices_face];

    if (static_cast<unsigned int>(-1) == vertices_face)
    {
        std::cout << "The face of this point is " << vertices_face << ", no edge will be added :" << std::endl
                  << std::endl;
    }
    else
    {

        split_triangle(new_point, vertices_face);
    }
    return back_up;
}

Faces Mesh::insert_point_convexless(const int &coord_x, const int &coord_y, const int &coord_z, unsigned int &vertices_face)
{
    // Identify if this point belong to a face
    vertices.emplace_back(coord_x, coord_y, coord_z);
    vertices_face = identify_point_face(vertices[vertices.size() - 1]);
    Faces back_up = faces[vertices_face];
    if (static_cast<unsigned int>(-1) == vertices_face)
    {
        std::cout << "The face of this point is " << vertices_face << "  :" << std::endl
                  << std::endl;
        vertices.pop_back();
    }
    else
    {
        split_triangle(vertices.size() - 1, vertices_face);
    }
    return back_up;
}

void Mesh::split_triangle(unsigned int new_vert_index, unsigned int &new_vertices_face)
{
    // If the insertion face is not know, we start identifying it

    // Init
    Faces back_up = faces[new_vertices_face];
    unsigned vert1 = faces[new_vertices_face].vertices[0];
    unsigned vert2 = faces[new_vertices_face].vertices[1];
    unsigned vert3 = faces[new_vertices_face].vertices[2];

    // Push three new faces and set up their fae
    // Maintained face is the one with vert1, vert2

    faces[new_vertices_face].vertices[2] = new_vert_index;
    faces.emplace_back(new_vert_index, vert2, vert3, faces[new_vertices_face]);
    faces.emplace_back(vert1, new_vert_index, vert3, faces[new_vertices_face]);
    // Maintained face is also the opposite of edge vert[2]
    faces[new_vertices_face].neighbor[0] = faces.size() - 2;
    faces[new_vertices_face].neighbor[1] = faces.size() - 1;

    // For other faces, faces at same indices as new_vert_index is untouched for now
    faces[faces.size() - 2].neighbor[1] = faces.size() - 1;
    faces[faces.size() - 2].neighbor[2] = new_vertices_face;
    faces[faces.size() - 1].neighbor[0] = faces.size() - 2;
    faces[faces.size() - 1].neighbor[2] = new_vertices_face;

    // Necessary for easy circulation
    // Update vert3 as thetr is a chance it see itself as incident to "new_vertices_face"
    vertices[vert3].face = faces.size() - 2;
    vertices[vert2].face = faces.size() - 2;
    vertices[vert1].face = faces.size() - 1;
    vertices[new_vert_index].face = new_vertices_face;

    // May require more care
    // At last for each of tthe neighboring oppostite to the added vertices

    if (faces[faces.size() - 2].neighbor[0] == new_vertices_face)
    {
        faces[faces.size() - 2].neighbor[0] = faces.size() - 2;
    }
    else
    { // Handle neighbor triangle
        Faces &neighbor = faces[faces[faces.size() - 2].neighbor[0]];
        for (int i = 0; i < neighbor.neighbor.size(); i++)
        {
            if (neighbor.neighbor[i] == new_vertices_face)
            {
                neighbor.neighbor[i] = faces.size() - 2;
                break;
            }
        }
    }
    if (faces[faces.size() - 1].neighbor[1] == new_vertices_face)
    {
        faces[faces.size() - 1].neighbor[1] = faces.size() - 1;
    }
    else
    { // Handle neighbor triangle
        Faces &neighbor = faces[faces[faces.size() - 1].neighbor[1]];
        for (int i = 0; i < neighbor.neighbor.size(); i++)
        {
            if (neighbor.neighbor[i] == new_vertices_face)
            {
                neighbor.neighbor[i] = faces.size() - 1;
                break;
            }
        }
    }
}

bool Mesh::edgeCoherence(Edges edge, unsigned int face1, unsigned int face2)
{
    bool resultf1v2 = false;
    bool resultf2v1 = false;
    bool resultf1v1 = false;
    bool resultf2v2 = false;
    for (int i = 0; i < 3; i++)
    {
        if (faces[face1].vertices[i] == edge.v1)
        {
            resultf1v1 = true;
        }
        if (faces[face1].vertices[i] == edge.v2)
        {
            resultf1v2 = true;
        }
        if (faces[face2].vertices[i] == edge.v1)
        {
            resultf2v1 = true;
        }
        if (faces[face2].vertices[i] == edge.v2)
        {
            resultf2v2 = true;
        }
    }
    return resultf1v1 & resultf1v2 & resultf2v1 & resultf2v2;
}

bool Mesh::edgeCoherence(Edges edge)
{
    bool resultf1v2 = false;
    bool resultf2v1 = false;
    bool resultf1v1 = false;
    bool resultf2v2 = false;

    for (int i = 0; i < 3; i++)
    {
        if (faces[edge.f1].vertices[i] == edge.v1)
        {
            resultf1v1 = true;
        }
        if (faces[edge.f1].vertices[i] == edge.v2)
        {
            resultf1v2 = true;
        }
        if (faces[edge.f2].vertices[i] == edge.v1)
        {
            resultf2v1 = true;
        }
        if (faces[edge.f2].vertices[i] == edge.v2)
        {
            resultf2v2 = true;
        }
    }
    return resultf1v1 & resultf1v2 & resultf2v1 & resultf2v2;
}

bool Mesh::isDelaunay(Edges edge)
{

    std::vector<unsigned int> edge_faces;

    Mesh::Circulator_Face itv1 = incident_faces_convex(edge.v1);
    int counter_face_search = 0;
    // std::cout << "In Delaunay check" << std::endl;
    //  Get the worrect face
    for (int i = 0; i < itv1.size(); i++, itv1++)
    {
        Mesh::Circulator_Face itv2 = incident_faces_convex(edge.v2);
        for (int j = 0; j < itv2.size(); j++, itv2++)
        {
            if (*itv1 == *itv2)
            {
                edge_faces.push_back(*itv1);
                break;
            }
        }
    }

    // On convex hull the circuclator may be unable to go further
    // This wasn't took into account previously
    if (edge_faces.size() < 2)
    {
        std::cout << "Early exit for invalid face" << std::endl;
        // May result from previous flip
        return true;
    };
    // Cercle circonscrit des triangle incluant
    // Faces shared_face = faces[edge.f1];
    Faces shared_face = faces[edge_faces[0]];
    Faces opposite_face = faces[edge_faces[1]];
    unsigned third_vertice = shared_face.vertices[return_opposite_vertices(edge, shared_face.vertices)];
    unsigned fourth_vertice = opposite_face.vertices[return_opposite_vertices(edge, opposite_face.vertices)];

    if (isInsideCircumcircle(vertices[edge.v1], vertices[edge.v2], vertices[third_vertice], vertices[fourth_vertice]))
    {
        return false;
    }
    if (isInsideCircumcircle(vertices[edge.v1], vertices[edge.v2], vertices[fourth_vertice], vertices[third_vertice]))
    {
        return false;
    }

    return true;
}

/*
Mesh boywerWatson(Mesh& mesh)
{
    // We choose  not to use the mesh structure for simplicity
    // Look for the min and max

    toto.createSuperTriangle();
    std::vector<Faces> faces;
    std::vector<Vertices> vertices =


    std::cout << faces[0] << std::endl;
    int vertex_count = 0;
    int facecounter = 0;
    // Every verticees entry point into the triangulation
    for (int i = 0; i < vertices.size() - 3; ++i)
    {
        // For each iteration adding new point, the face to remove.
        std::vector<Faces> invalid_faces;
        std::vector<Edges> edges_vec;
        std::unordered_map<Edges, int, Edges::Edgeshash> edge_count;

        // Get Bad triangle
        for (auto &face : faces)
        {
            if (isInsideCircumcircle4(vertices[face.vertices[0]],
                                      vertices[face.vertices[1]],
                                      vertices[face.vertices[2]], vertices[i]))
            { // Insert edges not tied to more than two bad triangle
                invalid_faces.push_back(face);
                for (int e = 0; e < 3; e++)
                {
                    Edges edge(face.vertices[e], face.vertices[(e + 1) % 3]);
                    edge_count[edge]++;
                }
            }
        }

        // Remove invaldi faces
        for (auto &face_to_remove : invalid_faces)
        {
            faces.erase(std::remove_if(faces.begin(), faces.end(),
                                       [&face_to_remove](const Faces &f)
                                       { return f == face_to_remove; }),
                        faces.end());
        }

        // Remove duplicate edges (polygon boundary edge)
        for (const auto &edge : edge_count)
        {
            if (edge.second == 1)
            {
                edges_vec.push_back(edge.first);
            }
        }

        for (const auto &edges : edges_vec)
        {
            if (orientation_test_2d(vertices[edges.v1], vertices[edges.v2], vertices[i]) > 0)
            {
                Faces f = Faces(edges.v1, edges.v2, i);
                faces.push_back(f);
            }
            else
            {
                Faces f = Faces(i, edges.v2, edges.v1);
                faces.push_back(f);
            }
        }
        vertex_count++;
    }
    std::cout << "All point" << std::endl;

    faces.erase(std::remove_if(faces.begin(), faces.end(),
                               [&](const Faces &face)
                               {
                                   return (return_local_indices(face, vertices.size() - 1) != 3) ||
                                          (return_local_indices(face, vertices.size() - 3) != 3) ||
                                          (return_local_indices(face, vertices.size() - 2) != 3);
                               }),
                faces.end());
    return Mesh(vertices, faces);
}
*/
unsigned getNeighbors(const Faces &curr_face, unsigned &indice, std::function<unsigned(const unsigned &)> direction)
{
    // Return the face opposed to local indices
    return curr_face.neighbor[direction(indice)];
}

// Function handling removal and rebinding of vertices
// Probably to put in "vertices simplification function"

float in_triangle_test_2d(const Mesh &mesh, const unsigned int &face, const Vertices &point)
{
    unsigned vert0 = (mesh.getFace(face)).vertices[0];
    unsigned vert1 = (mesh.getFace(face)).vertices[1];
    unsigned vert2 = (mesh.getFace(face)).vertices[2];

    // Signed area abp
    float sign_area_edgea = orientation_test_2d(mesh.getVertice(vert0),
                                                mesh.getVertice(vert1), point);
    // Signed area bcp
    float sign_area_edgeb = orientation_test_2d(mesh.getVertice(vert1),
                                                mesh.getVertice(vert2), point);

    // Signed area cap
    float sign_area_edgec = orientation_test_2d(mesh.getVertice(vert2),
                                                mesh.getVertice(vert0), point);

    if (sign_area_edgea == 0 || sign_area_edgeb == 0 || sign_area_edgec == 0)
    {
        return 0;
    }

    // TODO recheck
    return (sign_area_edgea > 0 && sign_area_edgeb > 0 && sign_area_edgec > 0) ||
                   (sign_area_edgea < 0 && sign_area_edgeb < 0 && sign_area_edgec < 0)
               ? 1 // Inside
               : -1;
}

float in_triangle_test_2d(std::vector<Vertices> &vertices, const Faces &face, unsigned int &point)
{
    unsigned vert0 = face.vertices[0];
    unsigned vert1 = face.vertices[1];
    unsigned vert2 = face.vertices[2];

    // Signed area abp
    float sign_area_edgea = orientation_test_2d(vertices[vert0],
                                                vertices[vert1], vertices[point]);
    // Signed area bcp
    float sign_area_edgeb = orientation_test_2d(vertices[vert1],
                                                vertices[vert2], vertices[point]);

    // Signed area cap
    float sign_area_edgec = orientation_test_2d(vertices[vert2],
                                                vertices[vert0], vertices[point]);

    if (sign_area_edgea == 0 || sign_area_edgeb == 0 || sign_area_edgec == 0)
    {
        return 0;
    }

    // TODO recheck
    return (sign_area_edgea > 0 && sign_area_edgeb > 0 && sign_area_edgec > 0) ||
                   (sign_area_edgea < 0 && sign_area_edgeb < 0 && sign_area_edgec < 0)
               ? 1 // Inside
               : -1;
}