//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief
 * \copyright
 * \author
 * \date
 */

#ifndef     DMD_MESH_H
#define     DMD_MESH_H

#include    <vector>
#include    <osg/Geometry>

/*!
 * \struct
 * \brief Face description structure
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct face_t
{
    std::vector<int>    indices;
    osg::Vec3           normal;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct dmd_mesh_t
{
    osg::Vec3Array      *vertices;
    std::vector<face_t> faces;
    osg::Vec3Array      *faset_normals;
    osg::Vec3Array      *smooth_normals;
    size_t              vertex_count;
    size_t              faces_count;

    float               tx_max;
    float               ty_max;

    dmd_mesh_t()
        : vertices(nullptr)        
        , faces({})
        , faset_normals(nullptr)
        , smooth_normals(nullptr)
        , vertex_count(0)
        , faces_count(0)
        , tx_max(1.0f)
        , ty_max(1.0f)
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct dmd_multymesh_t
{
    std::vector<dmd_mesh_t *>   meshes;
    osg::Vec3Array              *texture_vertices;
    std::vector<face_t>         texture_faces;
    size_t                      tex_v_count;
    size_t                      tex_f_count;
    bool                        texture_present;

    dmd_multymesh_t()
        : meshes({})
        , texture_vertices(nullptr)
        , texture_faces({})
        , tex_v_count(0)
        , tex_f_count(0)
        , texture_present(true)
    {

    }
};

#endif // DMD_MESH_H