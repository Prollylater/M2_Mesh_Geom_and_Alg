#include "ImgEditor.h"
#include <iostream>

#include "GlobalStates.h"

static float cam_x = 0.5f;
static float cam_z = 0.0f;
static float cam_y = 0.0f;
static float scale_global = 0.5f;
int triangulationmode = 0;
static bool render = 0;
static int display_curr_idx = 0; // Global for easier access
static bool display_3D = false;
static int im_width, im_height;
static std::vector<Vertices> world_coordinate;
// MainWinSt:: Display is currently in a weird stop as it only serve at init
void ShowImageRenderingArea()
{
    
    // create a file browser instance
    static ImGui::FileBrowser fileDialog;

    // Temporary value created to allow the use of show
    bool show = win_states.isTrue(WinStates::img_area);

    // Variable tied to this windows
    static ImVec4 color_pencil = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    if (/*!show*/ !win_states.isTrue(WinStates::img_area))
    {
        return;
    }

    // ImGui::SetNextWindowSize(ImVec2(900, 500), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_NoTitleBar |*/ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
    // Set the size of the window the first time it appears
    static GLuint display;

    ImGui::Begin("Edit Mode", nullptr, window_flags);
    {
        ImVec2 window_size = ImGui::GetWindowSize();
        im_width = window_size.x;
        im_height = window_size.y;

        // Menu Bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open"))
                {
                    fileDialog.Open();
                }
                if (ImGui::MenuItem("Save"))
                {
                    write_mesh("Saved.obj", appobj::meshobject, false, false);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
        // Menu Bar
        // IMGUI file dialog box

        fileDialog.Display();
        if (fileDialog.HasSelected())
        {
            /*
            ImGui::Begin("Triangulation Options", nullptr, window_flags);
            {
                // Each radio button checks if it's the selected option and updates `selectedOption` if clicked
                if (ImGui::RadioButton("Graham's hull + Incremental", triangulationmode == 0))
                {
                    triangulationmode = 0;
                }
                if (ImGui::RadioButton("Super Trangle + Incremental", triangulationmode == 1))
                {
                    triangulationmode = 1;
                }
                if (ImGui::RadioButton("Bowyer Watson", triangulationmode == 2))
                {
                    triangulationmode = 2;
                }
                 if (ImGui::RadioButton("Real Time Triangulation", triangulationmode == 3))
                {
                    triangulationmode = 3;
                }
                if (ImGui::RadioButton("Already triangulated", triangulationmode == 4))
                {
                    triangulationmode = 4;
                }

                ImGui::Spacing();
                if (ImGui::RadioButton("3D Mesh", display_3D == 1))
                {
                    display_3D = 1;
                }
                ImGui::SameLine();

                if (ImGui::RadioButton("2D Mesh", display_3D == 0))
                {
                    display_3D = 0;
                }

                if (ImGui::Button("Execute Triangulation"))
                {
                    std::string curr_mesh = fileDialog.GetSelected().string();
                    display_states.setState(MainWinSt::normals, appobj::glengine.loadMesh(curr_mesh.c_str(), &display, &im_width, &im_height));
                    std::cout << "Triangulation Done" << std::endl;
                    if (!display_3D)
                    {
                        appobj::glengine.updateTerrainto2D();
                    }
                    render = true;
                    fileDialog.ClearSelected();
                    std::cout << "Triangulation Do2ne" << std::endl;
                }
            }
            ImGui::End();*/
            triangulationmode = 1;
            display_3D = 0;
            std::string curr_mesh = fileDialog.GetSelected().string();
            display_states.setState(MainWinSt::normals, appobj::glengine.loadMesh(curr_mesh.c_str(), &display, &im_width, &im_height));
            std::cout << "Triangulation Done" << std::endl;
            if (!display_3D)
            {
                appobj::glengine.updateTerrainto2D();
            }
            render = true;
            fileDialog.ClearSelected();
            std::cout << "Triangulation Do2ne" << std::endl;
        }

        if (render)
        {
            appobj::glengine.renderMesh(im_width, im_height, display_curr_idx, display_3D, cam_x, cam_y, cam_z, scale_global);
            delaunayPanel(render);
        }
        //  Calculation regarding center child window

        ImVec2 parent_size = ImGui::GetWindowSize();
        ImVec2 parent_pos = ImGui::GetWindowPos();
        //
        // Icons Bar

        if (!display_states.isTrue(MainWinSt::none))
        {
            // TODO offload this to the texture
            glBindTexture(GL_TEXTURE_2D, display);
            ImGui::Image((ImTextureID)(intptr_t)display, parent_size, ImVec2(0, 1), ImVec2(1, 0));

            //  ImGui::Image((ImTextureID)(intptr_t)display, ImVec2(parent_size.getWidth(), im_height), ImVec2(0, 1), ImVec2(1, 0));
        }

        if (ImGui::IsWindowHovered() && render && !display_3D)
        {
            handleClick(im_width, im_height);
        }
    }

    ImGui::End();
}
static float point_height = 0.0f;

void handleClick(int img_w, int img_h)
{
    static Vec<GLfloat> positions;

    static bool isDragging = false;
    static int lastcall = 0;
    lastcall++;

    // Check if the left mouse button was clicked
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {

        std::cout << "You clicked did you not ?" << std::endl;

        // Get the mouse position in screen coordinates
        ImVec2 mouse_pos = ImGui::GetMousePos();
        std::cout << "At ?" << mouse_pos.x << " " << mouse_pos.y << std::endl;

        // Convert to local window coordinates

        ImVec2 local_pos = ImVec2(mouse_pos.x, mouse_pos.y);
        ImGui::Text("Inserting a point at coordinate!");
        ImGui::Text("%f %f", local_pos.x, local_pos.y);

        if ((local_pos.x < img_w && local_pos.x > 0) && (local_pos.y < img_h && local_pos.y > 0))
        {

            // Unproject
            std::cout << "Starting the operations" << std::endl;

            float x_ndc = (2.0f * local_pos.x) / im_width - 1.0f;
            float y_ndc = 1.0f - (2.0f * local_pos.y) / im_height;
            float z_ndc = 1.0f;
            Vec<float> ray_ndc = Vec<float>(x_ndc, y_ndc, z_ndc);
            Vec4 ray_clip = Vec4(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
            Mat<float> inv_proj = Transform::Ortho(0.0f, im_width, 0.0f, im_height, -1.0f, 1.0f);
            Transform::Inverse(inv_proj);
            Vec4 ray_eye = Transform::mat4mult(inv_proj, ray_clip);
            Mat<float> inv_view = Transform::Translation(cam_x, cam_y, cam_z);
            Transform::Inverse(inv_view);
            Vec4 ray_wor = Transform::mat4mult(inv_view, ray_eye);
            Vec<float> ray_worm = Norm(Vec<float>(ray_wor.x, ray_wor.y, ray_wor.z));
            Vertices ray_world = Vertices(ray_worm.x, ray_worm.y, ray_worm.z);

            Vertices origin = Vertices(cam_x, cam_y, cam_z);

            unsigned int insertion_face;
            float t;
            Vertices intersection;
            std::cout << "NDC coordinates: " << x_ndc << ", " << y_ndc << ", " << z_ndc << std::endl;
            std::cout << "Ray clip space: " << ray_clip.x << ", " << ray_clip.y << ", " << ray_clip.z << ", " << ray_clip.w << std::endl;
            std::cout << "Ray eye space: " << ray_eye.x << ", " << ray_eye.y << ", " << ray_eye.z << ", " << ray_eye.w << std::endl;
            std::cout << "Ray world direction: " << ray_world.x << ", " << ray_world.y << ", " << ray_world.z << std::endl;
            std::cout << "Origin: " << origin.x << ", " << origin.y << ", " << origin.z << std::endl;

            std::cout << ray_world << std::endl;
            int resu = appobj::meshobject.identify_intersection(origin, ray_world, world_coordinate, t, intersection);
            if (resu >= 0)
            {

                insertion_face = resu;
                std::cout << "To insertt at " << insertion_face << std::endl;
            }
            else
            {
                std::cout << "No insertion <<std::endl";
                std::cout << intersection << std::endl;
                return;
            }

            // World pointcoordinate
            Vec4 intersection_world = Vec4(intersection.x, intersection.y, 0.0, 1.0);
            Mat<float> inv_model = Transform::Scale(scale_global, scale_global, scale_global);
            Transform::Inverse(inv_model);
            Vec4 world_loocal = Transform::mat4mult(inv_model, intersection_world);
            Vertices local_coord_point = Vertices(world_loocal.x, world_loocal.y, 0.0);

            std::cout << local_coord_point << std::endl;
            // Check the intersected face

            if (delaunay_states.isTrue(DelaunayStates::insert_point))
            {
                appobj::meshobject.insert_point_convexless(local_pos.x, local_pos.y, point_height, insertion_face);
            }
            else if (delaunay_states.isTrue(DelaunayStates::flip_edge))
            {
                // Use mutiple new image
                Vertices position = Vertices(local_pos.x, local_pos.y, point_height);
                insertion_face = appobj::meshobject.identify_point_face(position);
                const Faces &curr_face = appobj::meshobject.getFace(insertion_face);
                Edges edge_a(curr_face.vertices[0], curr_face.vertices[1]);
                Edges edge_b(curr_face.vertices[1], curr_face.vertices[2]);
                Edges edge_c(curr_face.vertices[2], curr_face.vertices[0]);

                // Get the closest edge
                const Edges &closest = appobj::meshobject.closest_Edges(edge_a, edge_b, edge_c, position);
                // If closest is delaunay ext.
                appobj::meshobject.insert_point_convexless(local_pos.x, local_pos.y, point_height, insertion_face);
            }
        }

        // Use normalizedPos as needed
    }
}

void delaunayPanel(bool &show)
{
    if (!show)
    {
        return;
    }
    if (ImGui::Begin("Delaunay Panel"))
    {
        ImGui::SliderFloat("Camera axis X:", &cam_x, -1000.0f, 1000.f);
        ImGui::SliderFloat("Camera axis Y:", &cam_y, -1000.0f, 1000.f);
        ImGui::SliderFloat("Camera axis Z:", &cam_z, -100.0f, 100.f);
        ImGui::SliderFloat("Mesh Scale:", &scale_global, -2.0f, 2.f);

        // TODO Add description
        const char *items[] = {"Insert Point", "Flip_Edge"};
        static int xyz_current_idx = 0;

        const char *combo_preview_value = items[xyz_current_idx];

        if (ImGui::BeginCombo("Mesh Operations", combo_preview_value, ImGuiComboFlags_WidthFitPreview))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (xyz_current_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                {
                    xyz_current_idx = n;
                    if (n == 0)
                    {
                        delaunay_states.setState(DelaunayStates::insert_point, true);
                    }
                    if (n == 1)
                    {
                        delaunay_states.setState(DelaunayStates::flip_edge, true);
                    }
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        // Spatial Coherence
        ImGui::SliderFloat("Inserted Point \nElevation", &point_height, 1.0f, 1000.f);

        ImGui::TextColored(ImVec4(0.2f, 0.5f, 0.4f, 1.0f), "Display mode parameters");
        const char *items_display[] = {"Normal-(NotImplemented)", "WireFrame", "Normal Laplacian", "Curve"};
        const char *display_preview_value = items_display[display_curr_idx];
        // TODO: Laplacian and Curve ?
        if (ImGui::BeginCombo("Display Types", display_preview_value, ImGuiComboFlags_WidthFitPreview))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items_display); n++)
            {
                const bool is_selected = (display_curr_idx == n);
                if (ImGui::Selectable(items_display[n], is_selected))
                {
                    display_curr_idx = n;
                    if (n == 0)
                    {
                        display_curr_idx = n;
                    }
                }

                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        ImGui::Spacing();
        // Each radio button checks if it's the selected option and updates `selectedOption` if clicked
        if (ImGui::RadioButton("3D Mesh", display_3D == 1))
        {
            display_3D = 1;
        }
        ImGui::SameLine();

        if (ImGui::RadioButton("2D Mesh", display_3D == 0))
        {
            display_3D = 0;
        }
        ImGui::Spacing();

        // Dispatch the Result
        if (ImGui::Button("Re-Render"))
        {
            std::cout << "Rerender with 3D as" << display_3D << std::endl;
            appobj::glengine.updateMesh(true, display_states.isTrue(MainWinSt::normals), display_states.isTrue(MainWinSt::curvature), display_3D);
        }

        // Dispatch the Result
        if (!display_3D)
        {
            if (ImGui::Button("Buffer World space coordinate"))
            {
                // Should have multiple call back for this
                world_coordinate.clear();
                Mat<float> proj_temp = Transform::Ortho(0.0f, im_width, 0.0f, im_height, -1.0f, 1.0f);
#pragma omp parallel for
                for (size_t i = 0; i < appobj::meshobject.getVerticesNb(); i++)
                {
                    Vec4 result = Vec4(appobj::meshobject.getVertice(i).x, appobj::meshobject.getVertice(i).y, 0.0f, 1.0f);
                    // Vec4 could have been a mat. But whatever at this point
                    Vec4 result_toworld_coord = Transform::mat4mult(proj_temp, result);
                    world_coordinate.emplace_back(result_toworld_coord.x, result_toworld_coord.y, 0.0);
                }
            }
        }
    }
    ImGui::End();
}