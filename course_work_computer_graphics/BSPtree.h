#ifndef BSP_TREE_H
#define BSP_TREE_H

#include "Face.h"

#include <vector>

struct BSPnode {
    std::vector <Face> faces;
    BSPnode* left{ nullptr }, * right{ nullptr };
};

void build_bsp_tree(BSPnode* parent_node, std::vector <Face>& faces) {
    std::vector <Face> left_vector, parent_vector, right_vector;
    Face parent_face = faces.back(); faces.pop_back();
    parent_vector.push_back(parent_face);
    while (faces.size()) {
        Face current_face = faces.back(); faces.pop_back();
        switch(current_face.located_relative(parent_face)) {
        case Location::FRONT: left_vector.push_back(current_face); break;
        case Location::INSIDE: parent_vector.push_back(current_face); break;
        case Location::BACK: right_vector.push_back(current_face); break;
        case Location::SPLIT:
            std::vector <Face> split_faces = current_face.split(parent_face);
            faces.insert(faces.end(),
                std::make_move_iterator(split_faces.begin()),
                std::make_move_iterator(split_faces.end()));
            break;
        }
    }
    parent_node->faces = parent_vector;
    if (left_vector.size())
        build_bsp_tree(parent_node->left = new BSPnode, left_vector);
    else parent_node->left = nullptr;
    if (right_vector.size())
        build_bsp_tree(parent_node->right = new BSPnode, right_vector);
    else parent_node->right = nullptr;
}

void clear_tree(BSPnode* root) {
    if (!root) return;
    clear_tree(root->left);
    clear_tree(root->right);
    root->faces.clear();
    free(root);
}

#endif // BSP_TREE_H