#include<iostream>
#include "BucketNode.h"

using namespace std;

BucketNode::BucketNode(){ }

BucketNode::BucketNode(int sNum) {
	studentNum = sNum;
	next = NULL;
}