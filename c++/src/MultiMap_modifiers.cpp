#include <stdexcept>
#include "MultiMap.h"


template<typename K, typename D>
void MultiMapCustom<K,D>::left_rotate(const TreeNode *pivot) {
    	// Return if invaild pivot given
	if (!pivot || !pivot->right) {
        throw std::invalid_argument("Pivot cannot be left rotated.");
    }

		// Initializes the needed values
	TreeNode *detach;

		// Detaches right child of pivot and attaches the right-left grandchild of pivot in its place
		// The detached right child is stored in node detach for later use
	detach = pivot->right;
	pivot->right = detach->left;
	if (detach->left) {
        // Used to change the parent of pivot's right-left grandchild to be pivot
        detach->left->parent = pivot;
    }

		// Assignes the detach child's parent to be the same as pivot
	detach->parent = pivot->parent;

		// If pivot was the root node, then make detach the new root node
	if (!detach->parent) {
        root = detach;
    } else {
            // Else, put detach in pivot's position
        if (pivot == pivot->parent->right) {
            pivot->parent->right = detach;
        } else {
            pivot->parent->left = detach;
        }
    }

		// Assigns pivot as a child of detach
	detach->left = pivot;
	pivot->parent = detach;

		// Corrects the descendants of each node
	pivot->descendants -= detach->descendants + 1;
	if (pivot->right) {
		pivot->descendants += pivot->right->descendants + 1;
    }

	detach->descendants = pivot->descendants + 1;
	if (detach->right) {
		detach->descendants += detach->right->descendants + 1;
    }
}

template<typename K, typename D>
void MultiMapCustom<K,D>::right_rotate(const TreeNode *pivot) {
		// Return if invaild pivot given
	if (!pivot || !pivot->left) {
        throw std::invalid_argument("Pivot cannot be right rotated.");
    }

		// Initializes the needed values
	TreeNode *detach;

		// Detaches left child of pivot and attaches the left-right grandchild of pivot in its place
		// The detached left child is stored in node detach for later use
	detach = pivot->left;
	pivot->left = detach->right;
	if (detach->right) {
        // Used to change the parent of pivot's left-right grandchild to be pivot
        detach->right->parent = pivot;
    }

		// Assignes the detach child's parent to be the same as pivot
	detach->parent = pivot->parent;

		// If pivot was the root node, then make detach the new root node
	if (!detach->parent) {
        root = detach;
    } else {
            // Else, put detach in pivot's position
        if (pivot == pivot->parent->left) {
            pivot->parent->left = detach;
        } else {
            pivot->parent->right = detach;
        }
    }
		

		// Assigns pivot as a child of detach
	detach->right = pivot;
	pivot->parent = detach;

		// Corrects the descendants of each node
	detach->descendants++;
	pivot->descendants -= detach->descendants;
	if (pivot->left) {
		pivot->descendants += pivot->left->descendants + 1;
    }
    
	detach->descendants = pivot->descendants + 1;
	if (detach->left) {
		detach->descendants += detach->left->descendants + 1;
    }
}


template<typename K, typename D>
void MultiMapCustom<K,D>::insert_node(const TreeNode *opNode) {
		// Checks for node overflow while increasing size
	if (++size == 0) {
        throw std::overflow_error("Memory overflow"); 
    }

		// Sets opNode's color
	opNode->color = RED;

		// If there is no root node, use the node we just created and finish
	if (!root) {
		root = opNode;
		opNode->parent = 0;
	} else {
			// Initializes the needed values
		TreeNode *temp = 0;
		TreeNode *curr = root;

			// Finds an empty position that opNode can be put in
		while(1) {
				// Adding a child to this node
			curr->descendants++;
				// Sets temp to curr, before storing a child in curr
			temp = curr;

			if ((opNode->key < curr->key) || ((opNode->key == curr->key) && (opNode->data < curr->data))) {
					// If opNode < curr, opNode should be somewhere at the left branch of curr
					// temp is now curr's parent
				curr = curr->left;
					// If curr position is empty, fill it with opNode and finish
				if (!curr) {
					temp->left = opNode;
					break;
				}
			} else {
					// If opNode > curr, opNode should be somewhere at the right branch of curr
					// temp is now curr's parent
				curr = curr->right;
					// If curr position is empty, fill it with opNode and finish
				if (!curr) {
					temp->right = opNode;
					break;
				}
			}
		}

			// Sets opNode's parent appropriately
		opNode->parent = temp;

		// Insertion finished
		// Now begins to rebalance the tree in case the insertion messed something up

			// Loops until opNode's parent isn't red
		while(opNode != root && opNode->parent != root && opNode->parent->color == RED) {
				// Sets temp to be opNode's uncle
				// If left grandparent's child is opNode's parent, right grandparent's child is its uncle
			if (opNode->parent->parent->left == opNode->parent) {
                temp = opNode->parent->parent->right;
            } else {
                // Else, left grandparent's child is its uncle
                temp = opNode->parent->parent->left;
            }

				// If uncle is black, check if the opNode node fits in one of 4 cases (LL, RR, LR, RL)
			if (!temp || temp->color == BLACK) {
				if (opNode == opNode->parent->left) {
					// opNode is left child

						// LL case
						// Swap the colors of opNode's parent and grandparent, then right rotate on opNode's grandparent
					if (opNode->parent == opNode->parent->parent->left) {
							// Swap Colors
						bool color = opNode->parent->color;
						opNode->parent->color = opNode->parent->parent->color;
						opNode->parent->parent->color = color;

							// Right Rotate grandparent
						rightRotate(opNode->parent->parent);
					}

						// RL case
						// Swaps the color of opNode and its grandparent, right rotates opNode's parent, and finally left rotate on opNode's grandparent
					else {
							// Swap Colors
						bool color = opNode->color;
						opNode->color = opNode->parent->parent->color;
						opNode->parent->parent->color = color;

							// Right Rotate Parent
						rightRotate(opNode->parent);

							// Left Rotate grandparent
						leftRotate(opNode->parent->parent);
					}
				} else {
					// opNode is right child

						// RR case
						// Swap the colors of opNode's parent and grandparent, then left rotate on opNode's grandparent
					if (opNode->parent == opNode->parent->parent->right) {
							// Swap Colors
						bool color = opNode->parent->color;
						opNode->parent->color = opNode->parent->parent->color;
						opNode->parent->parent->color = color;

							// Left Rotate grandparent
						leftRotate(opNode->parent->parent);
					}

						// LR case
						// Swaps the color of opNode and its grandparent, left rotates opNode's parent, and finally right rotate on opNode's grandparent
					else {
							// Swap Colors
						bool color = opNode->color;
						opNode->color = opNode->parent->parent->color;
						opNode->parent->parent->color = color;

							// Left Rotate Parent
						leftRotate(opNode->parent);

							// Right Rotate grandparent
						rightRotate(opNode->parent->parent);
					}
				}
			}
				// If uncle is red, color it and its sibling black, but it's parent red
				// Afterwards, begin rebalancing the tree at opNode's grandparent's positon now
			else {
				opNode = opNode->parent->parent;
				opNode->color = RED;
				opNode->left->color = BLACK;
				opNode->right->color = BLACK;
			}
		}
	}

		// Ensures that the root node is black
	root->color = BLACK;
}

template<typename K, typename D>
void MultiMapCustom<K,D>::delete_node(const TreeNode *opNode) {
		// Returns default if given invaild node
	if (!opNode) {
		return;
    }

		// Initializes the needed values
	TreeNode *curr;

	if (opNode->right && opNode->left) {
			// This node has two children

			// Find the node, with the next smallest key in the red-black tree
		curr = opNode->right;
		while (curr->left) {
            curr = curr->left;
        }

			// Exchange data and key with the found node
		opNode->key = curr->key;
		D tempData = opNode->data;
		opNode->data = curr->data;
		curr->data = tempData;

			// Now, act to delete this found node instead
		opNode = curr;
	}
	
		// Decreases the rbt's node count
	size--;

		// Corrects the descendants of the parent nodes
	curr = opNode;
	while (curr) {
		curr->descendants--;
		curr = curr->parent;
	}
	
		// Finds the child node, of the node to be deleted
		// Save this child for later
	if (opNode->left) {
        curr = opNode->left;
    } else {
        curr = opNode->right;
    }

		// Checks if the node to be deleted is the root node
	if (root == opNode) {
			// If so, replace the root node with the child found earlier
		root = curr;
			// Color the new root node black and assign a NULL parent
		if (curr) {
			curr->parent = nullptr;
			curr->color = BLACK;
		}
			// Frees the node scheduled to be deleted
		delete opNode;
		return; // Finish fixup
	}
		// Else, the node to be deleted is not the root
	else {
			// Place the child found earlier in the position the deleted node was in before
		if (curr) {
            curr->parent = opNode->parent;
        }

		if (opNode == opNode->parent->left) {
            opNode->parent->left = curr;
        } else {
            opNode->parent->right = curr;
        }
	}

	// Node deleted
	// Now begins to rebalance the tree in case the deletion messed something up

		// Checks simple cases
			// Checks if the opNode node was red and if there is no child
			// If so, no fixup required
	if (opNode->color == RED && !curr) {
        delete opNode;
        return;
    }

		// Initializes needed variable
	TreeNode *parent = opNode->parent;

	delete opNode; // Frees the deleted node

		// Checks if the replacement is red
		// If so, set it to black and finish
	if (curr && curr->color == RED) {
        curr->color = BLACK;
        return;
    }

	// At this point, the replacement node is now double black
	// We will now promote it

		// Fixup loop
	while (curr != root) {
			// Checks if promoted node is left child
		if (curr == parent->right) {
				// If so, then sibling is left child
			opNode = parent->left;
				// Check if sibling is not NULL
			if (opNode) {
					// Checks if sibling is red and left child
				if (opNode->color == RED) {
						// Colors the appropriate nodes
					parent->color = RED;
					opNode->color = BLACK;

						// Right Rotation of parent
					rightRotate(parent);
					continue; // Go back to start of loop
				}
					// Checks if sibling's left child is red
					// If so, LL case: sibling is black and left child and sibling's left child is red
				else if (opNode->left && opNode->left->color == RED) {
						// Right Rotation of parent
					rightRotate(parent);
				}
					// Checks if sibling's right child is red
					// If so, LR case: sibling is black and left child and sibling's right child is red
				else if (opNode->right && opNode->right->color == RED) {
						// Left Rotation of sibling
					leftRotate(opNode);
						// Right Rotation of parent
					rightRotate(parent);
				}
					// Else, sibling is black and has two black children
				else {
                    goto __Black_Children_Label__;
                }

					// Else, sibling is black and has at least one red child
					// Moves down the blackness
				parent->parent->color = parent->color;
				parent = parent->parent;
				parent->left->color = BLACK;

				if (parent->right) {
                    parent->right->color = BLACK;
                }
				if (curr) {
                    curr->color = BLACK;
                }
				break; // Finish fixup
			}
		}
			// Else promoted node is right child
		else {
				// Thus, sibling is right child
			opNode = parent->right;
				// Check if sibling is not NULL
			if (opNode) {
					// Checks if sibling is red and right child
				if (opNode->color == RED) {
						// Colors the appropriate nodes
					parent->color = RED;
					opNode->color = BLACK;

						// Left Rotation of parent
					leftRotate(parent);
					continue; // Go back to start of loop
				}
					// Checks if sibling's right child is red
					// If so, RR case: sibling is black and right child and sibling's right child is red
				else if (opNode->right && opNode->right->color == RED) {
						// Left Rotation of parent
					leftRotate(parent);
				}
					// Checks if sibling's left child is red
					// If so, RL case: sibling is black and right child and sibling's left child is red
				else if (opNode->left && opNode->left->color == RED) {
						// Right Rotation of sibling
					rightRotate(opNode);
						// Left Rotation of parent
					leftRotate(parent);
				}
					// Else, sibling is black and has two black children
				else {
                    goto __Black_Children_Label__;
                }

					// Else, sibling is black and has at least one red child
					// Moves down the blackness
				parent->parent->color = parent->color;
				parent = parent->parent; // Moves up the parent

				if (parent->left) {
                    parent->left->color = BLACK;
                }
				parent->right->color = BLACK;

				if (curr) {
                    // Sets the promoted node to be black
                    curr->color = BLACK;
                }
				break; // Finish fixup
			}
		}

__Black_Children_Label__:

			// Else, sibling is either NULL or black and has two black children
			// Moves up the blackness
		if (opNode) {
            opNode->color = RED;
        }
		if (curr) {
            curr->color = BLACK;
        }
			// If parent was already black, it is now the promoted node
		if (parent != root && parent->color == BLACK) {
			curr = parent;
			parent = curr->parent;
			continue; // Go back to start of loop with new promoted node
		}
		parent->color = BLACK;
		break; // Finish fixup
	}

		// Ensures that the root node is black
	root->color = BLACK;
	return;
}