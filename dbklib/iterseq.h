#pragma once
#include <array>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

template<int N>
struct node_t {
	std::array<int,N> prob {};
};



template<int N_tree, int N_node>
struct tree_t {
	std::array<node_t<N_node>,N_tree> pos {};
};



template<int N_tree, int N_node>
int print_iterative(tree_t<N_tree,N_node> tree) {
	std::stack<std::array<int,2>> stk_taddr;
	std::array<int,2> cpos {};
	stk_taddr.push({0,0});

	std::string s {};
	std::vector<std::string> vs {};

	while (!stk_taddr.empty()) {
		cpos = stk_taddr.top();
		stk_taddr.pop();

		for (int i=0; i<(N_tree-cpos[0]); ++i) {
			if (vs.size() == 0) { break; }  // Occurs only on the first iteration
			vs.pop_back();
		}

		// On entering this inner loop, cpos[0] takes its value from whatever was popped
		// from the stack, however, on subsequent iterations cpos[0] is set to 0 (see bottom
		// of loop).  
		// TODO:  Would the loop be simpler if instead i pushed the "address" of the present
		// node and let the loop calculate the next?
		for (true; cpos[0]<N_tree; ++cpos[0]) {
			// Node processing
			if (tree.pos[cpos[0]].prob[cpos[1]] != 0) {
				s = "{" + std::to_string(cpos[0]) + "," + std::to_string(cpos[1]) + "}=" 
					+ std::to_string(tree.pos[cpos[0]].prob[cpos[1]]) + "->";
			} else {
				s = " ";
			}
			vs.push_back(s);

			if (cpos[1] < (N_node-1)) {
				// {cpos[0],cpos[1]+1} is the "address" of the next node connected
				// to the present node; in a breadth-first traversal, this is where we
				// would move to next.  
				stk_taddr.push({cpos[0],cpos[1]+1});
			}

			cpos[1]=0;  // On next tree node, want to start @ 0
		}

		for (const auto& e : vs) {
			std::cout << e;
		}
		std::cout << std::endl;
	}

	return 0;
}







template<int N_tree, int N_node>
int print_recursive(tree_t<N_tree,N_node> tree, std::array<int,2> cpos, std::string s) {
	for (cpos[1]=0; cpos[1]<N_node; ++cpos[1]) {
		if (tree.pos[cpos[0]].prob[cpos[1]] != 0) {
			s += "{" + std::to_string(cpos[0]) + "," + std::to_string(cpos[1]) + "}=" 
				+ std::to_string(tree.pos[cpos[0]].prob[cpos[1]]) + "->";
		} else {
			s += " ";
		}
		//std::cout << s;

		if (cpos[0] < (N_tree-1)) {
			++cpos[0];
			print_recursive(tree,{cpos[0],0},s);
		}
	}
	std::cout << s << std::endl;
	return 0;
}


/*

	while (!stk_taddr.empty()) {
		cpos = stk_taddr.top();
		stk_taddr.pop();

		for (int i=0; i<(N_tree-cpos[0]); ++i) {
			if (vs.size() == 0) { break; }  // Occurs only on the first iteration
			vs.pop_back();
		}

		// On entering this inner loop, cpos[0] takes its value from whatever was popped
		// from the stack, however, on subsequent iterations cpos[0] is set to 0 (see bottom
		// of loop).  
		// TODO:  Would the loop be simpler if instead i pushed the "address" of the present
		// node and let the loop calculate the next?
		for (true; cpos[0]<N_tree; ++cpos[0]) {
			// Node processing
			if (tree.pos[cpos[0]].prob[cpos[1]] != 0) {
				s = "{" + std::to_string(cpos[0]) + "," + std::to_string(cpos[1]) + "}=" 
					+ std::to_string(tree.pos[cpos[0]].prob[cpos[1]]) + "->";
			} else {
				s = " ";
			}
			vs.push_back(s);

			if (cpos[1] < (N_node-1)) {
				// {cpos[0],cpos[1]+1} is the "address" of the next node connected
				// to the present node; in a breadth-first traversal, this is where we
				// would move to next.  
				stk_taddr.push({cpos[0],cpos[1]+1});
			}

			cpos[1]=0;  // On next tree node, want to start @ 0
		}

		for (const auto& e : vs) {
			std::cout << e;
		}
		std::cout << std::endl;
	}

	return 0;
}*/



