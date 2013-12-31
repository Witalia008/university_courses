#pragma once
#include "Head.h"
#include "Texture.h"

typedef vector<float> vf;
typedef vector<int> vi;
typedef vector<unsigned> vu;
typedef vector<string> vs;

struct my_model {
    vf vertices, normals, textures, tangents, colours;
    vi starts;
    vu texs, tex_num;
    vs texs_name;
    vf ambient, diffuse, specular, emmisive, shininess;
};

void add_col(vf &cols, aiColor4D col) {
    cols.push_back(col.r);
    cols.push_back(col.g);
    cols.push_back(col.b);
    cols.push_back(col.a);
}

bool load_mesh (string file_name, float coef, my_model &model) {
    Assimp::Importer a;
    const aiScene* scene = a.ReadFile(file_name, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_SortByPType);
    if (!scene) {
        fprintf (stderr, "ERROR: reading mesh %s\n", file_name);
        return false;
    }
    printf ("  %i animations\n", scene->mNumAnimations);
    printf ("  %i cameras\n", scene->mNumCameras);
    printf ("  %i lights\n", scene->mNumLights);
    printf ("  %i materials\n", scene->mNumMaterials);
    printf ("  %i meshes\n", scene->mNumMeshes);
    printf ("  %i textures\n", scene->mNumTextures);
    for (unsigned i = 0; i < scene->mNumMaterials; ++i) {
        aiMaterial* cur = scene->mMaterials[i];
        if (cur->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if (cur->GetTexture(aiTextureType_DIFFUSE, 0, &path) == aiReturn_SUCCESS) {
                string cur_file = path.data;
                cur_file = cur_file.substr(0, cur_file.find_last_of('.') + 1) + "png";
                model.texs_name.push_back(cur_file);
            }
        }
    }
    float col[4];
    for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
        const aiMesh* mesh = scene->mMeshes[m_i];
        //printf ("    %i vertices in mesh\n", mesh->mNumVertices);
        model.starts.push_back(model.vertices.size());
        model.tex_num.push_back(mesh->mMaterialIndex);
        for (int i = 0; i < 3; ++i)
            col[i] = (float) rand() / RAND_MAX;
        col[3] = 1.0f;
        for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
            if (mesh->HasVertexColors(0)) {
                //aiColor4D curcol = aiColor4D(mesh->mColors[v_i]->r;
                add_col(model.colours, mesh->mColors[0][v_i]);
                aiColor4D x = mesh->mColors[0][v_i];
                //printf ("      vp %i (%f,%f,%f,%f)\n", v_i, x.r, x.g, x.b, x.a);
            } else add_col(model.colours, aiColor4D(col[0], col[1], col[2], col[3]));
            if (mesh->HasPositions ()) {
                const aiVector3D* vp = &(mesh->mVertices[v_i]);
                //printf ("      vp %i (%f,%f,%f)\n", v_i, vp->x, vp->y, vp->z);
                model.vertices.push_back (vp->x*coef);
                model.vertices.push_back (vp->y*coef);
                model.vertices.push_back (vp->z*coef);
                aiMaterial *curm = scene->mMaterials[mesh->mMaterialIndex];
                for (int i = 0; i < 4; ++i)
                    model.colours.push_back(col[i]);
                aiColor4D curcol;
                curm->Get(AI_MATKEY_COLOR_DIFFUSE, curcol);
                add_col(model.diffuse, curcol);

                curm->Get(AI_MATKEY_COLOR_AMBIENT, curcol);
                add_col(model.ambient, curcol);

                curm->Get(AI_MATKEY_COLOR_EMISSIVE, curcol);
                add_col(model.emmisive, curcol);

                curm->Get(AI_MATKEY_COLOR_SPECULAR, curcol);
                add_col(model.specular, curcol);
            }
            if (mesh->HasNormals ()) {
                const aiVector3D* vn = &(mesh->mNormals[v_i]);
                //printf ("      vn %i (%f,%f,%f)\n", v_i, vn->x, vn->y, vn->z);
                model.normals.push_back (vn->x);
                model.normals.push_back (vn->y);
                model.normals.push_back (vn->z);
            }
            if (mesh->HasTextureCoords(0)) {
                const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
                //printf ("      vt %i (%f,%f)\n", v_i, vt->x, vt->y);
                model.textures.push_back (vt->x);
                model.textures.push_back (vt->y);
            }
            if (mesh->HasTangentsAndBitangents ()) {
                // NB: could store/print tangents here
            }
        }
    }
    return true;
}