#include "abstractsyntaxtree.h"
#include <string>

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}

double AbstractSyntaxTree::eval(typename BinaryTree<std::string>::Node* subRoot) const {
    if (subRoot->elem == "+") {
      return eval(subRoot->left) + eval(subRoot->right);
    } else if (subRoot->elem == "-") {
      return eval(subRoot->left) - eval(subRoot->right);
    } else if (subRoot->elem == "*") {
      return eval(subRoot->left) * eval(subRoot->right);
    } else if (subRoot->elem == "/") {
      return eval(subRoot->left) / eval(subRoot->right);
    } else {
      return std::stod(subRoot->elem);
    }
 }
