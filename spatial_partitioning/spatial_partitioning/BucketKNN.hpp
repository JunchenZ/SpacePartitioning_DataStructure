#pragma once

#include "Point.hpp"
#include <vector>
#include <math.h>

using namespace std;

template<int Dimension> //The dimension of the points.  This can be used like any other constant within.
class BucketKNN{
    
    
public:
    
    BucketKNN(const std::vector<Point<Dimension> >& points, int divisions_)
    {
        //getbound, aabb, store the mins and maxes
        AABB<Dimension> aabb = getBounds(points);
        mins = aabb.mins;
        maxs = aabb.maxs;
        divisions = divisions_;
        
        //for{} loop to calculate tilesize
        for (int i = 0; i < Dimension; ++i) {
            tileSize[i] = (maxs[i] - mins[i]) / divisions_;
        }
        
        //create vector
        buckets = vector<vector<Point<Dimension>>>((int) pow(divisions_, Dimension));
        
        //for{} loop over each point
        for (Point<Dimension> p : points) {
            array<int, Dimension> index;
            for (int i = 0; i < Dimension; ++i) {
                int temp = (p[i] - mins[i]) / tileSize[i];
                index[i] = min(temp, divisions - 1);
            }
            int new_index = 0;
            for (int i = 0; i < Dimension; ++i) {
                new_index += index[i] * pow(divisions_, i);
            }
            buckets[new_index].push_back(p);
        }
    }
    
    std::array<int, Dimension> nextBucket(array<int, Dimension> current, array<int, Dimension> minCoords, array<int, Dimension> maxCoords) const{
        current[Dimension - 1]++; //increment the last dimension
        for(int i = Dimension - 1; i > 0; i--){
            //if we need to "carry"
            if(current[i] > maxCoords[i]){
                //reset this dimension
                current[i] = minCoords[i];
                //and add to the next "digit"
                current[i -1]++;
            } else {
                //no more carries... we're done here
                break;
            }
        }
        return current;
    }
    
    std::vector<Point<Dimension> > rangeQuery(const Point<Dimension>& p, float radius) const{
        array<int, Dimension> min_index, max_index;
        array<float, Dimension> min_bound, max_bound;
        for (int i = 0; i < Dimension; ++i) {
            min_bound[i] = p[i] - radius;
            int temp = (min_bound[i] - mins[i]) / tileSize[i];
            min_index[i] = max(temp, 0);
            max_bound[i] = p[i] + radius;
            temp = (max_bound[i] - mins[i]) / tileSize[i];
            max_index[i] = min(temp, divisions - 1);
        }
        
        vector<Point<Dimension> > res;
        array<int, Dimension> current = min_index;
        
        while (true) {
            int new_index = 0;
            for (int i = 0; i < Dimension; ++i) {
                new_index += current[i] * pow(divisions, i);
            }
            for (Point<Dimension> point : buckets[new_index]) {
                if (distance(point, p) <= radius) {
                    res.push_back(point);
                }
            }
            if (current == max_index) {
                break;
            }
            current = nextBucket(current, min_index, max_index);
        }
        return res;
    }
    
    
    std::vector<Point<Dimension> > KNN(const Point<Dimension>& p, int k) const{
        float radius = tileSize[0];
        vector<Point<Dimension>> points = rangeQuery(p, radius);
        while (points.size() < k) {
            radius += tileSize[0];
            points = rangeQuery(p, radius);
        }
        DistanceComparator dc = DistanceComparator<Dimension>(p);
        sort(points.begin(), points.end(), dc);
        vector<Point<Dimension>> res = vector<Point<Dimension>>();
        for (int i = 0; i < k; ++i) {
            res.push_back(points.at(i));
        }
        return res;
    }
    
    
private:
    array<float, Dimension> mins, maxs, tileSize;
    vector<vector<Point<Dimension>>> buckets;
    int divisions;
};
