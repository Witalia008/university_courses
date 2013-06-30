#ifndef STNLIB_H
#define STNLIB_H

#include "tree/tree.h"
#include "vars/variables.h"

/* List of standart functions */
Node_data print_func(vector<Node_data> &args);
Node_data scan_func(vector<Node_data> &args);
Node_data return_func(vector<Node_data> &args);


/* List of standart operators */
Node_data operator_add(Node_data, int, bool);
Node_data operator_is(Node_data);
Node_data operator_not(Node_data);
Node_data operator_rev(Node_data);
Node_data operator_bit_not(Node_data);
Node_data operator_plusplusL(Node_data);
Node_data operator_plusplusR(Node_data);
Node_data operator_minusx2L(Node_data);
Node_data operator_minusx2R(Node_data);
Node_data operator_unary_minus(Node_data);
Node_data operator_unary_plus(Node_data);

Node_data operator_void(Node_data, Node_data);
Node_data operator_semicolon(Node_data, Node_data);
Node_data operator_coma(Node_data, Node_data);
Node_data bin_bit_op(Node_data, Node_data, char);
Node_data operator_and(Node_data, Node_data);
Node_data operator_or(Node_data, Node_data);
Node_data operator_xor(Node_data, Node_data);
Node_data operator_shr(Node_data, Node_data);
Node_data operator_shl(Node_data, Node_data);
Node_data operator_equal(Node_data, Node_data);
Node_data operator_plus_equal(Node_data, Node_data);
Node_data operator_minus_equal(Node_data, Node_data);
Node_data operator_multi_equal(Node_data, Node_data);
Node_data operator_div_equal(Node_data, Node_data);
Node_data operator_mod_equal(Node_data, Node_data);
Node_data operator_and_equal(Node_data, Node_data);
Node_data operator_or_equal(Node_data, Node_data);
Node_data operator_xor_equal(Node_data, Node_data);
Node_data operator_shl_equal(Node_data, Node_data);
Node_data operator_shr_equal(Node_data, Node_data);
Node_data operator_andx2(Node_data, Node_data);
Node_data operator_orx2(Node_data, Node_data);
Node_data operator_equalx2(Node_data, Node_data);
Node_data operator_not_equal(Node_data, Node_data);
Node_data operator_plus(Node_data, Node_data);
Node_data operator_minus(Node_data, Node_data);
Node_data operator_multi(Node_data, Node_data);
Node_data operator_div(Node_data, Node_data);
Node_data operator_mod(Node_data, Node_data);

Node_data operator_if(Node_data, Node_data, Node_data);

#endif //STNLIB_H
