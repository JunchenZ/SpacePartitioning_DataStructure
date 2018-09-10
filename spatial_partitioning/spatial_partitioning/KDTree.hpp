#pragma once
#include "Point.hpp"
#include <memory>
#include <queue>
#include <algorithm>

using namespace std;

template<int Dimension>
class KDTree{
public:
    
    KDTree(const std::vector<Point<Dimension> >& points){
        vector<Point<Dimension>> myPoints = points;
        root = std::unique_ptr<Node<0>>(new Node<0> (myPoints.begin(), myPoints.end()));
    }
    
private:

    template<int SplitDimension> //Don't store the split dimension explicitly
    struct Node{
        Point<Dimension> p;
        //The children will have the "next" splitting dimension
        //Since this is part of the type, we can't "forget" to set it properly... nice!
        std::unique_ptr<Node< (SplitDimension + 1)%Dimension> >  left, right;
        
        /*
         We'll use iterators to describe the chunk of our points array that belong to this node/subtree
         */
        template<typename Iter>
        Node(Iter begin, Iter end)
        {
            //Our children (if we have any) will use the "next" splitting dimension
            using ChildType = Node<(SplitDimension +1)%Dimension>;
            auto middle = begin + (end - begin) / 2;
            
            CompareBy<SplitDimension> compareByX;
            nth_element(begin, middle, end, compareByX);
            p = *middle;
            
            if (begin != middle) {
                left = unique_ptr<ChildType>(new ChildType(begin, middle));
            }
            if (middle + 1 != end) {
                right = unique_ptr<ChildType>(new ChildType(middle + 1, end));;
            }
        }
    };
    
    std::unique_ptr<Node<0>> root;
    
    template<int SplitDimension>
    void rangeQueryHelper(Node<SplitDimension> node, const Point<Dimension>& p, float radius, vector<Point<Dimension> > query) const{
        if (distance(p, node->p) <= radius) {
            query.push_back(node);
        }
        float distance = p[SplitDimension] - node->p[SplitDimension];
        if (node->left != nullptr && distance >= 0 && distance <= radius) {
            rangeQueryHelper(node->left, p, radius);
        }
        if (node->right != nullptr && distance < 0 && (-1 * distance) <= radius) {
            rangeQueryHelper(node->right, p, radius);
        }
    }
    
    template<int SplitDimension>
    void KNNHelper(const unique_ptr<Node<SplitDimension>>& node, const Point<Dimension>& p, int k, AABB<Dimension> aabb, vector<Point<Dimension> >& heap) const{
        if (heap.size() < k) {
            heap.push_back(node->p);
            push_heap(heap.begin(), heap.end(), DistanceComparator<Dimension>(p));
        } else if (distance(p, node->p) < distance(heap.front(), p)) {
            pop_heap(heap.begin(), heap.end(), DistanceComparator<Dimension>(p));
            heap.pop_back();
            heap.push_back(node->p);
            push_heap(heap.begin(), heap.end(), DistanceComparator<Dimension>(p));
        }
        if (node->left != nullptr) {
            AABB<Dimension> left = aabb;
            left.maxs[SplitDimension] = node->p[SplitDimension];
            if (heap.size() < k || distance(left.closestInBox(p), p) < distance(heap.front(), p)) {
                KNNHelper(node->left, p, k, left, heap);
            }
        }
        if (node->right != nullptr) {
            AABB<Dimension> right = aabb;
            right.mins[SplitDimension] = node->p[SplitDimension];
            if (heap.size() < k || distance(right.closestInBox(p), p) < distance(heap.front(), p)) {
                KNNHelper(node->right, p, k, right, heap);
            }
        }
    }
    
public:
    
    std::vector<Point<Dimension> > rangeQuery(const Point<Dimension>& p, float radius) const{
        vector<Point<Dimension> > query = vector<Point<Dimension>>();
        rangeQueryHelper(root, p, radius, query);
        return query;
    }
    
    std::vector<Point<Dimension>> KNN(const Point<Dimension>& p, int k) const{
        vector<Point<Dimension>> heap = vector<Point<Dimension>>();
        AABB<Dimension> aabb = AABB<Dimension>();
        KNNHelper(root, p, k, aabb, heap);
        return heap;
    }
    
};

