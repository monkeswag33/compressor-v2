#pragma once

// Sizes
static const unsigned int ID_SIZE = sizeof(unsigned short);
static const unsigned int NODE_TYPE_SIZE = sizeof(bool);
static const unsigned int PSEUDO_SIZE = sizeof(bool);
static const unsigned int CHAR_SIZE = sizeof(char);
static const unsigned int COMMON_NODE_SIZE = ID_SIZE + NODE_TYPE_SIZE; // Size of the common node format
static const unsigned int INTERNAL_NODE_SIZE = COMMON_NODE_SIZE + (ID_SIZE * 2); // Size of an internal node
static const unsigned int LEAF_NODE_SIZE = COMMON_NODE_SIZE + CHAR_SIZE + PSEUDO_SIZE; // Size of a leaf node

// Offsets
static const unsigned int ID_OFFSET = 0;
static const unsigned int NODE_TYPE_OFFSET = ID_OFFSET + ID_SIZE;
static const unsigned int COMMON_NODE_OFFSET = NODE_TYPE_OFFSET + NODE_TYPE_SIZE;
static const unsigned int LEFT_CHILD_OFFSET = COMMON_NODE_OFFSET;
static const unsigned int RIGHT_CHILD_OFFSET = LEFT_CHILD_OFFSET + ID_SIZE;
static const unsigned int PSEUDO_OFFSET = COMMON_NODE_OFFSET;
static const unsigned int CHAR_OFFSET = PSEUDO_OFFSET + PSEUDO_SIZE;
static const unsigned int BITS_PER_BYTE = 8;

const unsigned int BUFFER_SIZE = 4096;
