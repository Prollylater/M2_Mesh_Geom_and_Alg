#pragma once
#include "Mesh_IO.h"


// Retourne le sommet ne correspondant à aucun de ceux du bord


void map_edge(std::vector<Faces> &faces, std::vector<Vertices> &vertices)
{
    // Assuming an edge will only have two faces
    std::unordered_map<edges, edges_face, PairHash> triangle_map;
    int curr_face = 0;

    // Current indices
    for (Faces &face : faces)
    {
        // for each edges they will be stored with in growing order
        auto sorted_pair = [](unsigned x, unsigned y)
        {
            return std::make_pair(std::min(x, y), std::max(x, y));
        };

        // std::cout << "La face" << curr_face << "a pour vertex :  ";

        // Opposite to vertices 2
        edges edgea = sorted_pair(face.vertices[0], face.vertices[1]);
        // Opposite to vertices 0
        edges edgeb = sorted_pair(face.vertices[1], face.vertices[2]);
        // Opposite to vertices 1
        edges edgec = sorted_pair(face.vertices[2], face.vertices[0]);

        // Associe chaque vertex à une face "infinie"
        vertices[face.vertices[0]].face = curr_face;
        vertices[face.vertices[1]].face = curr_face;
        vertices[face.vertices[2]].face = curr_face;

        // Also assuming we only come here once by face and edge
        // If key never inserted -> true -> add the faces
        if (triangle_map.insert(std::pair<edges, edges_face>(edgea, edges_face())).second)
        {
            // Add the face as neigbor to other face of the edges
            triangle_map[edgea].first = curr_face;
        }
        else
        {
            triangle_map[edgea].second = curr_face;
            // Create the link
            // Go through neigbor to have the unsigned int
            int indexa = return_opposite_vertices(edgea, faces[triangle_map[edgea].first].vertices);
            int indexb = return_opposite_vertices(edgea, faces[triangle_map[edgea].second].vertices);

            faces[triangle_map[edgea].first].neighbor[indexa] = (triangle_map[edgea].second);
            faces[triangle_map[edgea].second].neighbor[indexb] = (triangle_map[edgea].first);
        }

        if (triangle_map.insert(std::pair<edges, edges_face>(edgeb, edges_face())).second)
        {
            triangle_map[edgeb].first = curr_face;
        }
        else
        {
            triangle_map[edgeb].second = curr_face;
            // std::cout << "La face" << triangle_map[edgeb].first << "a pour voisin en b:  " << triangle_map[edgeb].second << std::endl;
            int indexa = return_opposite_vertices(edgeb, faces[triangle_map[edgeb].first].vertices);
            int indexb = return_opposite_vertices(edgeb, faces[triangle_map[edgeb].second].vertices);

            faces[triangle_map[edgeb].first].neighbor[indexa] = (triangle_map[edgeb].second);
            faces[triangle_map[edgeb].second].neighbor[indexb] = (triangle_map[edgeb].first);
        }

        if (triangle_map.insert(std::pair<edges, edges_face>(edgec, edges_face())).second)
        {
            triangle_map[edgec].first = curr_face;
        }
        else
        {

            triangle_map[edgec].second = curr_face;
            // std::cout << "La face" << triangle_map[edgec].first << "a pour voisin en c:  " << triangle_map[edgec].second << std::endl;
            // Create the link
            int indexa = return_opposite_vertices(edgec, faces[triangle_map[edgec].first].vertices);
            int indexb = return_opposite_vertices(edgec, faces[triangle_map[edgec].second].vertices);
            faces[triangle_map[edgec].first].neighbor[indexa] = (triangle_map[edgec].second);
            faces[triangle_map[edgec].second].neighbor[indexb] = (triangle_map[edgec].first);
        }

        curr_face++;
    }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
} 





Mesh load_mesh_faceless(const char *filename, bool choice)
{
    // Constructor to create streamer + open
    std::ifstream input(filename);

    if (!input.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        Mesh a;
        return a;
    }
    std::cout << "Parsing mesh file" << std::endl;

    std::vector<Vertices> vertices;
    std::vector<Faces> faces;

    // Reading from the file
    std::stringstream buffer;
    int vertices_lines = 0;
    int faces_lines = 0;
    int edges_lines = 0;

    buffer << input.rdbuf();

    std::string data = buffer.str();

    input.close();

    std::istringstream lines(data);

    std::string line;
    int var = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    std::cout << "Parsing Vertices" << std::endl;

    while (std::getline(lines, line))
    {

        if (line.substr(0, 3) == "OFF" || line[0] == '#')
        {
            continue;
        }

        if (vertices_lines == 0)
        {
            if (sscanf(line.c_str(), "%d %d %d", &vertices_lines, &faces_lines, &edges_lines) != 3)
            {
                continue;
            }
        }
        else
        {
            // Ajouter les vertex trouvés
            if (vertices_lines > vertices.size())
            {
                if (sscanf(line.c_str(), "%f %f %f", &x, &y, &z) == 3)
                {
                    Vertices new_vertex(x, y, z * choice);
                    vertices.emplace_back(new_vertex);
                    continue;
                }
            }
        }

        break;
    }

    std::cout << "Finalizing mesh structure creation" << std::endl;
    return Mesh(std::move(vertices), {});
}


Mesh load_mesh(const char *filename)
{
    // Constructor to create streamer + open
    std::ifstream input(filename);

    if (!input.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        Mesh a;
        return a;
    }
    std::cout << "Parsing mesh file" << std::endl;

    std::vector<Vertices> vertices;
    std::vector<Faces> faces;

    // Reading from the file
    std::stringstream buffer;
    int vertices_lines = 0;
    int faces_lines = 0;
    int edges_lines = 0;

    buffer << input.rdbuf();

    std::string data = buffer.str();

    input.close();

    std::istringstream lines(data);

    std::string line;
    int var = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    std::cout << "Parsing Vertices" << std::endl;

    while (std::getline(lines, line))
    {

        if (line.substr(0, 3) == "OFF" || line[0] == '#')
        {
            continue;
        }

        if (vertices_lines == 0)
        {
            if (sscanf(line.c_str(), "%d %d %d", &vertices_lines, &faces_lines, &edges_lines) != 3)
            {
                continue;
            }
        }
        else
        {
            // Ajouter les vertex trouvés
            if (vertices_lines > vertices.size())
            {
                if (sscanf(line.c_str(), "%f %f %f", &x, &y, &z) == 3)
                {
                    Vertices new_vertex(x, y, z);
                    vertices.emplace_back(new_vertex);
                    continue;
                }
            }
        }

        var = static_cast<unsigned int>(line[0]) - '0';

        std::string format;
        for (int i = 0; i < var; ++i)
        {
            format += "%f ";
        }
        format.pop_back();
        if (faces_lines > faces.size())
        {
            if (sscanf(line.substr(2).c_str(), format.c_str(), &x, &y, &z) != var)
            {
                continue;
            }
            else
            {
                faces.push_back(Faces(x, y, z));
                continue;
            }
        }
    }
    std::cout << "Parsing faces" << std::endl;

    map_edge(faces, vertices);
    std::cout << "Finalizing mesh structure creation" << std::endl;
    return Mesh(std::move(vertices), std::move(faces));
}

// TODO More than obj ?
// TODO: const Mesh&
bool write_mesh(const char *filename, Mesh &mesh, bool normal, bool curvature , const std::vector<float> &texture_coordinate)
{

    std::cout << "Starting writing" << std::endl;

    // Create and open a file
    std::ofstream mesh_file(filename);

    if (!mesh_file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return 0;
    }

    for (auto vert_it = mesh.vertices_begin(); vert_it != mesh.vertices_end(); vert_it++)
    {
        mesh_file << "v " << (*vert_it).x /**< setprecision(2)*/
                  << " " << (*vert_it).y
                  << " " << (*vert_it).z << "\n";
    }
    int counter = 0;

    std::cout << "Vertices written" << std::endl;
    if (curvature && (texture_coordinate.size() == 0))
    {

        std::vector<float> curvature = mesh.compute_mean_curvature_f();
        for (counter = 0; counter < curvature.size(); counter++)
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
            mesh_file << "vt " << val << " " << 0 << "\n"; 
        }
    }

    std::cout << "Texture coordinate written" << std::endl;

    // Texture coordinate must be passed currently
    /*
    if(texture_coordinate.size() > 0){
    for (auto vert_it = mesh.vertices_begin(); vert_it != mesh.vertices_end(); vert_it++)
    {
        mesh_file << "vt "<<texture_coordinate[1] // it's u
                << " " << texture_coordinate[1] // it"s v
                //it's not implemented
    }
    }*/

    if (normal)
    {
        std::vector<Vertices> normals = mesh.compute_mesh_normal();
        for (counter = 0; counter < normals.size(); counter++)
        {
            mesh_file << "vn " << normals[counter].x
                      << " " << normals[counter].y
                      << " " << normals[counter].z << "\n";
        }
        for (auto face_it = mesh.faces_begin(); face_it != mesh.faces_end(); face_it++)
        {
            mesh_file << "f " << (*face_it).vertices[0] + 1 << "/" << (*face_it).vertices[0] + 1 << "/" << (*face_it).vertices[0] + 1
                      << " " << (*face_it).vertices[1] + 1 << "/" << (*face_it).vertices[1] + 1 << "/" << (*face_it).vertices[1] + 1
                      << " " << (*face_it).vertices[2] + 1 << "/" << (*face_it).vertices[2] + 1 << "/" << (*face_it).vertices[2] + 1
                      << "\n";
             
        }
    }
    else
    {
        for (auto face_it = mesh.faces_begin(); face_it != mesh.faces_end(); face_it++)
        {
            mesh_file << "f " << (*face_it).vertices[0] + 1
                      << " " << (*face_it).vertices[1] + 1
                      << " " << (*face_it).vertices[2] + 1 << "\n";
        }
    }

    std::cout << "Normals and faces coordinates written" << std::endl;

    // Close the file
    mesh_file.close();

    std::cout << "Data written!" << std::endl;

    return 0;
};
